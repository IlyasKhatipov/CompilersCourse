#include "semantic.hpp"
#include <sstream>
#include <cassert>

SemanticAnalyzer::SemanticAnalyzer() {
    classes.clear();
    types.clear();
    currentClass = nullptr;
    currentMethod = nullptr;
    currentConstructor = nullptr;
}

// Индексация классов
void SemanticAnalyzer::indexClasses(AST::Program* p) {
    for (auto* c : p->classes) {
        classes[c->name] = c;
    }
}

// Построение иерархии типов
void SemanticAnalyzer::buildTypeHierarchy() {
    // Создаем TypeInfo для каждого класса
    for (auto& pair : classes) {
        SemanticAnalyzer::TypeInfo* info = new SemanticAnalyzer::TypeInfo();
        info->name = pair.first;
        info->classDecl = pair.second;
        types[pair.first] = info;
    }
    
    // Устанавливаем связи наследования
    for (auto& pair : types) {
        AST::ClassDecl* c = pair.second->classDecl;
        if (!c->baseClass.empty()) {
            auto it = types.find(c->baseClass);
            if (it != types.end()) {
                pair.second->base = it->second;
            } else {
                result.addError("Class '" + c->name + "' extends undefined class '" + c->baseClass + "'");
            }
        }
    }
    
    // Проверяем циклические зависимости
    for (auto& pair : types) {
        SemanticAnalyzer::TypeInfo* current = pair.second;
        std::unordered_set<SemanticAnalyzer::TypeInfo*> visited;
        
        while (current) {
            if (visited.count(current)) {
                result.addError("Circular inheritance detected for class '" + pair.first + "'");
                break;
            }
            visited.insert(current);
            current = current->base;
        }
    }
}

SemanticAnalyzer::TypeInfo* SemanticAnalyzer::getTypeInfo(const std::string& name) {
    auto it = types.find(name);
    if (it != types.end()) return it->second;
    
    // Проверяем встроенные типы
    if (name == "Integer" || name == "Real" || name == "Boolean" || 
        name == "Array" || name == "List") {
        SemanticAnalyzer::TypeInfo* info = new SemanticAnalyzer::TypeInfo();
        info->name = name;
        types[name] = info;
        return info;
    }
    
    return nullptr;
}

// Основной метод анализа
SemanticResult SemanticAnalyzer::analyze(AST::Program* p) {
    result = SemanticResult();
    
    indexClasses(p);
    buildTypeHierarchy();
    
    if (!result.ok) return result;
    
    // Анализируем каждый класс
    for (auto* c : p->classes) {
        analyzeClass(c);
    }
    
    // Удаляем неиспользуемые переменные
    removeUnusedVars();
    
    return result;
}

void SemanticAnalyzer::analyzeClass(AST::ClassDecl* c) {
    currentClass = c;
    
    // Анализируем поля
    for (auto* f : c->fields) {
        analyzeField(f);
    }
    
    // Анализируем конструкторы
    for (auto* cons : c->constructors) {
        analyzeConstructor(cons);
    }
    
    // Анализируем методы
    for (auto* m : c->methods) {
        analyzeMethod(m);
    }
    
    currentClass = nullptr;
}

void SemanticAnalyzer::analyzeField(AST::VarDecl* f) {
    pushScope();
    
    SemanticAnalyzer::TypeInfo* initType = typeOfExpr(f->initializer);
    if (!initType) {
        result.addError("Field '" + f->name + "' has invalid initializer type");
    }
    
    // Проверяем, что инициализатор использует только определенные поля/методы
    // (в реализации можно добавить дополнительную проверку)
    
    popScope();
}

void SemanticAnalyzer::analyzeConstructor(AST::ConstructorDecl* c) {
    currentConstructor = c;
    pushScope();
    
    // Объявляем параметры
    for (auto* p : c->params) {
        SemanticAnalyzer::TypeInfo* paramType = getTypeInfo(p->typeName);
        if (!paramType) {
            result.addError("Unknown type '" + p->typeName + "' for parameter '" + p->name + "'");
        } else {
            declareVariable(p->name, paramType);
        }
    }
    
    // Анализируем тело
    if (c->body) {
        analyzeBlock(c->body);
    }
    
    popScope();
    currentConstructor = nullptr;
}

