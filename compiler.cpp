#include "interpreter.hpp"
#include <iostream>

Interpreter::Interpreter(AST::Program* p) : program(p), mainInstance(nullptr) {
    indexClasses();
}

void Interpreter::indexClasses() {
    classes.clear();
    for (auto* c : program->classes) {
        classes[c->name] = c;
    }
}

Value Interpreter::defaultValueForType(const std::string& typeName) {
    if (typeName == "Int") return Value::makeInt(0);
    if (typeName == "Bool") return Value::makeBool(false);
    if (typeName == "String") return Value::makeString("");
    return Value::makeVoid();
}

AST::MethodDecl* Interpreter::findMethod(AST::ClassDecl* c, const std::string& name) {
    for (auto* m : c->methods) {
        if (m->name == name) return m;
    }
    return nullptr;
}

Value Interpreter::evalExpr(AST::Expr* e, Frame& frame) {
    if (!e) return Value::makeVoid();

    if (auto* il = dynamic_cast<AST::IntLiteral*>(e)) {
        return Value::makeInt(il->value);
    }
    if (auto* sl = dynamic_cast<AST::StringLiteral*>(e)) {
        return Value::makeString(sl->value);
    }
    if (auto* bl = dynamic_cast<AST::BoolLiteral*>(e)) {
        return Value::makeBool(bl->value);
    }
    if (auto* id = dynamic_cast<AST::Identifier*>(e)) {
        auto it = frame.locals.find(id->name);
        if (it != frame.locals.end()) return it->second;
        if (frame.self) {
            auto fit = frame.self->fields.find(id->name);
            if (fit != frame.self->fields.end()) return fit->second;
        }
        return Value::makeVoid();
    }
    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        if (bin->op == AST::BinOp::Assign) {
            Value rv = evalExpr(bin->rhs, frame);
            if (auto* lid = dynamic_cast<AST::Identifier*>(bin->lhs)) {
                auto it = frame.locals.find(lid->name);
                if (it != frame.locals.end()) {
                    it->second = rv;
                    return rv;
                }
                if (frame.self) {
                    auto fit = frame.self->fields.find(lid->name);
                    if (fit != frame.self->fields.end()) {
                        fit->second = rv;
                        return rv;
                    }
                    frame.self->fields[lid->name] = rv;
                    return rv;
                }
                frame.locals[lid->name] = rv;
                return rv;
            }
            return rv;
        }
        Value lv = evalExpr(bin->lhs, frame);
        Value rv = evalExpr(bin->rhs, frame);
        if (bin->op == AST::BinOp::Add && lv.type == Value::Type::Int && rv.type == Value::Type::Int) {
            return Value::makeInt(lv.i + rv.i);
        }
        if (bin->op == AST::BinOp::Sub && lv.type == Value::Type::Int && rv.type == Value::Type::Int) {
            return Value::makeInt(lv.i - rv.i);
        }
        if (bin->op == AST::BinOp::Mul && lv.type == Value::Type::Int && rv.type == Value::Type::Int) {
            return Value::makeInt(lv.i * rv.i);
        }
        if (bin->op == AST::BinOp::Div && lv.type == Value::Type::Int && rv.type == Value::Type::Int) {
            if (rv.i == 0) return Value::makeInt(0);
            return Value::makeInt(lv.i / rv.i);
        }
        if (bin->op == AST::BinOp::Gt && lv.type == Value::Type::Int && rv.type == Value::Type::Int) {
            return Value::makeBool(lv.i > rv.i);
        }
        if (bin->op == AST::BinOp::Lt && lv.type == Value::Type::Int && rv.type == Value::Type::Int) {
            return Value::makeBool(lv.i < rv.i);
        }
        if (bin->op == AST::BinOp::Eq) {
            if (lv.type == rv.type) {
                if (lv.type == Value::Type::Int) return Value::makeBool(lv.i == rv.i);
                if (lv.type == Value::Type::Bool) return Value::makeBool(lv.b == rv.b);
                if (lv.type == Value::Type::String) return Value::makeBool(lv.s == rv.s);
            }
            return Value::makeBool(false);
        }
        return Value::makeVoid();
    }
    if (auto* un = dynamic_cast<AST::Unary*>(e)) {
        Value rv = evalExpr(un->rhs, frame);
        if (un->op == AST::Unary::Op::Neg && rv.type == Value::Type::Int) {
            return Value::makeInt(-rv.i);
        }
        return Value::makeVoid();
    }
    if (auto* call = dynamic_cast<AST::Call*>(e)) {
        if (auto* id = dynamic_cast<AST::Identifier*>(call->callee)) {
            if (id->name == "output" || id->name == "print") {
                std::vector<Value> args;
                for (auto* a : call->args) args.push_back(evalExpr(a, frame));
                for (size_t i = 0; i < args.size(); ++i) {
                    if (i > 0) std::cout << " ";
                    std::cout << args[i].toString();
                }
                std::cout << std::endl;
                return Value::makeVoid();
            }
            if (frame.self && frame.self->cls) {
                AST::MethodDecl* m = findMethod(frame.self->cls, id->name);
                if (m) {
                    std::vector<Value> args;
                    for (auto* a : call->args) args.push_back(evalExpr(a, frame));
                    return callMethod(frame.self, m, args);
                }
            }
            return Value::makeVoid();
        }
        return Value::makeVoid();
    }
    if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        Value obj = evalExpr(ma->object, frame);
        return Value::makeVoid();
    }
    if (auto* idx = dynamic_cast<AST::Index*>(e)) {
        Value base = evalExpr(idx->base, frame);
        Value ind = evalExpr(idx->index, frame);
        return Value::makeVoid();
    }
    return Value::makeVoid();
}

