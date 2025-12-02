#pragma once
#include "ast.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

struct Value {
    enum class Type { Int, Bool, String, Void };
    Type type;
    std::int64_t i;
    bool b;
    std::string s;

    Value() : type(Type::Void), i(0), b(false) {}

    static Value makeInt(std::int64_t v) {
        Value r;
        r.type = Type::Int;
        r.i = v;
        return r;
    }

    static Value makeBool(bool v) {
        Value r;
        r.type = Type::Bool;
        r.b = v;
        return r;
    }

    static Value makeString(const std::string& v) {
        Value r;
        r.type = Type::String;
        r.s = v;
        return r;
    }

    static Value makeVoid() {
        return Value();
    }

    std::string toString() const {
        if (type == Type::Int) return std::to_string(i);
        if (type == Type::Bool) return b ? "true" : "false";
        if (type == Type::String) return s;
        return "";
    }
};

class Interpreter {
public:
    explicit Interpreter(AST::Program* p);
    void run();

private:
    struct Instance {
        AST::ClassDecl* cls;
        std::unordered_map<std::string, Value> fields;
        explicit Instance(AST::ClassDecl* c) : cls(c) {}
    };

    struct Frame {
        Instance* self;
        std::unordered_map<std::string, Value> locals;
        Frame() : self(nullptr) {}
    };

    AST::Program* program;
    std::unordered_map<std::string, AST::ClassDecl*> classes;
    Instance* mainInstance;

    void indexClasses();
    Value evalExpr(AST::Expr* e, Frame& frame);
    void execStmt(AST::Stmt* s, Frame& frame, bool& returned, Value& retVal);
    void execBlock(AST::Block* b, Frame& frame, bool& returned, Value& retVal);
    AST::MethodDecl* findMethod(AST::ClassDecl* c, const std::string& name);
    Value callMethod(Instance* inst, AST::MethodDecl* m, const std::vector<Value>& args);
    Value defaultValueForType(const std::string& typeName);
};
