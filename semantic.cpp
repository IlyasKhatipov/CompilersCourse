#include "semantic.hpp"
#include <typeinfo>

SemanticAnalyzer::SemanticAnalyzer() {
    classes.clear();
    curClass = nullptr;
    curMethod = nullptr;
    localsStack.clear();
}

void SemanticAnalyzer::indexClasses(AST::Program* p) {
    classes.clear();
    if (p) {
        for (auto* c : p->classes) {
            if (c) classes[c->name] = c;
        }
    }
    if (!classes.count("Integer")) classes["Integer"] = nullptr;
    if (!classes.count("Real")) classes["Real"] = nullptr;
    if (!classes.count("Boolean")) classes["Boolean"] = nullptr;
}

SemanticResult SemanticAnalyzer::analyze(AST::Program* p) {
    result = SemanticResult();
    indexClasses(p);
    if (p) {
        for (auto* c : p->classes) {
            if (c) analyzeClass(c);
        }
    }
    return result;
}

void SemanticAnalyzer::analyzeClass(AST::ClassDecl* c) {
    curClass = c;
    analyzeFields(c);
    for (auto* ctor : c->ctors) {
        if (ctor) analyzeCtor(ctor);
    }
    for (auto* m : c->methods) {
        if (m) analyzeMethod(m);
    }
    curClass = nullptr;
}

void SemanticAnalyzer::analyzeFields(AST::ClassDecl* c) {
    for (auto* f : c->fields) {
        if (!f) continue;
        if (!f->init) {
            result.addError("Field '" + f->name + "' in class '" + c->name + "' must have initializer");
            continue;
        }
        std::string t = typeOfExpr(f->init);
        f->typeName = t;
    }
}

void SemanticAnalyzer::pushScope() {
    localsStack.emplace_back();
}

void SemanticAnalyzer::popScope() {
    if (!localsStack.empty()) localsStack.pop_back();
}

void SemanticAnalyzer::declareLocal(const std::string& name, const std::string& type) {
    if (localsStack.empty()) pushScope();
    localsStack.back()[name] = type;
}

void SemanticAnalyzer::markUsed(const std::string& name) {
    usedLocals.push_back(name);
}

void SemanticAnalyzer::analyzeCtor(AST::CtorDecl* c) {
    curMethod = nullptr;
    localsStack.clear();
    declaredLocals.clear();
    usedLocals.clear();

    pushScope();
    for (auto* p : c->params) {
        if (!p) continue;
        declareLocal(p->name, p->typeName);
        declaredLocals.push_back(p->name);
    }
    if (curClass) {
        for (auto* f : curClass->fields) {
            declareLocal(f->name, f->typeName);
            declaredLocals.push_back(f->name);
        }
    }

    if (auto* b = dynamic_cast<AST::Block*>(c->body)) {
        analyzeBlock(b);
    } else if (c->body) {
        AST::Block* wrap = new AST::Block();
        wrap->stmts.push_back(c->body);
        c->body = wrap;
        analyzeBlock(wrap);
    }
    removeUnreachableInBlock(dynamic_cast<AST::Block*>(c->body));
    popScope();
}

void SemanticAnalyzer::analyzeMethod(AST::MethodDecl* m) {
    curMethod = m;
    localsStack.clear();
    declaredLocals.clear();
    usedLocals.clear();

    pushScope();
    for (auto* p : m->params) {
        if (!p) continue;
        declareLocal(p->name, p->typeName);
        declaredLocals.push_back(p->name);
    }
    if (curClass) {
        for (auto* f : curClass->fields) {
            declareLocal(f->name, f->typeName);
            declaredLocals.push_back(f->name);
        }
    }

    if (auto* b = dynamic_cast<AST::Block*>(m->body)) {
        analyzeBlock(b);
    } else if (m->body) {
        AST::Block* wrap = new AST::Block();
        wrap->stmts.push_back(m->body);
        m->body = wrap;
        analyzeBlock(wrap);
    } else {
        result.addError("Method '" + m->name + "' has empty body");
    }

    removeUnreachableInBlock(dynamic_cast<AST::Block*>(m->body));

    for (const auto& name : declaredLocals) {
        bool used = false;
        for (const auto& u : usedLocals) {
            if (u == name) {
                used = true;
                break;
            }
        }
        if (!used) {
            result.warnings.push_back("Variable '" + name + "' is never used in method '" + m->name + "'");
            result.optimizations.push_back("Variable '" + name + "' is unused and can be removed in method '" + m->name + "'");
        }
    }

    popScope();
    curMethod = nullptr;
}

