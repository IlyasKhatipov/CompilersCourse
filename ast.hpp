#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

namespace AST {

struct Node { virtual ~Node() = default; virtual void print(std::ostream& os, int indent = 0) const = 0; };

inline void doIndent(std::ostream& os, int n) { for (int i = 0; i < n; ++i) os << "  "; }

struct Expr : Node { };

struct IntLiteral : Expr {
    std::int64_t value;
    explicit IntLiteral(std::int64_t v) : value(v) {}
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Int(" << value << ")\n"; }
};

struct StringLiteral : Expr {
    std::string value;
    explicit StringLiteral(std::string v) : value(std::move(v)) {}
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "String(" << value << ")\n"; }
};

struct BoolLiteral : Expr {
    bool value;
    explicit BoolLiteral(bool v) : value(v) {}
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Bool(" << (value ? "true" : "false") << ")\n"; }
};

struct Identifier : Expr {
    std::string name;
    explicit Identifier(std::string n) : name(std::move(n)) {}
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Id(" << name << ")\n"; }
};

enum class BinOp { Add, Sub, Mul, Div, Assign, Gt, Lt, Eq };

struct Binary : Expr {
    BinOp op; Expr* lhs; Expr* rhs;
    Binary(BinOp o, Expr* l, Expr* r) : op(o), lhs(l), rhs(r) {}
    ~Binary() { delete lhs; delete rhs; }
    static const char* opToStr(BinOp o) {
        switch (o) { case BinOp::Add: return "+"; case BinOp::Sub: return "-"; case BinOp::Mul: return "*"; case BinOp::Div: return "/"; case BinOp::Assign: return ":="; case BinOp::Gt: return ">"; case BinOp::Lt: return "<"; case BinOp::Eq: return "=="; }
        return "?";
    }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "BinOp(" << opToStr(op) << ")\n"; lhs->print(os, indent + 1); rhs->print(os, indent + 1); }
};

struct Unary : Expr {
    enum class Op { Neg }; Op op; Expr* rhs;
    Unary(Op o, Expr* e) : op(o), rhs(e) {}
    ~Unary() { delete rhs; }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Unary(-)\n"; rhs->print(os, indent + 1); }
};

struct MemberAccess : Expr {
    Expr* object; std::string member;
    MemberAccess(Expr* o, std::string m) : object(o), member(std::move(m)) {}
    ~MemberAccess() { delete object; }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Member\n"; object->print(os, indent + 1); doIndent(os, indent + 1); os << member << "\n"; }
};

struct Index : Expr {
    Expr* base; Expr* index;
    Index(Expr* b, Expr* i) : base(b), index(i) {}
    ~Index() { delete base; delete index; }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Index\n"; base->print(os, indent + 1); index->print(os, indent + 1); }
};

struct Call : Expr {
    Expr* callee; std::vector<Expr*> args;
    explicit Call(Expr* c) : callee(c) {}
    ~Call() { delete callee; for (auto* a : args) delete a; }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Call\n"; callee->print(os, indent + 1); for (auto* a : args) a->print(os, indent + 1); }
};

struct Stmt : Node { };

struct ExprStmt : Stmt {
    Expr* expr;
    explicit ExprStmt(Expr* e) : expr(e) {}
    ~ExprStmt() { delete expr; }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "expr\n"; expr->print(os, indent + 1); }
};

struct ReturnStmt : Stmt {
    Expr* value;
    explicit ReturnStmt(Expr* v) : value(v) {}
    ~ReturnStmt() { delete value; }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "return\n";
        if (value) value->print(os, indent + 1);
    }
};


struct IfStmt : Stmt {
    Expr* cond; Stmt* thenS; Stmt* elseS;
    IfStmt(Expr* c, Stmt* t, Stmt* e) : cond(c), thenS(t), elseS(e) {}
    ~IfStmt() { delete cond; delete thenS; delete elseS; }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "if\n"; cond->print(os, indent + 1); doIndent(os, indent); os << "then\n"; thenS->print(os, indent + 1); doIndent(os, indent); os << "else\n"; elseS->print(os, indent + 1); }
};

struct WhileStmt : Stmt {
    Expr* cond; Stmt* body;
    WhileStmt(Expr* c, Stmt* b) : cond(c), body(b) {}
    ~WhileStmt() { delete cond; delete body; }
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "while\n"; cond->print(os, indent + 1); body->print(os, indent + 1); }
};

struct Block : Stmt {
    std::vector<Stmt*> stmts;
    ~Block() { for (auto* s : stmts) delete s; }
    void print(std::ostream& os, int indent) const override { for (auto* s : stmts) s->print(os, indent); }
};

struct VarDecl : Node {
    std::string name; std::string typeName; Expr* init;
    VarDecl(std::string n, std::string t, Expr* i) : name(std::move(n)), typeName(std::move(t)), init(i) {}
    ~VarDecl() { delete init; }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "var " << name << " : " << typeName;
        if (init) { os << " =\n"; init->print(os, indent + 1); }
        else { os << "\n"; }
    }
};

struct VarDeclStmt : Stmt {
    VarDecl* decl;
    explicit VarDeclStmt(VarDecl* d) : decl(d) {}
    ~VarDeclStmt() { delete decl; }
    void print(std::ostream& os, int indent) const override { decl->print(os, indent); }
};

struct Param { std::string name; std::string typeName; Param(std::string n, std::string t) : name(std::move(n)), typeName(std::move(t)) {} };

struct MethodDecl : Node {
    std::string name; std::vector<Param*> params; std::string returnType; Stmt* body;
    MethodDecl(std::string n, std::string rt, Stmt* b) : name(std::move(n)), returnType(std::move(rt)), body(b) {}
    ~MethodDecl() { for (auto* p : params) delete p; delete body; }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "method " << name << "(";
        for (size_t i = 0; i < params.size(); ++i) { os << params[i]->name << " : " << params[i]->typeName; if (i + 1 < params.size()) os << ", "; }
        os << ") : " << returnType << "\n";
        if (body) body->print(os, indent + 1);
    }
};

struct ClassDecl : Node {
    std::string name; std::vector<VarDecl*> fields; std::vector<MethodDecl*> methods;
    explicit ClassDecl(std::string n) : name(std::move(n)) {}
    ~ClassDecl() { for (auto* v : fields) delete v; for (auto* m : methods) delete m; }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "Class: " << name << "\n";
        for (auto* v : fields) v->print(os, indent + 1);
        for (auto* m : methods) m->print(os, indent + 1);
    }
};

struct Program : Node {
    std::vector<ClassDecl*> classes;
    ~Program() { for (auto* c : classes) delete c; }
    void print(std::ostream& os, int indent = 0) const override { for (auto* c : classes) c->print(os, indent); }
};

}
