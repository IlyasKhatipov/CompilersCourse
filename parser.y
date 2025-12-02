%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include "ast.hpp"
#include "tokens.hpp"

extern int yylex(void);
extern int yylineno;
void yyerror(const char* s);

AST::Program* g_program = nullptr;
%}

%code requires {
  #include <vector>
  namespace AST {
    struct Node; struct Program; struct ClassDecl; struct VarDecl; struct Expr; struct Stmt; 
    struct MethodDecl; struct ConstructorDecl; struct Param; struct Block; struct ReturnStmt;
    struct VarDeclStmt; struct AssignmentStmt; struct ExprStmt; struct IfStmt; struct WhileStmt;
    struct MemberAccess; struct MethodCall; struct ConstructorCall; struct IntLiteral;
    struct RealLiteral; struct BoolLiteral; struct Identifier; struct ThisLiteral;
  }
}

%defines "parser.hpp"
%define parse.error verbose

%union {
    long long                        ival;
    double                           dval;
    char*                            cstr;
    AST::Program*                    program;
    AST::ClassDecl*                  classdecl;
    AST::VarDecl*                    vardecl;
    AST::Expr*                       expr;
    AST::Stmt*                       stmt;
    AST::MethodDecl*                 methoddecl;
    AST::ConstructorDecl*            constructor;
    AST::Param*                      param;
    AST::Block*                      block;
    AST::Node*                       node;
    std::vector<AST::ClassDecl*>*    classlist;
    std::vector<AST::Node*>*         memberlist;
    std::vector<AST::VarDecl*>*      varlist;
    std::vector<AST::Param*>*        paramlist;
    std::vector<AST::Stmt*>*         stmtlist;
    std::vector<AST::Expr*>*         exprlist;
}

%token CLASS EXTENDS IS END
%token VAR METHOD THIS
%token WHILE LOOP IF THEN ELSE
%token RETURN
%token TRUE FALSE NEW

%token <cstr> IDENTIFIER
%token <ival> INTEGER_LITERAL
%token <dval> REAL_LITERAL

%token ASSIGN ARROW COLON COMMA DOT
%token LPAREN RPAREN LBRACKET RBRACKET

%type  <program>   program
%type  <classlist> class_list
%type  <classdecl> class_decl
%type  <memberlist> class_body member_list
%type  <node>      member
%type  <vardecl>   var_decl
%type  <methoddecl> method_decl
%type  <constructor> constructor_decl
%type  <paramlist> param_list opt_params
%type  <param>     param
%type  <stmt>      stmt simple_stmt if_stmt while_stmt return_stmt method_body
%type  <block>     body opt_else
%type  <stmtlist>  stmt_list
%type  <expr>      expr primary_expr opt_expr
%type  <exprlist>  arg_list opt_args
%type  <cstr>      opt_extends opt_return_type

%left DOT
%left LPAREN RPAREN

%%

program
    : class_list
      {
        g_program = new AST::Program();
        for (auto* c : *$1) g_program->classes.push_back(c);
        delete $1;
      }
    | /* empty */
      { g_program = new AST::Program(); }
    ;

class_list
    : class_list class_decl { $$ = $1; $1->push_back($2); }
    | class_decl            { $$ = new std::vector<AST::ClassDecl*>(); $$->push_back($1); }
    ;

class_decl
    : CLASS IDENTIFIER opt_extends IS class_body END
      {
        $$ = new AST::ClassDecl($2, $3);
        for (auto* n : *$5) {
          if (auto* v = dynamic_cast<AST::VarDecl*>(n)) $$->fields.push_back(v);
          else if (auto* m = dynamic_cast<AST::MethodDecl*>(n)) $$->methods.push_back(m);
          else if (auto* c = dynamic_cast<AST::ConstructorDecl*>(n)) $$->constructors.push_back(c);
          else delete n;
        }
        free($2);
        delete $5;
      }
    ;

opt_extends
    : EXTENDS IDENTIFIER { $$ = strdup($2); free($2); }
    | /* empty */        { $$ = nullptr; }
    ;

class_body
    : member_list { $$ = $1; }
    | /* empty */ { $$ = new std::vector<AST::Node*>(); }
    ;

member_list
    : member_list member { $$ = $1; $1->push_back($2); }
    | member             { $$ = new std::vector<AST::Node*>(); $$->push_back($1); }
    ;

member
    : var_decl         { $$ = $1; }
    | method_decl      { $$ = $1; }
    | constructor_decl { $$ = $1; }
    ;

var_decl
    : VAR IDENTIFIER COLON expr
      { $$ = new AST::VarDecl($2, $4); free($2); }
    ;