void Interpreter::execBlock(AST::Block* b, Frame& frame, bool& returned, Value& retVal) {
    if (!b) return;
    for (auto* s : b->stmts) {
        if (returned) return;
        execStmt(s, frame, returned, retVal);
    }
}

void Interpreter::execStmt(AST::Stmt* s, Frame& frame, bool& returned, Value& retVal) {
    if (!s || returned) return;

    if (auto* ifs = dynamic_cast<AST::IfStmt*>(s)) {
        Value cv = evalExpr(ifs->cond, frame);
        bool cond = false;
        if (cv.type == Value::Type::Bool) cond = cv.b;
        if (cond) {
            execStmt(ifs->thenS, frame, returned, retVal);
        } else {
            execStmt(ifs->elseS, frame, returned, retVal);
        }
        return;
    }
    if (auto* w = dynamic_cast<AST::WhileStmt*>(s)) {
        while (!returned) {
            Value cv = evalExpr(w->cond, frame);
            bool cond = false;
            if (cv.type == Value::Type::Bool) cond = cv.b;
            if (!cond) break;
            if (auto* blk = dynamic_cast<AST::Block*>(w->body)) {
                execBlock(blk, frame, returned, retVal);
            } else {
                execStmt(w->body, frame, returned, retVal);
            }
        }
        return;
    }
    if (auto* ret = dynamic_cast<AST::ReturnStmt*>(s)) {
        retVal = evalExpr(ret->value, frame);
        returned = true;
        return;
    }
    if (auto* es = dynamic_cast<AST::ExprStmt*>(s)) {
        evalExpr(es->expr, frame);
        return;
    }
    if (auto* vds = dynamic_cast<AST::VarDeclStmt*>(s)) {
        if (vds->decl) {
            Value v;
            if (vds->decl->init) v = evalExpr(vds->decl->init, frame);
            else v = defaultValueForType(vds->decl->typeName);
            frame.locals[vds->decl->name] = v;
        }
        return;
    }
    if (auto* blk = dynamic_cast<AST::Block*>(s)) {
        execBlock(blk, frame, returned, retVal);
        return;
    }
}

Value Interpreter::callMethod(Instance* inst, AST::MethodDecl* m, const std::vector<Value>& args) {
    Frame f;
    f.self = inst;
    for (size_t i = 0; i < m->params.size() && i < args.size(); ++i) {
        f.locals[m->params[i]->name] = args[i];
    }
    bool returned = false;
    Value ret = Value::makeVoid();
    if (auto* blk = dynamic_cast<AST::Block*>(m->body)) {
        execBlock(blk, f, returned, ret);
    } else {
        execStmt(m->body, f, returned, ret);
    }
    return ret;
}

void Interpreter::run() {
    auto it = classes.find("Main");
    if (it == classes.end()) return;
    AST::ClassDecl* mainClass = it->second;
    mainInstance = new Instance(mainClass);
    for (auto* f : mainClass->fields) {
        mainInstance->fields[f->name] = defaultValueForType(f->typeName);
    }
    Frame fieldFrame;
    fieldFrame.self = mainInstance;
    for (auto* f : mainClass->fields) {
        if (f->init) {
            Value v = evalExpr(f->init, fieldFrame);
            mainInstance->fields[f->name] = v;
        }
    }
    AST::MethodDecl* mainMethod = findMethod(mainClass, "main");
    if (!mainMethod) {
        delete mainInstance;
        mainInstance = nullptr;
        return;
    }
    std::vector<Value> args;
    callMethod(mainInstance, mainMethod, args);
    delete mainInstance;
    mainInstance = nullptr;
}
