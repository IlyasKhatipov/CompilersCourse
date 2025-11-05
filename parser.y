/* parser.y */
%{
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include "tokens.hpp"
#include "ast.hpp"

extern int yylex(void);
extern FILE* yyin;
void yyerror(const char* s);

using namespace AST;

Program* g_program = nullptr;
%}

%define api.pure full
%define parse.error verbose
%define api.prefix {yy}
%define api.value.type {union}
%define api.token.prefix {T_}

%union {
  Token* tok;
  AST::Program* program;
  AST::ClassDecl* classDecl;
  std::vector<AST::ClassDecl*>* classList;
  AST::VarDecl* varDecl;
  std::vector<AST::VarDecl*>* varList;
  AST::TypeName* typeName;
  AST::Expr* expr;
}

%token <tok> CLASS IS VAR END
%token <tok> IDENTIFIER INT_TYPE INTEGER
%token <tok> COLON SEMI ASSIGN
%token <tok> LPAREN RPAREN PLUS MINUS STAR SLASH DOT

%type <program> program
%type <classList> class_list
%type <classDecl> class_decl
%type <varList> var_decl_list
%type <varDecl> var_decl
%type <typeName> type
%type <expr> expr term factor

%%

program
    : class_list
      {
        auto prog = new Program();
        for (auto* c : *$1) prog->classes.emplace_back(c);
        delete $1;
        g_program = prog;
        $$ = prog;
      }
    ;

class_list
    : class_decl                     { $$ = new std::vector<ClassDecl*>(); $$->push_back($1); }
    | class_list class_decl          { $$ = $1; $$->push_back($2); }
    ;

class_decl
    : CLASS IDENTIFIER IS var_decl_list END
      {
        auto cls = new ClassDecl($2->lexeme);
        for (auto* v : *$4) cls->fields.emplace_back(v);
        delete $4;
        $$ = cls;
      }
    ;

var_decl_list
    : /* empty */                    { $$ = new std::vector<VarDecl*>(); }
    | var_decl_list var_decl         { $$ = $1; $$->push_back($2); }
    ;

var_decl
    : VAR IDENTIFIER COLON type SEMI
      {
        $$ = new VarDecl($2->lexeme, std::unique_ptr<TypeName>($4));
      }
    | VAR IDENTIFIER COLON type ASSIGN expr SEMI
      {
        $$ = new VarDecl($2->lexeme, std::unique_ptr<TypeName>($4), std::unique_ptr<Expr>($6));
      }
    ;

type
    : INT_TYPE                       { $$ = new TypeName("Int"); }
    | IDENTIFIER                     { $$ = new TypeName($1->lexeme); }
    ;

/* Выражения: раскладываем a+b+10 и т.п. в бинарные узлы */
expr
    : expr PLUS term                 { $$ = new BinExpr('+', std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)); }
    | expr MINUS term                { $$ = new BinExpr('-', std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)); }
    | term                           { $$ = $1; }
    ;

term
    : term STAR factor               { $$ = new BinExpr('*', std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)); }
    | term SLASH factor              { $$ = new BinExpr('/', std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)); }
    | factor                         { $$ = $1; }
    ;

factor
    : INTEGER                        { $$ = new IntLiteral(static_cast<IntegerToken*>($1)->value); }
    | IDENTIFIER                     { $$ = new IdExpr($1->lexeme); }
    | LPAREN expr RPAREN             { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