void SemanticAnalyzer::analyzeMethod(AST::MethodDecl* m) {
    currentMethod = m;
    pushScope();
    
    // Объявляем параметры
    for (auto* p : m->params) {
        SemanticAnalyzer::TypeInfo* paramType = getTypeInfo(p->typeName);
        if (!paramType) {
            result.addError("Unknown type '" + p->typeName + "' for parameter '" + p->name + "'");
        } else {
            declareVariable(p->name, paramType);
        }
    }
    
    // Анализируем тело
    if (m->body) {
        analyzeStmt(m->body);
        
        // Проверяем возвращаемое значение
        if (!m->returnType.empty()) {
            SemanticAnalyzer::TypeInfo* expectedType = getTypeInfo(m->returnType);
            if (!expectedType) {
                result.addError("Unknown return type '" + m->returnType + "' for method '" + m->name + "'");
            }
            // TODO: Проверить, что все пути возвращают значение правильного типа
        }
    }
    
    popScope();
    currentMethod = nullptr;
}

void SemanticAnalyzer::analyzeBlock(AST::Block* b) {
    if (!b) return;
    
    pushScope();
    
    for (auto*& s : b->stmts) {
        analyzeStmt(s);
    }
    
    // Оптимизации
    removeUnreachableInBlock(b);
    
    popScope();
}

void SemanticAnalyzer::analyzeStmt(AST::Stmt*& s) {
    if (!s) return;
    
    if (auto* es = dynamic_cast<AST::ExprStmt*>(s)) {
        analyzeExpr(es->expr);
        
    } else if (auto* as = dynamic_cast<AST::AssignmentStmt*>(s)) {
        // Проверяем, что переменная объявлена
        bool found = false;
        for (int i = scopes.size() - 1; i >= 0; i--) {
            if (scopes[i].variables.find(as->varName) != scopes[i].variables.end()) {
                found = true;
                markVariableUsed(as->varName);
                break;
            }
        }
        
        if (!found) {
            // Проверяем, может быть это поле класса
            if (currentClass && findField(currentClass->name, as->varName)) {
                // Это поле класса
            } else {
                result.addError("Assignment to undeclared variable '" + as->varName + "'");
            }
        }
        
        analyzeExpr(as->value);
        
    } else if (auto* rs = dynamic_cast<AST::ReturnStmt*>(s)) {
        if (!currentMethod && !currentConstructor) {
            result.addError("Return statement outside of method or constructor");
        } else {
            if (rs->value) {
                analyzeExpr(rs->value);
                
                if (currentMethod && !currentMethod->returnType.empty()) {
                    SemanticAnalyzer::TypeInfo* returnType = typeOfExpr(rs->value);
                    SemanticAnalyzer::TypeInfo* expectedType = getTypeInfo(currentMethod->returnType);
                    
                    if (returnType && expectedType && !isAssignable(expectedType, returnType)) {
                        result.addError("Return type mismatch in method '" + currentMethod->name + "'");
                    }
                } else if (currentConstructor) {
                    result.addError("Constructor cannot return a value");
                }
            } else if (currentMethod && !currentMethod->returnType.empty()) {
                result.addError("Method '" + currentMethod->name + "' must return a value");
            }
        }
        
    } else if (auto* is = dynamic_cast<AST::IfStmt*>(s)) {
        analyzeExpr(is->cond);
        analyzeStmt(is->thenStmt);
        if (is->elseStmt) analyzeStmt(is->elseStmt);
        
        // Оптимизация
        simplifyIf(s);
        
    } else if (auto* ws = dynamic_cast<AST::WhileStmt*>(s)) {
        analyzeExpr(ws->cond);
        analyzeStmt(ws->body);
        
    } else if (auto* vs = dynamic_cast<AST::VarDeclStmt*>(s)) {
        analyzeExpr(vs->decl->initializer);
        
        SemanticAnalyzer::TypeInfo* initType = typeOfExpr(vs->decl->initializer);
        if (initType) {
            declareVariable(vs->decl->name, initType);
        }
        
    } else if (auto* b = dynamic_cast<AST::Block*>(s)) {
        analyzeBlock(b);
    }
}

