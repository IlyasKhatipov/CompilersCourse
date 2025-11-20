#include "semantic.hpp"
#include <sstream>
#include <typeinfo>
#include <cassert>

std::string SemanticAnalyzer::curPos(AST::Node* n) {
    (void)n;
    return "";
}

SemanticAnalyzer::SemanticAnalyzer() {
    classes.clear();
    curClass = nullptr;
    curMethod = nullptr;
    localsStack.clear();
}

void SemanticAnalyzer::indexClasses(AST::Program* p) {
    for (auto* c : p->classes) {
        classes[c->name] = c;
    }
}

SemanticResult SemanticAnalyzer::analyze(AST::Program* p) {
    result = SemanticResult();
    indexClasses(p);
    for (auto* c : p->classes) analyzeClass(c);
    return result;
}

void SemanticAnalyzer::analyzeClass(AST::ClassDecl* c) {
    curClass = c;
    for (auto* m : c->methods) analyzeMethod(m);
    curClass = nullptr;
}

void SemanticAnalyzer::analyzeMethod(AST::MethodDecl* m) {
    curMethod = m;
    pushScope();
    declaredLocals.clear();
    usedLocals.clear();
    for (auto* p : m->params) {
        declareLocal(p->name, p->typeName);
    }
    for (auto* f : curClass->fields) {
        declareLocal(f->name, f->typeName);
    }
    if (m->body) {
        analyzeBlock(dynamic_cast<AST::Block*>(m->body));
    } else {
        result.addError("Method " + m->name + " has empty body");
    }
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

std::string SemanticAnalyzer::typeOfExpr(AST::Expr* e) {
    if (!e) return "";
    if (auto* il = dynamic_cast<AST::IntLiteral*>(e)) return std::string("Int");
    if (auto* sl = dynamic_cast<AST::StringLiteral*>(e)) return std::string("String");
    if (auto* bl = dynamic_cast<AST::BoolLiteral*>(e)) return std::string("Bool");
    if (auto* id = dynamic_cast<AST::Identifier*>(e)) {
        for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
            auto found = it->find(id->name);
            if (found != it->end()) return found->second;
        }
        result.addError("Use of undeclared identifier '" + id->name + "'");
        return "";
    }
    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        auto lhs = typeOfExpr(bin->lhs);
        auto rhs = typeOfExpr(bin->rhs);
        switch (bin->op) {
            case AST::BinOp::Add: case AST::BinOp::Sub: case AST::BinOp::Mul: case AST::BinOp::Div:
                if (lhs != "Int" || rhs != "Int") {
                    result.addError("Arithmetic operator used with non-Int operands");
                    return "";
                }
                return "Int";
            case AST::BinOp::Gt: case AST::BinOp::Lt:
                if (lhs != "Int" || rhs != "Int") {
                    result.addError("Relational operator used with non-Int operands");
                    return "";
                }
                return "Bool";
            case AST::BinOp::Eq:
                if (lhs == "" || rhs == "" || lhs != rhs) {
                    result.addError("Equality operator used with incompatible types");
                    return "";
                }
                return "Bool";
            case AST::BinOp::Assign:
                if (auto* lid = dynamic_cast<AST::Identifier*>(bin->lhs)) {
                    std::string lhs_type;
                    for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
                        auto found = it->find(lid->name);
                        if (found != it->end()) { lhs_type = found->second; break; }
                    }
                    if (lhs_type.empty()) {
                        result.addError("Assignment to undeclared variable '" + lid->name + "'");
                        return "";
                    }
                    if (lhs_type != rhs) {
                        result.addError("Type mismatch in assignment to '" + lid->name + "'");
                        return "";
                    }
                    return lhs_type;
                }
                return rhs;
        }
    }
    if (auto* un = dynamic_cast<AST::Unary*>(e)) {
        auto rt = typeOfExpr(un->rhs);
        if (un->op == AST::Unary::Op::Neg) {
            if (rt != "Int") {
                result.addError("Unary - applied to non-Int");
                return "";
            }
            return "Int";
        }
    }
    if (auto* call = dynamic_cast<AST::Call*>(e)) {
        if (auto* id = dynamic_cast<AST::Identifier*>(call->callee)) {
            if (id->name == "output" || id->name == "print") {
                for (auto* a : call->args) typeOfExpr(a);
                return "";
            }
            auto it = classes.find(curClass->name);
            if (it != classes.end()) {
                bool found = false;
                for (auto* m : it->second->methods) {
                    if (m->name == id->name) { found = true; break; }
                }
                if (!found) {
                    result.addError("Call to undeclared method '" + id->name + "' in class '" + curClass->name + "'");
                }
            }
            return "";
        }
        return "";
    }
    if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        if (auto* objid = dynamic_cast<AST::Identifier*>(ma->object)) {
            std::string t;
            for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
                auto found = it->find(objid->name);
                if (found != it->end()) { t = found->second; break; }
            }
            if (t.empty()) {
                result.addError("Unknown object '" + objid->name + "' for member access");
                return "";
            }
            auto cit = classes.find(t);
            if (cit != classes.end()) {
                for (auto* f : cit->second->fields) if (f->name == ma->member) return f->typeName;
            }
        }
        return "";
    }
    if (auto* idx = dynamic_cast<AST::Index*>(e)) {
        typeOfExpr(idx->base);
        typeOfExpr(idx->index);
        return "";
    }
    return "";
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
        analyzeExpr(ifs->cond);
        analyzeStmt(ifs->thenS);
        analyzeStmt(ifs->elseS);
        simplifyIf(s);
        return;
    }
    if (auto* w = dynamic_cast<AST::WhileStmt*>(s)) {
        analyzeExpr(w->cond);
        analyzeBlock(dynamic_cast<AST::Block*>(w->body));
        return;
    }
    if (auto* ret = dynamic_cast<AST::ReturnStmt*>(s)) {
        if (!curMethod) {
            result.addError("Return used outside of method");
        } else {
            if (curMethod->returnType == "Void") {
                if (ret->value) {
                    analyzeExpr(ret->value);
                    result.addError("Void method '" + curMethod->name + "' must not return a value");
                }
            } else {
                if (!ret->value) {
                    result.addError("Non-void method '" + curMethod->name + "' must return a value of type '" + curMethod->returnType + "'");
                } else {
                    analyzeExpr(ret->value);
                    auto rv = typeOfExpr(ret->value);
                    if (rv != "" && curMethod->returnType != rv) {
                        result.addError("Return type mismatch in method '" + curMethod->name + "': expected " + curMethod->returnType + ", got " + rv);
                    }
                }
            }
        }
        return;
    }

    if (auto* es = dynamic_cast<AST::ExprStmt*>(s)) {
        analyzeExpr(es->expr);
        return;
    }
    if (auto* vds = dynamic_cast<AST::VarDeclStmt*>(s)) {
        if (vds->decl) {
            declareLocal(vds->decl->name, vds->decl->typeName);
            declaredLocals.push_back(vds->decl->name);
            if (vds->decl->init) analyzeExpr(vds->decl->init);
            if (vds->decl->init) {
                auto it = typeOfExpr(vds->decl->init);
                if (it != "" && it != vds->decl->typeName) {
                    result.addError("Initializer type mismatch for variable '" + vds->decl->name + "'");
                }
            }
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
    bool folded = foldConstantsInExpr(e);
    if (folded) {
    }
    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        analyzeExpr(bin->lhs);
        analyzeExpr(bin->rhs);
        if (bin->op == AST::BinOp::Assign) {
            if (auto* lid = dynamic_cast<AST::Identifier*>(bin->lhs)) {
                bool found = false;
                for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
                    if (it->find(lid->name) != it->end()) { found = true; break; }
                }
                if (!found) result.addError("Assignment to undeclared variable '" + lid->name + "'");
            }
        }
        return;
    }
    if (auto* un = dynamic_cast<AST::Unary*>(e)) {
        analyzeExpr(un->rhs);
        return;
    }
    if (auto* call = dynamic_cast<AST::Call*>(e)) {
        if (auto* id = dynamic_cast<AST::Identifier*>(call->callee)) {
            if (id->name == "output" || id->name == "print") {
                for (auto*& a : call->args) analyzeExpr(a);
                return;
            }
            bool found = false;
            for (auto* m : curClass->methods) if (m->name == id->name) { found = true; break; }
            if (!found) result.addError("Call to undeclared method '" + id->name + "'");
        } else {
            analyzeExpr(call->callee);
        }
        for (auto*& a : call->args) analyzeExpr(a);
        return;
    }
    if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        analyzeExpr(ma->object);
        return;
    }
    if (auto* idx = dynamic_cast<AST::Index*>(e)) {
        analyzeExpr(idx->base);
        analyzeExpr(idx->index);
        return;
    }
    if (auto* id = dynamic_cast<AST::Identifier*>(e)) {
        bool found = false;
        for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
            if (it->find(id->name) != it->end()) { found = true; break; }
        }
        if (found) {
            usedLocals.push_back(id->name);
        } else {
            result.addError("Use of undeclared identifier '" + id->name + "'");
        }
        return;
    }
}

