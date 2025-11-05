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
    struct Node;
    struct Program;
    struct ClassDecl;
    struct VarDecl;
    struct Expr;
    struct Stmt;
    struct MethodDecl;
    struct Param;
  }
}

%defines "parser.hpp"
%define parse.error verbose

%union {
    long long                      ival;
    char*                          cstr;
    AST::Program*                  program;
    AST::ClassDecl*                classdecl;
    AST::VarDecl*                  vardecl;
    AST::Expr*                     expr;
    AST::Stmt*                     stmt;
    AST::MethodDecl*               methoddecl;
    AST::Param*                    param;
    AST::Node*                     node;
    std::vector<AST::ClassDecl*>*  classlist;
    std::vector<AST::Node*>*       memberlist;
    std::vector<AST::VarDecl*>*    varlist;
    std::vector<AST::Param*>*      paramlist;
}

%token CLASS VAR IS END
%token METHOD RETURN IF THEN ELSE
%token TRUE FALSE
%token COLON SEMICOLON COMMA
%token LPAREN RPAREN LBRACE RBRACE
%token ASSIGN ARROW PLUS MINUS STAR SLASH
%token <cstr> IDENTIFIER
%token <cstr> TYPE_NAME
%token <ival> INT_LITERAL

%type  <program>   program
%type  <classlist> class_list
%type  <classdecl> class_decl
%type  <memberlist> class_body member_list
%type  <node>      member
%type  <vardecl>   var_decl
%type  <methoddecl> method_decl
%type  <paramlist> opt_params param_list
%type  <param>     param
%type  <stmt>      method_body stmt if_stmt
%type  <expr>      expr additive_expr multiplicative_expr unary_expr primary_expr

%%

program
    : class_list
      {
        g_program = new AST::Program();
        for (auto* c : *$1) g_program->classes.push_back(c);
        delete $1;
      }
    ;

class_list
    : class_list class_decl
      { $$ = $1; $1->push_back($2); }
    | class_decl
      { $$ = new std::vector<AST::ClassDecl*>(); $$->push_back($1); }
    ;

class_decl
    : CLASS IDENTIFIER IS class_body END
      {
        $$ = new AST::ClassDecl($2);
        for (auto* n : *$4) {
            if (auto* v = dynamic_cast<AST::VarDecl*>(n)) $$->fields.push_back(v);
            else if (auto* m = dynamic_cast<AST::MethodDecl*>(n)) $$->methods.push_back(m);
            else delete n;
        }
        free($2);
        delete $4;
      }
    ;

class_body
    : member_list { $$ = $1; }
    | { $$ = new std::vector<AST::Node*>(); }
    ;

member_list
    : member_list member
      { $$ = $1; $1->push_back($2); }
    | member
      { $$ = new std::vector<AST::Node*>(); $$->push_back($1); }
    ;

member
    : var_decl     { $$ = $1; }
    | method_decl  { $$ = $1; }
    ;

var_decl
    : VAR IDENTIFIER COLON TYPE_NAME SEMICOLON
      {
        $$ = new AST::VarDecl($2, $4, nullptr);
        free($2); free($4);
      }
    | VAR IDENTIFIER COLON TYPE_NAME ASSIGN expr SEMICOLON
      {
        $$ = new AST::VarDecl($2, $4, $6);
        free($2); free($4);
      }
    ;

method_decl
    : METHOD IDENTIFIER LPAREN opt_params RPAREN COLON TYPE_NAME ARROW method_body
      {
        $$ = new AST::MethodDecl($2, $7, $9);
        if ($4) { for (auto* p : *$4) $$->params.push_back(p); delete $4; }
        free($2); free($7);
      }
    ;

opt_params
    : param_list { $$ = $1; }
    | { $$ = new std::vector<AST::Param*>(); }
    ;

param_list
    : param_list COMMA param
      { $$ = $1; $1->push_back($3); }
    | param
      { $$ = new std::vector<AST::Param*>(); $$->push_back($1); }
    ;

param
    : IDENTIFIER COLON TYPE_NAME
      {
        $$ = new AST::Param($1, $3);
        free($1); free($3);
      }
    ;

method_body
    : expr
      { $$ = new AST::ReturnStmt($1); }
    | stmt
      { $$ = $1; }
    ;

stmt
    : RETURN expr
      { $$ = new AST::ReturnStmt($2); }
    | if_stmt
      { $$ = $1; }
    ;

if_stmt
    : IF expr THEN stmt ELSE stmt
      { $$ = new AST::IfStmt($2, $4, $6); }
    ;

expr
    : additive_expr { $$ = $1; }
    ;

additive_expr
    : additive_expr PLUS multiplicative_expr
      { $$ = new AST::Binary(AST::BinOp::Add, $1, $3); }
    | additive_expr MINUS multiplicative_expr
      { $$ = new AST::Binary(AST::BinOp::Sub, $1, $3); }
    | multiplicative_expr
      { $$ = $1; }
    ;

multiplicative_expr
    : multiplicative_expr STAR unary_expr
      { $$ = new AST::Binary(AST::BinOp::Mul, $1, $3); }
    | multiplicative_expr SLASH unary_expr
      { $$ = new AST::Binary(AST::BinOp::Div, $1, $3); }
    | unary_expr
      { $$ = $1; }
    ;

unary_expr
    : MINUS unary_expr
      { $$ = new AST::Unary(AST::Unary::Op::Neg, $2); }
    | primary_expr
      { $$ = $1; }
    ;

primary_expr
    : INT_LITERAL
      { $$ = new AST::IntLiteral($1); }
    | TRUE
      { $$ = new AST::BoolLiteral(true); }
    | FALSE
      { $$ = new AST::BoolLiteral(false); }
    | IDENTIFIER
      { $$ = new AST::Identifier($1); free($1); }
    | LPAREN expr RPAREN
      { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    std::fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