void SemanticAnalyzer::analyzeBlock(AST::Block* b) {
    if (!b) return;
    for (auto*& s : b->stmts) {
        analyzeStmt(s);
    }
    removeUnreachableInBlock(b);
}

void SemanticAnalyzer::analyzeStmt(AST::Stmt*& s) {
    if (!s) return;

    if (auto* ifs = dynamic_cast<AST::IfStmt*>(s)) {
        foldConstantsInExpr(ifs->cond);
        std::string ct = typeOfExpr(ifs->cond);
        if (!ct.empty() && ct != "Boolean") {
            result.addError("If condition must be Boolean");
        }
        analyzeStmt(ifs->thenS);
        analyzeStmt(ifs->elseS);
        simplifyIf(s);
        return;
    }

    if (auto* w = dynamic_cast<AST::WhileStmt*>(s)) {
        foldConstantsInExpr(w->cond);
        std::string ct = typeOfExpr(w->cond);
        if (!ct.empty() && ct != "Boolean") {
            result.addError("While condition must be Boolean");
        }
        if (auto* blk = dynamic_cast<AST::Block*>(w->body)) {
            pushScope();
            analyzeBlock(blk);
            popScope();
        } else {
            analyzeStmt(w->body);
        }
        return;
    }

    if (auto* ret = dynamic_cast<AST::ReturnStmt*>(s)) {
        if (!curMethod) {
            if (ret->value) {
                foldConstantsInExpr(ret->value);
                typeOfExpr(ret->value);
            }
            return;
        }
        if (curMethod->returnType.empty()) {
            if (ret->value) {
                foldConstantsInExpr(ret->value);
                typeOfExpr(ret->value);
                result.addError("Method '" + curMethod->name + "' must not return a value");
            }
        } else {
            if (!ret->value) {
                result.addError("Method '" + curMethod->name + "' must return a value of type '" + curMethod->returnType + "'");
            } else {
                foldConstantsInExpr(ret->value);
                std::string rt = typeOfExpr(ret->value);
                if (!rt.empty() && rt != curMethod->returnType) {
                    result.addError("Return type mismatch in method '" + curMethod->name + "': expected " + curMethod->returnType + ", got " + rt);
                }
            }
        }
        return;
    }

    if (auto* vds = dynamic_cast<AST::VarDeclStmt*>(s)) {
        if (vds->decl) {
            if (!vds->decl->init) {
                result.addError("Variable '" + vds->decl->name + "' must have initializer");
            } else {
                foldConstantsInExpr(vds->decl->init);
                std::string t = typeOfExpr(vds->decl->init);
                vds->decl->typeName = t;
                declareLocal(vds->decl->name, t);
                declaredLocals.push_back(vds->decl->name);
            }
        }
        return;
    }

    if (auto* es = dynamic_cast<AST::ExprStmt*>(s)) {
        if (es->expr) {
            foldConstantsInExpr(es->expr);
            typeOfExpr(es->expr);
        }
        return;
    }

    if (auto* blk = dynamic_cast<AST::Block*>(s)) {
        pushScope();
        analyzeBlock(blk);
        popScope();
        return;
    }
}

void SemanticAnalyzer::analyzeExpr(AST::Expr*& e) {
    if (!e) return;
    foldConstantsInExpr(e);
    typeOfExpr(e);
}

