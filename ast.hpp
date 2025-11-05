#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

namespace AST {

struct Node {
    virtual ~Node() = default;
    virtual void print(std::ostream& os, int indent = 0) const = 0;
};

inline void doIndent(std::ostream& os, int n) {
    for (int i = 0; i < n; ++i) os << "  ";
}

struct Expr : Node { };

struct IntLiteral : Expr {
    std::int64_t value;
    explicit IntLiteral(std::int64_t v) : value(v) {}
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent); os << "Int(" << value << ")\n";
    }
};

struct Identifier : Expr {
    std::string name;
    explicit Identifier(std::string n) : name(std::move(n)) {}
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent); os << "Id(" << name << ")\n";
    }
};

enum class BinOp { Add, Sub, Mul, Div, Assign };

struct Binary : Expr {
    BinOp op;
    Expr* lhs;
    Expr* rhs;
    Binary(BinOp o, Expr* l, Expr* r) : op(o), lhs(l), rhs(r) {}
    ~Binary() { delete lhs; delete rhs; }
    static const char* opToStr(BinOp o) {
        switch (o) {
            case BinOp::Add: return "+";
            case BinOp::Sub: return "-";
            case BinOp::Mul: return "*";
            case BinOp::Div: return "/";
            case BinOp::Assign: return "=";
        }
        return "?";
    }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "BinOp(" << opToStr(op) << ")\n";
        lhs->print(os, indent + 1);
        rhs->print(os, indent + 1);
    }
};

struct Unary : Expr {
    enum class Op { Neg };
    Op op;
    Expr* rhs;
    Unary(Op o, Expr* e) : op(o), rhs(e) {}
    ~Unary() { delete rhs; }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "Unary(-)\n";
        rhs->print(os, indent + 1);
    }
};

struct VarDecl : Node {
    std::string name;
    std::string typeName;
    Expr* init;
    VarDecl(std::string n, std::string t, Expr* i)
        : name(std::move(n)), typeName(std::move(t)), init(i) {}
    ~VarDecl() { delete init; }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "var " << name << " : " << typeName;
        if (init) {
            os << " =\n";
            init->print(os, indent + 1);
        } else {
            os << "\n";
        }
    }
};

struct ClassDecl : Node {
    std::string name;
    std::vector<VarDecl*> fields;
    explicit ClassDecl(std::string n) : name(std::move(n)) {}
    ~ClassDecl() { for (auto* v : fields) delete v; }
    void print(std::ostream& os, int indent) const override {
        doIndent(os, indent);
        os << "Class: " << name << "\n";
        for (auto* v : fields) v->print(os, indent + 1);
    }
};

struct Program : Node {
    std::vector<ClassDecl*> classes;
    ~Program() { for (auto* c : classes) delete c; }
    void print(std::ostream& os, int indent = 0) const override {
        for (auto* c : classes) c->print(os, indent);
    }
};

}
