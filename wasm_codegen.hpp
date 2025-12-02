#pragma once
#include "ast.hpp"
#include "semantic.hpp"
#include <ostream>
#include <string>
#include <unordered_map>

class WasmGenerator {
public:
    WasmGenerator(AST::Program* prog, const SemanticResult& sem);
    void generateToWat(std::ostream& os, const std::string& entryClass);

private:
    AST::Program* program;
    const SemanticResult& semantic;
    std::unordered_map<std::string, AST::ClassDecl*> classes;
    int labelCounter;

    void indexClasses();
    void emitModuleHeader(std::ostream& os);
    void emitModuleFooter(std::ostream& os);
    AST::ClassDecl* findClass(const std::string& name);
    AST::CtorDecl* findDefaultCtor(AST::ClassDecl* c);

    void emitCtorAsMain(std::ostream& os, AST::ClassDecl* c, AST::CtorDecl* ctor);

    void collectLocals(AST::Stmt* s, std::unordered_map<std::string, bool>& locals);
    void emitLocals(std::ostream& os, const std::unordered_map<std::string, bool>& locals);

    void emitStmt(std::ostream& os, AST::Stmt* s, const std::unordered_map<std::string, bool>& locals);
    void emitBlock(std::ostream& os, AST::Block* b, const std::unordered_map<std::string, bool>& locals);
    void emitExpr(std::ostream& os, AST::Expr* e, const std::unordered_map<std::string, bool>& locals);

    int nextLabelId();
};