void SemanticAnalyzer::analyzeExpr(AST::Expr*& e) {
    if (!e) return;
    
    // Константное свертывание
    bool folded = foldConstantsInExpr(e);
    if (folded) {
        result.addOptimization("Constant expression folded");
    }
    
    if (dynamic_cast<AST::IntLiteral*>(e)) {
        // Ничего не делать
        
    } else if (dynamic_cast<AST::RealLiteral*>(e)) {
        // Ничего не делать
        
    } else if (dynamic_cast<AST::BoolLiteral*>(e)) {
        // Ничего не делать
        
    } else if (auto* tl = dynamic_cast<AST::ThisLiteral*>(e)) {
        (void)tl; // подавляем warning
        if (!currentClass) {
            result.addError("'this' used outside of class context");
        }
        
    } else if (auto* id = dynamic_cast<AST::Identifier*>(e)) {
        // Проверяем, что идентификатор объявлен
        bool found = false;
        for (int i = scopes.size() - 1; i >= 0; i--) {
            if (scopes[i].variables.find(id->name) != scopes[i].variables.end()) {
                found = true;
                markVariableUsed(id->name);
                break;
            }
        }
        
        if (!found) {
            // Проверяем, может быть это поле класса
            if (currentClass && findField(currentClass->name, id->name)) {
                // Это поле класса
            } else {
                result.addError("Use of undeclared identifier '" + id->name + "'");
            }
        }
        
    } else if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        analyzeExpr(ma->object);
        
        SemanticAnalyzer::TypeInfo* objectType = typeOfExpr(ma->object);
        if (objectType) {
            // Проверяем, что member существует в этом классе
            AST::VarDecl* field = findField(objectType->name, ma->member);
            if (!field) {
                result.addError("Class '" + objectType->name + "' has no field '" + ma->member + "'");
            }
        }
        
    } else if (auto* mc = dynamic_cast<AST::MethodCall*>(e)) {
        analyzeExpr(mc->object);
        
        for (auto* arg : mc->args) {
            analyzeExpr(arg);
        }
        
        SemanticAnalyzer::TypeInfo* returnType = typeOfMethodCall(mc);
        (void)returnType; // подавляем warning
        
    } else if (auto* cc = dynamic_cast<AST::ConstructorCall*>(e)) {
        for (auto* arg : cc->args) {
            analyzeExpr(arg);
        }
        
        SemanticAnalyzer::TypeInfo* createdType = typeOfConstructorCall(cc);
        (void)createdType; // подавляем warning
    }
}

// Проверка типов выражений
SemanticAnalyzer::TypeInfo* SemanticAnalyzer::typeOfExpr(AST::Expr* e) {
    if (!e) return nullptr;
    
    if (dynamic_cast<AST::IntLiteral*>(e)) {
        return getTypeInfo("Integer");
        
    } else if (dynamic_cast<AST::RealLiteral*>(e)) {
        return getTypeInfo("Real");
        
    } else if (dynamic_cast<AST::BoolLiteral*>(e)) {
        return getTypeInfo("Boolean");
        
    } else if (auto* tl = dynamic_cast<AST::ThisLiteral*>(e)) {
        (void)tl; // подавляем warning
        if (currentClass) {
            return getTypeInfo(currentClass->name);
        }
        return nullptr;
        
    } else if (auto* id = dynamic_cast<AST::Identifier*>(e)) {
        // Ищем переменную в областях видимости
        for (int i = scopes.size() - 1; i >= 0; i--) {
            auto it = scopes[i].variables.find(id->name);
            if (it != scopes[i].variables.end()) {
                return it->second;
            }
        }
        
        // Проверяем, может быть это поле класса
        if (currentClass) {
            AST::VarDecl* field = findField(currentClass->name, id->name);
            if (field) {
                // Нужно определить тип поля
                SemanticAnalyzer::TypeInfo* fieldType = typeOfExpr(field->initializer);
                return fieldType;
            }
        }
        
        return nullptr;
        
    } else if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        SemanticAnalyzer::TypeInfo* objectType = typeOfExpr(ma->object);
        if (!objectType) return nullptr;
        
        AST::VarDecl* field = findField(objectType->name, ma->member);
        if (field) {
            return typeOfExpr(field->initializer);
        }
        
        return nullptr;
        
    } else if (auto* mc = dynamic_cast<AST::MethodCall*>(e)) {
        return typeOfMethodCall(mc);
        
    } else if (auto* cc = dynamic_cast<AST::ConstructorCall*>(e)) {
        return typeOfConstructorCall(cc);
    }
    
    return nullptr;
}