std::string SemanticAnalyzer::typeOfExpr(AST::Expr* e) {
    if (!e) return "";

    if (auto* il = dynamic_cast<AST::IntLiteral*>(e)) return "Integer";
    if (auto* rl = dynamic_cast<AST::RealLiteral*>(e)) return "Real";
    if (auto* sl = dynamic_cast<AST::StringLiteral*>(e)) return "String";
    if (auto* bl = dynamic_cast<AST::BoolLiteral*>(e)) return "Boolean";

    if (auto* th = dynamic_cast<AST::ThisExpr*>(e)) {
        if (!curClass) {
            result.addError("this used outside of class");
            return "";
        }
        return curClass->name;
    }

    if (auto* id = dynamic_cast<AST::Identifier*>(e)) {
        auto itc = classes.find(id->name);
        if (itc != classes.end()) {
            return id->name;
        }
        for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
            auto f = it->find(id->name);
            if (f != it->end()) {
                markUsed(id->name);
                return f->second;
            }
        }
        result.addError("Use of undeclared identifier '" + id->name + "'");
        return "";
    }

    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        std::string lt = typeOfExpr(bin->lhs);
        std::string rt = typeOfExpr(bin->rhs);

        if (bin->op == AST::BinOp::Assign) {
            if (auto* lid = dynamic_cast<AST::Identifier*>(bin->lhs)) {
                std::string lhsType;
                for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
                    auto f = it->find(lid->name);
                    if (f != it->end()) {
                        lhsType = f->second;
                        break;
                    }
                }
                if (lhsType.empty()) {
                    result.addError("Assignment to undeclared variable '" + lid->name + "'");
                    return "";
                }
                if (!rt.empty() && lhsType != rt) {
                    result.addError("Type mismatch in assignment to '" + lid->name + "'");
                    return "";
                }
                return lhsType;
            }
            return rt;
        }

        if (bin->op == AST::BinOp::Add || bin->op == AST::BinOp::Sub ||
            bin->op == AST::BinOp::Mul || bin->op == AST::BinOp::Div) {
            if (lt != "Integer" || rt != "Integer") {
                result.addError("Infix arithmetic operators are not allowed in O; use methods Plus/Minus/Mult/Div");
                return "";
            }
            return "Integer";
        }

        if (bin->op == AST::BinOp::Gt || bin->op == AST::BinOp::Lt || bin->op == AST::BinOp::Eq) {
            if (lt.empty() || rt.empty() || lt != rt) {
                result.addError("Relational operator used with incompatible types");
                return "";
            }
            return "Boolean";
        }

        return "";
    }

    if (auto* un = dynamic_cast<AST::Unary*>(e)) {
        std::string rt = typeOfExpr(un->rhs);
        if (un->op == AST::Unary::Op::Neg) {
            if (rt != "Integer" && rt != "Real") {
                result.addError("Unary - applied to non-numeric type");
                return "";
            }
            return rt;
        }
        return "";
    }

    if (auto* call = dynamic_cast<AST::Call*>(e)) {
        if (auto* id = dynamic_cast<AST::Identifier*>(call->callee)) {
            if (id->name == "output" || id->name == "print") {
                for (auto* a : call->args) typeOfExpr(a);
                return "";
            }
            auto itc = classes.find(id->name);
            if (itc != classes.end()) {
                for (auto* a : call->args) typeOfExpr(a);
                return id->name;
            }
            if (curClass) {
                for (auto* m : curClass->methods) {
                    if (m->name == id->name) {
                        for (auto* a : call->args) typeOfExpr(a);
                        return m->returnType;
                    }
                }
            }
            for (auto* a : call->args) typeOfExpr(a);
            result.addError("Call to unknown function or constructor '" + id->name + "'");
            return "";
        }
        if (auto* ma = dynamic_cast<AST::MemberAccess*>(call->callee)) {
            std::string objType = typeOfExpr(ma->object);
            for (auto* a : call->args) typeOfExpr(a);
            if (objType == "Integer") {
                if (ma->member == "Plus" || ma->member == "Minus" || ma->member == "Mult" ||
                    ma->member == "Div" || ma->member == "Rem") {
                    return "Integer";
                }
                if (ma->member == "Less" || ma->member == "LessEqual" ||
                    ma->member == "Greater" || ma->member == "GreaterEqual" ||
                    ma->member == "Equal") {
                    return "Boolean";
                }
            }
            if (objType == "Real") {
                if (ma->member == "Plus" || ma->member == "Minus" || ma->member == "Mult" ||
                    ma->member == "Div" || ma->member == "Rem") {
                    return "Real";
                }
                if (ma->member == "Less" || ma->member == "LessEqual" ||
                    ma->member == "Greater" || ma->member == "GreaterEqual" ||
                    ma->member == "Equal") {
                    return "Boolean";
                }
            }
            return "";
        }
        for (auto* a : call->args) typeOfExpr(a);
        return "";
    }

    if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        typeOfExpr(ma->object);
        return "";
    }

    if (auto* idx = dynamic_cast<AST::Index*>(e)) {
        typeOfExpr(idx->base);
        typeOfExpr(idx->index);
        return "";
    }

    return "";
}

