#include "semantic.hpp"
#include <sstream>
#include <typeinfo>
#include <cassert>

// Helper to get node position (best-effort, using identifiers not storing positions)
std::string SemanticAnalyzer::curPos(AST::Node* n) {
    (void)n;
    return ""; // AST nodes currently don't store line/column, so empty
}

SemanticAnalyzer::SemanticAnalyzer() {
    classes.clear();
    curClass = nullptr;
    curMethod = nullptr;
    localsStack.clear();
}

// Build class index
void SemanticAnalyzer::indexClasses(AST::Program* p) {
    for (auto* c : p->classes) {
        classes[c->name] = c;
    }
}

SemanticResult SemanticAnalyzer::analyze(AST::Program* p) {
    result = SemanticResult();
    indexClasses(p);
    // analyze each class
    for (auto* c : p->classes) analyzeClass(c);
    return result;
}

void SemanticAnalyzer::analyzeClass(AST::ClassDecl* c) {
    curClass = c;
    // fields become available as "locals" inside methods
    for (auto* m : c->methods) analyzeMethod(m);
    curClass = nullptr;
}

void SemanticAnalyzer::analyzeMethod(AST::MethodDecl* m) {
    curMethod = m;
    pushScope();
    // declare parameters
    for (auto* p : m->params) {
        declareLocal(p->name, p->typeName);
    }
    // declare fields (accessible as locals too)
    for (auto* f : curClass->fields) {
        declareLocal(f->name, f->typeName);
    }
    // optimize/mutate body before or after checks? We'll do folding first, then checks & other optimizations
    if (m->body) {
        // perform constant folding for expressions inside this method body
        analyzeBlock(dynamic_cast<AST::Block*>(m->body));
    } else {
        result.addError("Method " + m->name + " has empty body");
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
        // lookup locals stack from top
        for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
            auto found = it->find(id->name);
            if (found != it->end()) return found->second;
        }
        // not found — maybe it's a type-as-expr stored as Identifier node, but in general we warn
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
                // lhs should be lvalue: here we take rhs type and compare to declared lhs type if identifier
                if (auto* lid = dynamic_cast<AST::Identifier*>(bin->lhs)) {
                    // find declared type
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
                // assignment to member/index not deeply typed here
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
        // try to deduce member type if object has class and field exists (simple)
        if (auto* objid = dynamic_cast<AST::Identifier*>(ma->object)) {
            // find name in locals -> type is class name?
            std::string t;
            for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
                auto found = it->find(objid->name);
                if (found != it->end()) { t = found->second; break; }
            }
            if (t.empty()) {
                result.addError("Unknown object '" + objid->name + "' for member access");
                return "";
            }
            // if t matches a class name, look for field
            auto cit = classes.find(t);
            if (cit != classes.end()) {
                for (auto* f : cit->second->fields) if (f->name == ma->member) return f->typeName;
            }
        }
        return "";
    }
    if (auto* idx = dynamic_cast<AST::Index*>(e)) {
        // index expression type inference is complex; skip
        typeOfExpr(idx->base);
        typeOfExpr(idx->index);
        return "";
    }
    return "";
}

void SemanticAnalyzer::analyzeBlock(AST::Block* b) {
    if (!b) return;
    // First – recursively fold constants inside expressions and statements
    for (auto*& s : b->stmts) {
        analyzeStmt(s); // analyzeStmt will call analyzeExpr and optimizations
    }
    // Remove unreachable code after returns
    removeUnreachableInBlock(b);
}

