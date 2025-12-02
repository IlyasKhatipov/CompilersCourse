#include "wasm_codegen.hpp"
#include <sstream>

WasmGenerator::WasmGenerator(AST::Program* prog, const SemanticResult& sem)
    : program(prog), semantic(sem), labelCounter(0) {
    indexClasses();
}

void WasmGenerator::indexClasses() {
    classes.clear();
    if (!program) return;
    for (auto* c : program->classes) {
        classes[c->name] = c;
    }
}

AST::ClassDecl* WasmGenerator::findClass(const std::string& name) {
    auto it = classes.find(name);
    if (it == classes.end()) return nullptr;
    return it->second;
}

AST::CtorDecl* WasmGenerator::findDefaultCtor(AST::ClassDecl* c) {
    if (!c) return nullptr;
    for (auto* ct : c->ctors) {
        if (ct->params.empty()) return ct;
    }
    return nullptr;
}

int WasmGenerator::nextLabelId() {
    int v = labelCounter;
    labelCounter += 1;
    return v;
}

void WasmGenerator::emitModuleHeader(std::ostream& os) {
    os << "(module\n";
    os << "  (import \"env\" \"print_i32\" (func $print_i32 (param i32)))\n";
}

void WasmGenerator::emitModuleFooter(std::ostream& os) {
    os << ")\n";
}

void WasmGenerator::collectLocals(AST::Stmt* s, std::unordered_map<std::string, bool>& locals) {
    if (!s) return;
    if (auto* vds = dynamic_cast<AST::VarDeclStmt*>(s)) {
        if (vds->decl) {
            locals[vds->decl->name] = true;
        }
        return;
    }
    if (auto* blk = dynamic_cast<AST::Block*>(s)) {
        for (auto* st : blk->stmts) collectLocals(st, locals);
        return;
    }
    if (auto* ifs = dynamic_cast<AST::IfStmt*>(s)) {
        collectLocals(ifs->thenS, locals);
        collectLocals(ifs->elseS, locals);
        return;
    }
    if (auto* w = dynamic_cast<AST::WhileStmt*>(s)) {
        if (auto* b = dynamic_cast<AST::Block*>(w->body)) {
            collectLocals(b, locals);
        } else {
            collectLocals(w->body, locals);
        }
        return;
    }
}

void WasmGenerator::emitLocals(std::ostream& os, const std::unordered_map<std::string, bool>& locals) {
    for (const auto& kv : locals) {
        os << "    (local $" << kv.first << " i32)\n";
    }
}

void WasmGenerator::emitExpr(std::ostream& os, AST::Expr* e, const std::unordered_map<std::string, bool>& locals) {
    if (!e) return;
    if (auto* il = dynamic_cast<AST::IntLiteral*>(e)) {
        os << "    i32.const " << il->value << "\n";
        return;
    }
    if (auto* bl = dynamic_cast<AST::BoolLiteral*>(e)) {
        os << "    i32.const " << (bl->value ? 1 : 0) << "\n";
        return;
    }
    if (auto* id = dynamic_cast<AST::Identifier*>(e)) {
        auto it = locals.find(id->name);
        if (it != locals.end()) {
            os << "    local.get $" << id->name << "\n";
        } else {
            os << "    i32.const 0\n";
        }
        return;
    }
    if (auto* bin = dynamic_cast<AST::Binary*>(e)) {
        if (bin->op == AST::BinOp::Assign) {
            if (auto* lid = dynamic_cast<AST::Identifier*>(bin->lhs)) {
                emitExpr(os, bin->rhs, locals);
                auto it = locals.find(lid->name);
                if (it != locals.end()) {
                    os << "    local.set $" << lid->name << "\n";
                } else {
                    os << "    drop\n";
                }
                os << "    i32.const 0\n";
                return;
            }
        }
        emitExpr(os, bin->lhs, locals);
        emitExpr(os, bin->rhs, locals);
        if (bin->op == AST::BinOp::Add) {
            os << "    i32.add\n";
        } else if (bin->op == AST::BinOp::Sub) {
            os << "    i32.sub\n";
        } else if (bin->op == AST::BinOp::Mul) {
            os << "    i32.mul\n";
        } else if (bin->op == AST::BinOp::Div) {
            os << "    i32.div_s\n";
        } else if (bin->op == AST::BinOp::Gt) {
            os << "    i32.gt_s\n";
        } else if (bin->op == AST::BinOp::Lt) {
            os << "    i32.lt_s\n";
        } else if (bin->op == AST::BinOp::Eq) {
            os << "    i32.eq\n";
        }
        return;
    }
    if (auto* call = dynamic_cast<AST::Call*>(e)) {
        if (auto* id = dynamic_cast<AST::Identifier*>(call->callee)) {
            if (id->name == "output" || id->name == "print") {
                if (!call->args.empty()) {
                    emitExpr(os, call->args[0], locals);
                } else {
                    os << "    i32.const 0\n";
                }
                os << "    call $print_i32\n";
                os << "    i32.const 0\n";
                return;
            }
        }
        if (auto* ma = dynamic_cast<AST::MemberAccess*>(call->callee)) {
            if (auto* objId = dynamic_cast<AST::Identifier*>(ma->object)) {
                if (ma->member == "Plus" || ma->member == "Minus" || ma->member == "Mult" || ma->member == "Div" || ma->member == "Rem") {
                    emitExpr(os, ma->object, locals);
                    if (!call->args.empty()) emitExpr(os, call->args[0], locals);
                    if (ma->member == "Plus") os << "    i32.add\n";
                    else if (ma->member == "Minus") os << "    i32.sub\n";
                    else if (ma->member == "Mult") os << "    i32.mul\n";
                    else if (ma->member == "Div") os << "    i32.div_s\n";
                    else if (ma->member == "Rem") os << "    i32.rem_s\n";
                    return;
                }
                if (ma->member == "Less" || ma->member == "LessEqual" || ma->member == "Greater" || ma->member == "GreaterEqual" || ma->member == "Equal") {
                    emitExpr(os, ma->object, locals);
                    if (!call->args.empty()) emitExpr(os, call->args[0], locals);
                    if (ma->member == "Less") os << "    i32.lt_s\n";
                    else if (ma->member == "LessEqual") {
                        os << "    i32.gt_s\n";
                        os << "    i32.eqz\n";
                    } else if (ma->member == "Greater") os << "    i32.gt_s\n";
                    else if (ma->member == "GreaterEqual") {
                        os << "    i32.lt_s\n";
                        os << "    i32.eqz\n";
                    } else if (ma->member == "Equal") os << "    i32.eq\n";
                    return;
                }
            }
        }
        os << "    i32.const 0\n";
        return;
    }
    if (auto* ma = dynamic_cast<AST::MemberAccess*>(e)) {
        emitExpr(os, ma->object, locals);
        return;
    }
}