SemanticAnalyzer::TypeInfo* SemanticAnalyzer::typeOfMethodCall(AST::MethodCall* mc) {
    SemanticAnalyzer::TypeInfo* objectType = typeOfExpr(mc->object);
    if (!objectType) return nullptr;
    
    // Ищем метод в классе
    AST::MethodDecl* method = findMethod(objectType->name, mc->methodName);
    if (!method) {
        result.addError("Class '" + objectType->name + "' has no method '" + mc->methodName + "'");
        return nullptr;
    }
    
    // Проверяем количество аргументов
    if (method->params.size() != mc->args.size()) {
        result.addError("Method '" + mc->methodName + "' expects " + 
                       std::to_string(method->params.size()) + 
                       " arguments, got " + std::to_string(mc->args.size()));
        return nullptr;
    }
    
    // Проверяем типы аргументов
    for (size_t i = 0; i < mc->args.size(); i++) {
        SemanticAnalyzer::TypeInfo* argType = typeOfExpr(mc->args[i]);
        SemanticAnalyzer::TypeInfo* paramType = getTypeInfo(method->params[i]->typeName);
        
        if (argType && paramType && !isAssignable(paramType, argType)) {
            result.addError("Argument " + std::to_string(i+1) + 
                           " type mismatch in call to method '" + mc->methodName + "'");
        }
    }
    
    if (method->returnType.empty()) {
        return nullptr; // void method
    }
    
    return getTypeInfo(method->returnType);
}

SemanticAnalyzer::TypeInfo* SemanticAnalyzer::typeOfConstructorCall(AST::ConstructorCall* cc) {
    // Для простых конструкторов
    SemanticAnalyzer::TypeInfo* classType = getTypeInfo(cc->className);
    if (!classType) {
        result.addError("Unknown class '" + cc->className + "'");
        return nullptr;
    }
    
    // Ищем конструктор с правильным количеством параметров
    // (упрощенно - проверяем только количество)
    AST::ClassDecl* classDecl = classType->classDecl;
    if (classDecl) {
        bool found = false;
        for (auto* cons : classDecl->constructors) {
            if (cons->params.size() == cc->args.size()) {
                found = true;
                
                // Проверяем типы аргументов
                for (size_t i = 0; i < cc->args.size(); i++) {
                    SemanticAnalyzer::TypeInfo* argType = typeOfExpr(cc->args[i]);
                    SemanticAnalyzer::TypeInfo* paramType = getTypeInfo(cons->params[i]->typeName);
                    
                    if (argType && paramType && !isAssignable(paramType, argType)) {
                        result.addError("Argument " + std::to_string(i+1) + 
                                       " type mismatch in constructor call");
                    }
                }
                break;
            }
        }
        
        if (!found) {
            result.addError("No matching constructor found for class '" + cc->className + 
                           "' with " + std::to_string(cc->args.size()) + " arguments");
        }
    }
    
    return classType;
}

// Проверка совместимости типов
bool SemanticAnalyzer::isAssignable(SemanticAnalyzer::TypeInfo* target, SemanticAnalyzer::TypeInfo* source) {
    if (!target || !source) return false;
    
    // Если типы одинаковые
    if (target->name == source->name) return true;
    
    // Проверяем наследование
    if (source->isSubtypeOf(target->name)) return true;
    
    // Неявные преобразования (Integer -> Real и т.д.)
    if (target->name == "Real" && source->name == "Integer") return true;
    
    return false;
}

bool SemanticAnalyzer::typesCompatible(SemanticAnalyzer::TypeInfo* t1, SemanticAnalyzer::TypeInfo* t2) {
    return isAssignable(t1, t2) || isAssignable(t2, t1);
}

// Поиск методов и полей
AST::MethodDecl* SemanticAnalyzer::findMethod(const std::string& className, const std::string& methodName) {
    auto it = classes.find(className);
    if (it == classes.end()) return nullptr;
    
    AST::ClassDecl* classDecl = it->second;
    
    // Ищем в текущем классе
    for (auto* m : classDecl->methods) {
        if (m->name == methodName) return m;
    }
    
    // Ищем в базовых классах
    SemanticAnalyzer::TypeInfo* typeInfo = getTypeInfo(className);
    while (typeInfo && typeInfo->base) {
        classDecl = typeInfo->base->classDecl;
        for (auto* m : classDecl->methods) {
            if (m->name == methodName) return m;
        }
        typeInfo = typeInfo->base;
    }
    
    return nullptr;
}

