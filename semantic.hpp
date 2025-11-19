#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "ast.hpp"

struct SemanticResult {
    bool ok;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    std::vector<std::string> optimizations;
    void addError(const std::string& s) { errors.push_back(s); ok = false; }
    SemanticResult() : ok(true) {}
};

class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    SemanticResult analyze(AST::Program* p);

private:
    std::unordered_map<std::string, AST::ClassDecl*> classes;

    AST::ClassDecl* curClass = nullptr;
    AST::MethodDecl* curMethod = nullptr;

    std::vector<std::unordered_map<std::string,std::string>> localsStack;

    SemanticResult result;

    void indexClasses(AST::Program* p);
    void analyzeClass(AST::ClassDecl* c);
    void analyzeMethod(AST::MethodDecl* m);
    void analyzeBlock(AST::Block* b);
    void analyzeStmt(AST::Stmt*& s);
    void analyzeExpr(AST::Expr*& e);

    bool foldConstantsInExpr(AST::Expr*& e);
    void simplifyIf(AST::Stmt*& s);
    void removeUnreachableInBlock(AST::Block* b);

    std::string typeOfExpr(AST::Expr* e);
    bool isLiteral(AST::Expr* e);
    void pushScope();
    void popScope();
    void declareLocal(const std::string& name, const std::string& type);

    std::string curPos(AST::Node* n);
};
