#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void print(int indent=0) const = 0;
};

using ASTNodePtr = unique_ptr<ASTNode>;

static string indentStr(int n) { return string(n, ' '); }

struct ProgramNode : ASTNode {
    vector<ASTNodePtr> decls;
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Program\n";
        for (auto &d : decls) d->print(indent+2);
    }
};

struct ClassNode : ASTNode {
    string name;
    string extendsName;
    vector<ASTNodePtr> members;
    ClassNode(const string &n="") : name(n) {}
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Class: " << name;
        if (!extendsName.empty()) cout << " extends " << extendsName;
        cout << "\n";
        for (auto &m : members) m->print(indent+2);
    }
};

struct VarNode : ASTNode {
    string name;
    string type;
    VarNode(const string &n="", const string &t="") : name(n), type(t) {}
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Var: " << name;
        if (!type.empty()) cout << " : " << type;
        cout << "\n";
    }
};

struct MethodNode : ASTNode {
    string name;
    vector<string> params;
    vector<ASTNodePtr> body;
    MethodNode(const string &n="") : name(n) {}
    void print(int indent=0) const override {
        cout << indentStr(indent) << "Method: " << name << "\n";
        for (auto &b : body) b->print(indent+2);
    }
};

extern unique_ptr<ProgramNode> g_program;

struct SimpleToken {
    string kind;
    string text;
    int line;
    int startCol;
    int endCol;

    SimpleToken() = default;
    SimpleToken(const string& k, const string& t, int l, int sc, int ec)
        : kind(k), text(t), line(l), startCol(sc), endCol(ec) {}
};
extern std::vector<SimpleToken> simpleTokens;

extern size_t parserTokIndex;

void yyerror(const char *s);
int yylex();
void printAST();

#endif // AST_H
