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

/* Вставляется в parser.hpp */
%code requires {
  #include <vector>
  namespace AST {
    struct Program;
    struct ClassDecl;
    struct VarDecl;
    struct Expr;
  }
}

%defines "parser.hpp"
%define parse.error verbose

%union {
    long long                ival;
    char*                    cstr;
    AST::Program*            program;
    AST::ClassDecl*          classdecl;
    AST::VarDecl*            vardecl;
    AST::Expr*               expr;
    std::vector<AST::ClassDecl*>* classlist;
    std::vector<AST::VarDecl*>*   varlist;
}

%token CLASS VAR IS END
%token COLON SEMICOLON COMMA
%token LPAREN RPAREN LBRACE RBRACE
%token ASSIGN PLUS MINUS STAR SLASH
%token <cstr> IDENTIFIER
%token <cstr> TYPE_NAME
%token <ival> INT_LITERAL

%type  <program>   program
%type  <classlist> class_list
%type  <classdecl> class_decl
%type  <varlist>   class_body var_decl_list
%type  <vardecl>   var_decl
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
        for (auto* v : *$4) $$->fields.push_back(v);
        free($2);
        delete $4;
      }
    ;

class_body
    : var_decl_list { $$ = $1; }
    | { $$ = new std::vector<AST::VarDecl*>(); }
    ;

var_decl_list
    : var_decl_list var_decl
      { $$ = $1; $1->push_back($2); }
    | var_decl
      { $$ = new std::vector<AST::VarDecl*>(); $$->push_back($1); }
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
    | IDENTIFIER
      { $$ = new AST::Identifier($1); free($1); }
    | LPAREN expr RPAREN
      { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    std::fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
