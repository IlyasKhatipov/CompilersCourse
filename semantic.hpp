#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "ast.hpp"

struct SemanticResult {
    bool ok = true;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;       
    std::vector<std::string> optimizations;  

    void addError(const std::string& msg) { 
        ok = false; 
        errors.push_back(msg); 
    }
    void addWarning(const std::string& msg) { 
        warnings.push_back(msg); 
    }        
    void addOptimization(const std::string& msg) { 
        optimizations.push_back(msg); 
    } 
};

class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    SemanticResult analyze(AST::Program* p);

private:
    // Система типов
    struct TypeInfo {
        std::string name;
        AST::ClassDecl* classDecl = nullptr;
        TypeInfo* base = nullptr;
        
        bool isSubtypeOf(const std::string& other) const {
            if (name == other) return true;
            if (base) return base->isSubtypeOf(other);
            return false;
        }
    };
    
    // Контекст анализа
    std::unordered_map<std::string, AST::ClassDecl*> classes;
    std::unordered_map<std::string, TypeInfo*> types;
    
    AST::ClassDecl* currentClass = nullptr;
    AST::MethodDecl* currentMethod = nullptr;
    AST::ConstructorDecl* currentConstructor = nullptr;
    
    // Локальные переменные и их типы
    struct Scope {
        std::unordered_map<std::string, TypeInfo*> variables;
        std::unordered_map<std::string, bool> used;
    };
    std::vector<Scope> scopes;
    
    SemanticResult result;
    
    // Вспомогательные методы
    void indexClasses(AST::Program* p);
    void buildTypeHierarchy();
    TypeInfo* getTypeInfo(const std::string& name);
    
    // Анализ
    void analyzeClass(AST::ClassDecl* c);
    void analyzeConstructor(AST::ConstructorDecl* c);
    void analyzeMethod(AST::MethodDecl* m);
    void analyzeField(AST::VarDecl* f);
    
    void analyzeBlock(AST::Block* b);
    void analyzeStmt(AST::Stmt*& s);
    void analyzeExpr(AST::Expr*& e);
    
    // Проверки типов
    TypeInfo* typeOfExpr(AST::Expr* e);
    TypeInfo* typeOfConstructorCall(AST::ConstructorCall* cc);
    TypeInfo* typeOfMethodCall(AST::MethodCall* mc);
    
    bool isAssignable(TypeInfo* target, TypeInfo* source);
    bool typesCompatible(TypeInfo* t1, TypeInfo* t2);
    
    // Поиск
    AST::MethodDecl* findMethod(const std::string& className, const std::string& methodName);
    AST::VarDecl* findField(const std::string& className, const std::string& fieldName);
    
    // Оптимизации
    bool foldConstantsInExpr(AST::Expr*& e);
    void simplifyIf(AST::Stmt*& s);
    void removeUnreachableInBlock(AST::Block* b);
    void removeUnusedVars();
    
    // Управление областями видимости
    void pushScope();
    void popScope();
    void declareVariable(const std::string& name, TypeInfo* type);
    void markVariableUsed(const std::string& name);
    
    // Утилиты
    std::string getPosition();
};