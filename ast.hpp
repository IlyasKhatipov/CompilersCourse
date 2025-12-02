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

struct RealLiteral : Expr {
    double value;
    explicit RealLiteral(double v) : value(v) {}
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Real(" << value << ")\n"; }
};

struct BoolLiteral : Expr {
    bool value;
    explicit BoolLiteral(bool v) : value(v) {}
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Bool(" << (value ? "true" : "false") << ")\n"; }
};

struct ThisLiteral : Expr {
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "this\n"; }
};

struct Identifier : Expr {
    std::string name;
    explicit Identifier(std::string n) : name(std::move(n)) {}
    void print(std::ostream& os, int indent) const override { doIndent(os, indent); os << "Id(" << name << ")\n"; }
};

struct MemberAccess : Expr {
    Expr* object;
    std::string member;
    MemberAccess(Expr* o, std::string m) : object(o), member(std::move(m)) {}
    ~MemberAccess() { delete object; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "MemberAccess\n";
        object->print(os, indent + 1);
        doIndent(os, indent + 1); os << member << "\n";
    }
};

struct MethodCall : Expr {
    Expr* object;
    std::string methodName;
    std::vector<Expr*> args;
    MethodCall(Expr* o, std::string m, std::vector<Expr*>* a) : object(o), methodName(std::move(m)) {
        if (a) { args = std::move(*a); delete a; }
    }
    ~MethodCall() {
        delete object;
        for (auto* a : args) delete a;
    }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "MethodCall: " << methodName << "\n";
        object->print(os, indent + 1);
        for (auto* a : args) a->print(os, indent + 1);
    }
};

struct ConstructorCall : Expr {
    std::string className;
    std::vector<Expr*> args;
    ConstructorCall(std::string c, std::vector<Expr*>* a) : className(std::move(c)) {
        if (a) { args = std::move(*a); delete a; }
    }
    ~ConstructorCall() { for (auto* a : args) delete a; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "ConstructorCall: " << className << "\n";
        for (auto* a : args) a->print(os, indent + 1);
    }
};

struct Stmt : Node { };

struct ExprStmt : Stmt {
    Expr* expr;
    explicit ExprStmt(Expr* e) : expr(e) {}
    ~ExprStmt() { delete expr; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "ExprStmt\n";
        expr->print(os, indent + 1);
    }
};

struct AssignmentStmt : Stmt {
    std::string varName;
    Expr* value;
    AssignmentStmt(std::string v, Expr* val) : varName(std::move(v)), value(val) {}
    ~AssignmentStmt() { delete value; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "Assignment: " << varName << "\n";
        value->print(os, indent + 1);
    }
};

struct ReturnStmt : Stmt {
    Expr* value;
    explicit ReturnStmt(Expr* v = nullptr) : value(v) {}
    ~ReturnStmt() { delete value; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "Return\n";
        if (value) value->print(os, indent + 1);
    }
};

struct IfStmt : Stmt {
    Expr* cond;
    Stmt* thenStmt;
    Stmt* elseStmt;
    IfStmt(Expr* c, Stmt* t, Stmt* e = nullptr) : cond(c), thenStmt(t), elseStmt(e) {}
    ~IfStmt() { delete cond; delete thenStmt; delete elseStmt; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "If\n";
        cond->print(os, indent + 1);
        doIndent(os, indent); os << "Then\n";
        thenStmt->print(os, indent + 1);
        if (elseStmt) {
            doIndent(os, indent); os << "Else\n";
            elseStmt->print(os, indent + 1);
        }
    }
};

struct WhileStmt : Stmt {
    Expr* cond;
    Stmt* body;
    WhileStmt(Expr* c, Stmt* b) : cond(c), body(b) {}
    ~WhileStmt() { delete cond; delete body; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "While\n";
        cond->print(os, indent + 1);
        body->print(os, indent + 1);
    }
};

struct Block : Stmt {
    std::vector<Stmt*> stmts;
    ~Block() { for (auto* s : stmts) delete s; }
    void print(std::ostream& os, int indent) const override { 
        for (auto* s : stmts) s->print(os, indent);
    }
};

struct VarDecl : Node {
    std::string name;
    Expr* initializer;
    VarDecl(std::string n, Expr* init) : name(std::move(n)), initializer(init) {}
    ~VarDecl() { delete initializer; }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "VarDecl: " << name << "\n";
        if (initializer) initializer->print(os, indent + 1);
    }
};

struct VarDeclStmt : Stmt {
    VarDecl* decl;
    explicit VarDeclStmt(VarDecl* d) : decl(d) {}
    ~VarDeclStmt() { delete decl; }
    void print(std::ostream& os, int indent) const override { 
        decl->print(os, indent);
    }
};

struct Param { 
    std::string name;
    std::string typeName;
    Param(std::string n, std::string t) : name(std::move(n)), typeName(std::move(t)) {}
};

struct MethodDecl : Node {
    std::string name;
    std::vector<Param*> params;
    std::string returnType;
    Stmt* body;  // может быть nullptr для forward declaration
    MethodDecl(std::string n, std::string rt, Stmt* b) : name(std::move(n)), returnType(std::move(rt)), body(b) {}
    ~MethodDecl() { 
        for (auto* p : params) delete p;
        delete body;
    }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "Method: " << name << " : " << returnType << "\n";
        for (auto* p : params) {
            doIndent(os, indent + 1); os << p->name << " : " << p->typeName << "\n";
        }
        if (body) body->print(os, indent + 1);
    }
};

struct ConstructorDecl : Node {
    std::vector<Param*> params;
    Block* body;
    ConstructorDecl(std::vector<Param*>* p = nullptr) : body(nullptr) {
        if (p) { params = std::move(*p); delete p; }
    }
    ~ConstructorDecl() { 
        for (auto* p : params) delete p;
        delete body;
    }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "Constructor\n";
        for (auto* p : params) {
            doIndent(os, indent + 1); os << p->name << " : " << p->typeName << "\n";
        }
        if (body) body->print(os, indent + 1);
    }
};

struct ClassDecl : Node {
    std::string name;
    std::string baseClass;
    std::vector<VarDecl*> fields;
    std::vector<ConstructorDecl*> constructors;
    std::vector<MethodDecl*> methods;
    ClassDecl(std::string n, char* base = nullptr) : name(std::move(n)), baseClass(base ? base : "") {
        if (base) free(base);
    }
    ~ClassDecl() { 
        for (auto* v : fields) delete v;
        for (auto* c : constructors) delete c;
        for (auto* m : methods) delete m;
    }
    void print(std::ostream& os, int indent) const override { 
        doIndent(os, indent); os << "Class: " << name;
        if (!baseClass.empty()) os << " extends " << baseClass;
        os << "\n";
        for (auto* v : fields) v->print(os, indent + 1);
        for (auto* c : constructors) c->print(os, indent + 1);
        for (auto* m : methods) m->print(os, indent + 1);
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