void SemanticAnalyzer::analyzeStmt(AST::Stmt*& s) {
    if (!s) return;
    // IfStmt
    if (auto* ifs = dynamic_cast<AST::IfStmt*>(s)) {
        analyzeExpr(ifs->cond);
        analyzeStmt(ifs->thenS);
        analyzeStmt(ifs->elseS);
        // after analyzing cond, maybe it's folded to literal; try to simplify
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
            analyzeExpr(ret->value);
            auto rv = typeOfExpr(ret->value);
            if (!curMethod->returnType.empty()) {
                if (rv != "" && curMethod->returnType != rv) {
                    result.addError("Return type mismatch in method '" + curMethod->name + "': expected " + curMethod->returnType + ", got " + rv);
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
        // var declaration - register local
        if (vds->decl) {
            declareLocal(vds->decl->name, vds->decl->typeName);
            if (vds->decl->init) analyzeExpr(vds->decl->init);
            // check init type matches declared type
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
    // try constant folding first
    bool folded = foldConstantsInExpr(e);
    if (folded) {
        // folded expression replaced e; still do type checks on new e
    }
    // then recurse into structure if not literal
    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        analyzeExpr(bin->lhs);
        analyzeExpr(bin->rhs);
        // assignment: ensure lvalue exists
        if (bin->op == AST::BinOp::Assign) {
            if (auto* lid = dynamic_cast<AST::Identifier*>(bin->lhs)) {
                // must be declared
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
        // identifier use check
        bool found = false;
        for (auto it = localsStack.rbegin(); it != localsStack.rend(); ++it) {
            if (it->find(id->name) != it->end()) { found = true; break; }
        }
        if (!found) result.addError("Use of undeclared identifier '" + id->name + "'");
        return;
    }
    // literals: nothing to do
}

bool SemanticAnalyzer::isLiteral(AST::Expr* e) {
    return dynamic_cast<AST::IntLiteral*>(e) || dynamic_cast<AST::StringLiteral*>(e) || dynamic_cast<AST::BoolLiteral*>(e);
}

// constant folding implementation
bool SemanticAnalyzer::foldConstantsInExpr(AST::Expr*& e) {
    if (!e) return false;
    // recursively fold children first
    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        bool l = foldConstantsInExpr(bin->lhs);
        bool r = foldConstantsInExpr(bin->rhs);
        // after children folded, try fold this node
        if (auto* L = dynamic_cast<AST::IntLiteral*>(bin->lhs)) {
            if (auto* R = dynamic_cast<AST::IntLiteral*>(bin->rhs)) {
                long long a = L->value;
                long long b = R->value;
                if (bin->op == AST::BinOp::Add || bin->op == AST::BinOp::Sub || bin->op == AST::BinOp::Mul || bin->op == AST::BinOp::Div) {
                    long long res = 0;
                    switch (bin->op) {
                        case AST::BinOp::Add: res = a + b; break;
                        case AST::BinOp::Sub: res = a - b; break;
                        case AST::BinOp::Mul: res = a * b; break;
                        case AST::BinOp::Div: if (b == 0) { result.addError("Division by zero in constant expression"); return false; } res = a / b; break;
                        default: break;
                    }
                    delete e;
                    e = new AST::IntLiteral(res);
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
        // bool equality folding
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
        // attempt to see if cond is BoolLiteral
        if (auto* bl = dynamic_cast<AST::BoolLiteral*>(ifs->cond)) {
            if (bl->value) {
                // replace s with thenS (which may be a Block or single stmt)
                AST::Stmt* newstmt = nullptr;
                // if thenS is a Block, keep it
                if (auto* tb = dynamic_cast<AST::Block*>(ifs->thenS)) {
                    // replace by block
                    // clone pointer ownership: delete whole if-stmt and use thenS pointer
                    newstmt = tb;
                    ifs->thenS = nullptr;
                    ifs->elseS = nullptr;
                    delete ifs->cond; // cond is BoolLiteral
                    // replace s
                    s = newstmt;
                    // NOTE: caller must not double-delete thenS (we transferred)
                } else {
                    newstmt = ifs->thenS;
                    ifs->thenS = nullptr;
                    ifs->elseS = nullptr;
                    delete ifs; // cond already deleted inside destructor? destructor deletes cond and thenS/elseS - we moved pointers so careful
                    s = newstmt;
                }
            } else {
                // cond is false -> replace with elseS or empty block
                if (ifs->elseS) {
                    AST::Stmt* newstmt = ifs->elseS;
                    ifs->elseS = nullptr;
                    ifs->thenS = nullptr;
                    delete ifs;
                    s = newstmt;
                } else {
                    // replace with empty block
                    delete ifs;
                    s = new AST::Block();
                }
            }
        }
    } else if (auto* blk = dynamic_cast<AST::Block*>(s)) {
        // walk statements and try simplify nested ifs
        for (auto*& st : blk->stmts) {
            simplifyIf(st);
        }
    }
}

void SemanticAnalyzer::removeUnreachableInBlock(AST::Block* b) {
    if (!b) return;
    std::vector<AST::Stmt*> newstmts;
    bool seenReturn = false;
    for (auto* s : b->stmts) {
        if (seenReturn) {
            // unreachable: free s
            delete s;
            continue;
        }
        newstmts.push_back(s);
        if (dynamic_cast<AST::ReturnStmt*>(s)) seenReturn = true;
        // if we simplified an if into block that contains return at end, this will handle later
    }
    b->stmts = std::move(newstmts);
}