AST::VarDecl* SemanticAnalyzer::findField(const std::string& className, const std::string& fieldName) {
    auto it = classes.find(className);
    if (it == classes.end()) return nullptr;
    
    AST::ClassDecl* classDecl = it->second;
    
    // Ищем в текущем классе
    for (auto* f : classDecl->fields) {
        if (f->name == fieldName) return f;
    }
    
    // Ищем в базовых классах
    SemanticAnalyzer::TypeInfo* typeInfo = getTypeInfo(className);
    while (typeInfo && typeInfo->base) {
        classDecl = typeInfo->base->classDecl;
        for (auto* f : classDecl->fields) {
            if (f->name == fieldName) return f;
        }
        typeInfo = typeInfo->base;
    }
    
    return nullptr;
}

// Оптимизации
bool SemanticAnalyzer::foldConstantsInExpr(AST::Expr*& e) {
    (void)e; // пока не реализовано
    return false;
}

void SemanticAnalyzer::simplifyIf(AST::Stmt*& s) {
    if (!s) return;
    
    if (auto* is = dynamic_cast<AST::IfStmt*>(s)) {
        if (auto* bl = dynamic_cast<AST::BoolLiteral*>(is->cond)) {
            if (bl->value) {
                // if true -> then branch
                result.addOptimization("Removed always-false else branch");
                AST::Stmt* newStmt = is->thenStmt;
                is->thenStmt = nullptr;
                is->elseStmt = nullptr;
                delete is;
                s = newStmt;
            } else {
                // if false -> else branch or empty
                result.addOptimization("Removed always-false then branch");
                if (is->elseStmt) {
                    AST::Stmt* newStmt = is->elseStmt;
                    is->thenStmt = nullptr;
                    is->elseStmt = nullptr;
                    delete is;
                    s = newStmt;
                } else {
                    delete is;
                    s = new AST::Block(); // empty block
                }
            }
        }
    } else if (auto* b = dynamic_cast<AST::Block*>(s)) {
        for (auto*& stmt : b->stmts) {
            simplifyIf(stmt);
        }
    }
}

void SemanticAnalyzer::removeUnreachableInBlock(AST::Block* b) {
    if (!b) return;
    
    std::vector<AST::Stmt*> newStmts;
    bool reachableEnded = false;
    
    for (auto* s : b->stmts) {
        if (reachableEnded) {
            delete s;
            continue;
        }
        
        newStmts.push_back(s);
        
        // Проверяем, является ли этот оператор завершающим
        if (dynamic_cast<AST::ReturnStmt*>(s)) {
            reachableEnded = true;
        }
    }
    
    if (reachableEnded && newStmts.size() < b->stmts.size()) {
        result.addOptimization("Removed unreachable code after return");
        b->stmts = std::move(newStmts);
    }
}

void SemanticAnalyzer::removeUnusedVars() {
    // Уже обрабатывается при анализе через markVariableUsed
}

// Управление областей видимости
void SemanticAnalyzer::pushScope() {
    scopes.push_back(Scope());
}

void SemanticAnalyzer::popScope() {
    if (!scopes.empty()) {
        // Проверяем неиспользованные переменные в этой области
        Scope& scope = scopes.back();
        for (auto& pair : scope.variables) {
            if (!scope.used[pair.first]) {
                result.addWarning("Variable '" + pair.first + "' declared but never used");
            }
        }
        scopes.pop_back();
    }
}

void SemanticAnalyzer::declareVariable(const std::string& name, SemanticAnalyzer::TypeInfo* type) {
    if (scopes.empty()) pushScope();
    scopes.back().variables[name] = type;
    scopes.back().used[name] = false;
}

void SemanticAnalyzer::markVariableUsed(const std::string& name) {
    for (int i = scopes.size() - 1; i >= 0; i--) {
        if (scopes[i].variables.find(name) != scopes[i].variables.end()) {
            scopes[i].used[name] = true;
            return;
        }
    }
}

// Утилиты
std::string SemanticAnalyzer::getPosition() {
    // TODO: Добавить информацию о позиции в исходном коде
    return "";
}