void WasmGenerator::emitBlock(std::ostream& os, AST::Block* b, const std::unordered_map<std::string, bool>& locals) {
    if (!b) return;
    for (auto* s : b->stmts) emitStmt(os, s, locals);
}

void WasmGenerator::emitStmt(std::ostream& os, AST::Stmt* s, const std::unordered_map<std::string, bool>& locals) {
    if (!s) return;
    if (auto* blk = dynamic_cast<AST::Block*>(s)) {
        emitBlock(os, blk, locals);
        return;
    }
    if (auto* vds = dynamic_cast<AST::VarDeclStmt*>(s)) {
        if (vds->decl && vds->decl->init) {
            auto it = locals.find(vds->decl->name);
            emitExpr(os, vds->decl->init, locals);
            if (it != locals.end()) {
                os << "    local.set $" << vds->decl->name << "\n";
            } else {
                os << "    drop\n";
            }
        }
        return;
    }
    if (auto* es = dynamic_cast<AST::ExprStmt*>(s)) {
        if (auto* bin = dynamic_cast<AST::Binary*>(es->expr)) {
            if (bin->op == AST::BinOp::Assign) {
                emitExpr(os, es->expr, locals);
                os << "    drop\n";
                return;
            }
        }
        emitExpr(os, es->expr, locals);
        os << "    drop\n";
        return;
    }
    if (auto* ifs = dynamic_cast<AST::IfStmt*>(s)) {
        emitExpr(os, ifs->cond, locals);
        os << "    if\n";
        emitStmt(os, ifs->thenS, locals);
        os << "    else\n";
        emitStmt(os, ifs->elseS, locals);
        os << "    end\n";
        return;
    }
    if (auto* w = dynamic_cast<AST::WhileStmt*>(s)) {
        int lid = nextLabelId();
        os << "    block $while" << lid << "\n";
        os << "      loop $loop" << lid << "\n";
        emitExpr(os, w->cond, locals);
        os << "        i32.eqz\n";
        os << "        br_if $while" << lid << "\n";
        emitStmt(os, w->body, locals);
        os << "        br $loop" << lid << "\n";
        os << "      end\n";
        os << "    end\n";
        return;
    }
    if (auto* ret = dynamic_cast<AST::ReturnStmt*>(s)) {
        if (ret->value) {
            emitExpr(os, ret->value, locals);
            os << "    drop\n";
        }
        os << "    return\n";
        return;
    }
}

void WasmGenerator::emitCtorAsMain(std::ostream& os, AST::ClassDecl* c, AST::CtorDecl* ctor) {
    std::unordered_map<std::string, bool> locals;
    if (ctor && ctor->body) collectLocals(ctor->body, locals);
    os << "  (func $main (export \"_start\")\n";
    emitLocals(os, locals);
    if (ctor && ctor->body) {
        if (auto* blk = dynamic_cast<AST::Block*>(ctor->body)) {
            emitBlock(os, blk, locals);
        } else {
            emitStmt(os, ctor->body, locals);
        }
    }
    os << "  )\n";
}

void WasmGenerator::generateToWat(std::ostream& os, const std::string& entryClass) {
    emitModuleHeader(os);
    AST::ClassDecl* c = findClass(entryClass);
    AST::CtorDecl* ctor = findDefaultCtor(c);
    emitCtorAsMain(os, c, ctor);
    emitModuleFooter(os);
}
