// ast.hpp
#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

namespace AST {

struct Node { virtual ~Node() = default; };

struct TypeName : Node {
    std::string name;
    explicit TypeName(std::string n) : name(std::move(n)) {}
};

struct Expr : Node { virtual void print(std::ostream& os) const = 0; };

struct IntLiteral : Expr {
    long long value;
    explicit IntLiteral(long long v) : value(v) {}
    void print(std::ostream& os) const override { os << value; }
};

struct IdExpr : Expr {
    std::string name;
    explicit IdExpr(std::string n) : name(std::move(n)) {}
    void print(std::ostream& os) const override { os << name; }
};

struct BinExpr : Expr {
    char op;
    std::unique_ptr<Expr> lhs, rhs;
    BinExpr(char op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(op), lhs(std::move(l)), rhs(std::move(r)) {}
    void print(std::ostream& os) const override {
        lhs->print(os); os << " " << op << " "; rhs->print(os);
    }
};

struct VarDecl : Node {
    std::string name;
    std::unique_ptr<TypeName> type;
    std::unique_ptr<Expr> init; // опционально
    VarDecl(std::string n, std::unique_ptr<TypeName> t, std::unique_ptr<Expr> i = {})
        : name(std::move(n)), type(std::move(t)), init(std::move(i)) {}
};

struct ClassDecl : Node {
    std::string name;
    std::vector<std::unique_ptr<VarDecl>> fields;
    explicit ClassDecl(std::string n) : name(std::move(n)) {}
};

struct Program : Node {
    std::vector<std::unique_ptr<ClassDecl>> classes;
    void printNormalized(std::ostream& os) const {
        for (auto& c : classes) {
            os << "Class: " << c->name << "\n";
            for (auto& v : c->fields) {
                os << "var " << v->name << " : " << v->type->name;
                if (v->init) {
                    os << " = ";
                    v->init->print(os);
                }
                os << "\n";
            }
        }
    }
};

} // namespace AST
