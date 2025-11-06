#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "ast.hpp"

struct SemanticResult {
    bool ok = true;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;       
    std::vector<std::string> optimizations;  

    void addError(const std::string& msg) { ok = false; errors.push_back(msg); }
    void addWarning(const std::string& msg) { warnings.push_back(msg); }        
    void addOptimization(const std::string& msg) { optimizations.push_back(msg); } 
};

class SemanticAnalyzer {
public:
    SemanticAnalyzer();
    SemanticResult analyze(AST::Program* p);

private:
    // class name -> pointer
    std::unordered_map<std::string, AST::ClassDecl*> classes;

    // state while traversing
    AST::ClassDecl* curClass = nullptr;
    AST::MethodDecl* curMethod = nullptr;

    // locals: name -> type
    std::vector<std::unordered_map<std::string,std::string>> localsStack;

    SemanticResult result;

    // helpers
    void indexClasses(AST::Program* p);
    void analyzeClass(AST::ClassDecl* c);
    void analyzeMethod(AST::MethodDecl* m);
    void analyzeBlock(AST::Block* b);
    void analyzeStmt(AST::Stmt*& s);
    void analyzeExpr(AST::Expr*& e);

    // optimizations
    bool foldConstantsInExpr(AST::Expr*& e); // returns true if replaced/changed
    void simplifyIf(AST::Stmt*& s);
    void removeUnreachableInBlock(AST::Block* b);

    // types
    std::string typeOfExpr(AST::Expr* e);
    bool isLiteral(AST::Expr* e);
    void pushScope();
    void popScope();
    void declareLocal(const std::string& name, const std::string& type);

    // utilities
    std::string curPos(AST::Node* n);
};