method_decl
    : METHOD IDENTIFIER LPAREN opt_params RPAREN opt_return_type method_body
      {
        // Создаем строку возвращаемого типа
        std::string returnType = $6 ? std::string($6) : "";
        $$ = new AST::MethodDecl($2, returnType, $7);
        if ($4) {
          for (auto* p : *$4) $$->params.push_back(p);
          delete $4;
        }
        free($2);
        if ($6) free($6);
      }
    ;

opt_return_type
    : COLON IDENTIFIER { $$ = strdup($2); free($2); }
    | /* empty */      { $$ = nullptr; }
    ;

method_body
    : IS body END
      { $$ = $2; }
    | ARROW expr
      { 
        auto* returnStmt = new AST::ReturnStmt($2);
        auto* block = new AST::Block();
        block->stmts.push_back(returnStmt);
        $$ = block;
      }
    | /* empty */  // forward declaration
      { $$ = nullptr; }
    ;

constructor_decl
    : THIS LPAREN opt_params RPAREN IS body END
      {
        $$ = new AST::ConstructorDecl($3);
        $$->body = $6;
      }
    ;

opt_params
    : param_list { $$ = $1; }
    | /* empty */ { $$ = new std::vector<AST::Param*>(); }
    ;

param_list
    : param_list COMMA param { $$ = $1; $1->push_back($3); }
    | param                  { $$ = new std::vector<AST::Param*>(); $$->push_back($1); }
    ;

param
    : IDENTIFIER COLON IDENTIFIER
      { $$ = new AST::Param($1, $3); free($1); free($3); }
    ;

body
    : stmt_list
      {
        auto* b = new AST::Block();
        for (auto* s : *$1) b->stmts.push_back(s);
        delete $1;
        $$ = b;
      }
    ;

stmt_list
    : stmt_list stmt { $$ = $1; $1->push_back($2); }
    | stmt           { $$ = new std::vector<AST::Stmt*>(); $$->push_back($1); }
    ;

stmt
    : simple_stmt
    | if_stmt
    | while_stmt
    | return_stmt
    ;

simple_stmt
    : var_decl
      { $$ = new AST::VarDeclStmt($1); }
    | IDENTIFIER ASSIGN expr
      { $$ = new AST::AssignmentStmt($1, $3); free($1); }
    | expr
      { $$ = new AST::ExprStmt($1); }
    ;

if_stmt
    : IF expr THEN body opt_else END
      { $$ = new AST::IfStmt($2, $4, $5); }
    ;

opt_else
    : ELSE body { $$ = $2; }
    | /* empty */ { $$ = nullptr; }
    ;

while_stmt
    : WHILE expr LOOP body END
      { $$ = new AST::WhileStmt($2, $4); }
    ;

return_stmt
    : RETURN opt_expr
      { $$ = new AST::ReturnStmt($2); }
    ;

opt_expr
    : expr { $$ = $1; }
    | /* empty */ { $$ = nullptr; }
    ;

expr
    : primary_expr
    | expr DOT IDENTIFIER
      { $$ = new AST::MemberAccess($1, $3); free($3); }
    | expr DOT IDENTIFIER LPAREN opt_args RPAREN
      { $$ = new AST::MethodCall($1, $3, $5); free($3); }
    | IDENTIFIER LPAREN opt_args RPAREN
      { $$ = new AST::MethodCall(new AST::Identifier("this"), $1, $3); free($1); }
    | NEW IDENTIFIER LPAREN opt_args RPAREN
      { $$ = new AST::ConstructorCall($2, $4); free($2); }
    | NEW IDENTIFIER LBRACKET IDENTIFIER RBRACKET LPAREN opt_args RPAREN
      { 
        std::string type = std::string($2) + "[" + $4 + "]";
        $$ = new AST::ConstructorCall(strdup(type.c_str()), $7); 
        free($2); 
        free($4); 
      }
    ;

primary_expr
    : INTEGER_LITERAL      { $$ = new AST::IntLiteral($1); }
    | REAL_LITERAL         { $$ = new AST::RealLiteral($1); }
    | TRUE                 { $$ = new AST::BoolLiteral(true); }
    | FALSE                { $$ = new AST::BoolLiteral(false); }
    | IDENTIFIER           { $$ = new AST::Identifier($1); free($1); }
    | THIS                 { $$ = new AST::ThisLiteral(); }
    | LPAREN expr RPAREN   { $$ = $2; }
    ;

opt_args
    : arg_list { $$ = $1; }
    | /* empty */ { $$ = new std::vector<AST::Expr*>(); }
    ;

arg_list
    : arg_list COMMA expr { $$ = $1; $1->push_back($3); }
    | expr                { $$ = new std::vector<AST::Expr*>(); $$->push_back($1); }
    ;

%%

void yyerror(const char* s) { std::fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s); }