bool SemanticAnalyzer::foldConstantsInExpr(AST::Expr*& e) {
    if (!e) return false;

    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        bool l = foldConstantsInExpr(bin->lhs);
        bool r = foldConstantsInExpr(bin->rhs);

        if (auto* L = dynamic_cast<AST::IntLiteral*>(bin->lhs)) {
            if (auto* R = dynamic_cast<AST::IntLiteral*>(bin->rhs)) {
                long long a = L->value;
                long long b = R->value;

                if (bin->op == AST::BinOp::Add || bin->op == AST::BinOp::Sub ||
                    bin->op == AST::BinOp::Mul || bin->op == AST::BinOp::Div) {
                    long long resv = 0;
                    if (bin->op == AST::BinOp::Add) resv = a + b;
                    else if (bin->op == AST::BinOp::Sub) resv = a - b;
                    else if (bin->op == AST::BinOp::Mul) resv = a * b;
                    else if (bin->op == AST::BinOp::Div) {
                        if (b == 0) {
                            result.addError("Division by zero in constant expression");
                            return false;
                        }
                        resv = a / b;
                    }
                    delete e;
                    e = new AST::IntLiteral(resv);
                    return true;
                }

                if (bin->op == AST::BinOp::Gt || bin->op == AST::BinOp::Lt || bin->op == AST::BinOp::Eq) {
                    bool rv = false;
                    if (bin->op == AST::BinOp::Gt) rv = a > b;
                    else if (bin->op == AST::BinOp::Lt) rv = a < b;
                    else if (bin->op == AST::BinOp::Eq) rv = (a == b);
                    delete e;
                    e = new AST::BoolLiteral(rv);
                    return true;
                }
            }
        }

        if (auto* LB = dynamic_cast<AST::BoolLiteral*>(bin->lhs)) {
            if (auto* RB = dynamic_cast<AST::BoolLiteral*>(bin->rhs)) {
                if (bin->op == AST::BinOp::Eq) {
                    bool rv = (LB->value == RB->value);
                    delete e;
                    e = new AST::BoolLiteral(rv);
                    return true;
                }
            }
        }

        return l || r;
    }

    if (auto* un = dynamic_cast<AST::Unary*>(e)) {
        bool r = foldConstantsInExpr(un->rhs);
        if (auto* R = dynamic_cast<AST::IntLiteral*>(un->rhs)) {
            if (un->op == AST::Unary::Op::Neg) {
                long long val = -R->value;
                delete e;
                e = new AST::IntLiteral(val);
                return true;
            }
        }
        return r;
    }

    if (auto* call = dynamic_cast<AST::Call*>(e)) {
        bool changed = foldConstantsInExpr(call->callee);
        for (auto*& a : call->args) {
            changed |= foldConstantsInExpr(a);
        }
        return changed;
    }

    if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        return foldConstantsInExpr(ma->object);
    }

    if (auto* idx = dynamic_cast<AST::Index*>(e)) {
        bool b = foldConstantsInExpr(idx->base);
        bool i = foldConstantsInExpr(idx->index);
        return b || i;
    }

    return false;
}

void SemanticAnalyzer::simplifyIf(AST::Stmt*& s) {
    if (!s) return;

    if (auto* ifs = dynamic_cast<AST::IfStmt*>(s)) {
        if (auto* bl = dynamic_cast<AST::BoolLiteral*>(ifs->cond)) {
            if (bl->value) {
                if (ifs->elseS) {
                    result.optimizations.push_back("Removed else-branch because condition is always true");
                } else {
                    result.optimizations.push_back("Simplified if true");
                }
                AST::Stmt* newstmt = nullptr;
                if (auto* tb = dynamic_cast<AST::Block*>(ifs->thenS)) {
                    newstmt = tb;
                    ifs->thenS = nullptr;
                    ifs->elseS = nullptr;
                    delete ifs->cond;
                    s = newstmt;
                } else {
                    newstmt = ifs->thenS;
                    ifs->thenS = nullptr;
                    ifs->elseS = nullptr;
                    delete ifs;
                    s = newstmt;
                }
            } else {
                if (ifs->thenS) {
                    result.optimizations.push_back("Removed then-branch because condition is always false");
                }
                if (ifs->elseS) {
                    AST::Stmt* newstmt = ifs->elseS;
                    ifs->thenS = nullptr;
                    ifs->elseS = nullptr;
                    delete ifs;
                    s = newstmt;
                } else {
                    delete ifs;
                    s = new AST::Block();
                }
            }
        }
    } else if (auto* blk = dynamic_cast<AST::Block*>(s)) {
        for (auto*& st : blk->stmts) {
            simplifyIf(st);
        }
    }
}

void SemanticAnalyzer::removeUnreachableInBlock(AST::Block* b) {
    if (!b) return;
    std::vector<AST::Stmt*> newstmts;
    bool seenReturn = false;
    bool removedAny = false;

    for (auto* s : b->stmts) {
        if (seenReturn) {
            delete s;
            removedAny = true;
            continue;
        }
        newstmts.push_back(s);
        if (dynamic_cast<AST::ReturnStmt*>(s)) seenReturn = true;
    }

    if (removedAny) {
        result.optimizations.push_back("Removed unreachable statements after return");
    }
    b->stmts = std::move(newstmts);
}