bool SemanticAnalyzer::isLiteral(AST::Expr* e) {
    return dynamic_cast<AST::IntLiteral*>(e) || dynamic_cast<AST::StringLiteral*>(e) || dynamic_cast<AST::BoolLiteral*>(e);
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
                if (bin->op == AST::BinOp::Add || bin->op == AST::BinOp::Sub || bin->op == AST::BinOp::Mul || bin->op == AST::BinOp::Div) {
                    long long resv = 0;
                    switch (bin->op) {
                        case AST::BinOp::Add: resv = a + b; break;
                        case AST::BinOp::Sub: resv = a - b; break;
                        case AST::BinOp::Mul: resv = a * b; break;
                        case AST::BinOp::Div:
                            if (b == 0) { result.addError("Division by zero in constant expression"); return false; }
                            resv = a / b; break;
                        default: break;
                    }
                    delete e;
                    e = new AST::IntLiteral(resv);
                    return true;
                }
                if (bin->op == AST::BinOp::Gt || bin->op == AST::BinOp::Lt) {
                    bool rr = false;
                    if (bin->op == AST::BinOp::Gt) rr = (a > b);
                    else rr = (a < b);
                    delete e;
                    e = new AST::BoolLiteral(rr);
                    return true;
                }
                if (bin->op == AST::BinOp::Eq) {
                    bool rr = (a == b);
                    delete e;
                    e = new AST::BoolLiteral(rr);
                    return true;
                }
            }
        }
        if (auto* LB = dynamic_cast<AST::BoolLiteral*>(bin->lhs)) {
            if (auto* RB = dynamic_cast<AST::BoolLiteral*>(bin->rhs)) {
                if (bin->op == AST::BinOp::Eq) {
                    bool rr = (LB->value == RB->value);
                    delete e;
                    e = new AST::BoolLiteral(rr);
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
        bool changed = false;
        changed |= foldConstantsInExpr(call->callee);
        for (auto*& a : call->args) changed |= foldConstantsInExpr(a);
        return changed;
    }
    if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        bool changed = foldConstantsInExpr(ma->object);
        return changed;
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
                    result.optimizations.push_back("Simplified 'if true' condition");
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
                    ifs->elseS = nullptr;
                    ifs->thenS = nullptr;
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
