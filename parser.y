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
static AST::ClassDecl* currentClass = nullptr;
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
    struct CtorDecl;
    struct Param;
    struct Block;
  }
}

%defines "parser.hpp"
%define parse.error verbose

%union {
    long long                        ival;
    double                           rval;
    char*                            cstr;
    AST::Program*                    program;
    AST::ClassDecl*                  classdecl;
    AST::VarDecl*                    vardecl;
    AST::Expr*                       expr;
    AST::Stmt*                       stmt;
    AST::MethodDecl*                 methoddecl;
    AST::CtorDecl*                   ctordecl;
    AST::Param*                      param;
    std::vector<AST::ClassDecl*>*    classlist;
    std::vector<AST::Node*>*         memberlist;
    std::vector<AST::VarDecl*>*      varlist;
    std::vector<AST::Param*>*        paramlist;
    std::vector<AST::Stmt*>*         stmtlist;
    std::vector<AST::Expr*>*         exprlist;
}

%token CLASS EXTENDS VAR IS END
%token METHOD RETURN IF THEN ELSE
%token WHILE LOOP
%token TRUE FALSE
%token THIS
%token COLON COMMA
%token LPAREN RPAREN LBRACKET RBRACKET
%token ASSIGN ARROW
%token DOT
%token <cstr> IDENTIFIER
%token <ival> INT_LITERAL
%token <rval> REAL_LITERAL
%token <cstr> STRING_LITERAL

%type  <program>   program
%type  <classlist> class_list
%type  <classdecl> class_decl
%type  <memberlist> class_body member_list
%type  <vardecl>   field_decl
%type  <methoddecl> method_decl
%type  <ctordecl>  ctor_decl
%type  <paramlist> opt_params param_list
%type  <param>     param
%type  <stmt>      stmt simple_stmt if_stmt while_stmt block_stmt method_body opt_else
%type  <stmtlist>  stmt_list
%type  <expr>      expr primary postfix
%type  <exprlist>  arg_list opt_args
%type  <cstr>      opt_extends opt_ret_type

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
    : class_list class_decl   { $$ = $1; $1->push_back($2); }
    | class_decl              { $$ = new std::vector<AST::ClassDecl*>(); $$->push_back($1); }
    ;

class_decl
    : CLASS IDENTIFIER opt_extends IS class_body END
      {
        AST::ClassDecl* c = new AST::ClassDecl($2);
        if ($3) c->baseName = $3;
        for (auto* n : *$5) {
            if (auto* v = dynamic_cast<AST::VarDecl*>(n)) c->fields.push_back(v);
            else if (auto* ct = dynamic_cast<AST::CtorDecl*>(n)) c->ctors.push_back(ct);
            else if (auto* m = dynamic_cast<AST::MethodDecl*>(n)) c->methods.push_back(m);
            else delete n;
        }
        free($2);
        if ($3) free($3);
        delete $5;
        $$ = c;
      }
    ;

opt_extends
    : EXTENDS IDENTIFIER { $$ = $2; }
    |                     { $$ = nullptr; }
    ;

class_body
    : member_list          { $$ = $1; }
    |                      { $$ = new std::vector<AST::Node*>(); }
    ;

member_list
    : member_list field_decl { $$ = $1; $1->push_back($2); }
    | member_list method_decl { $$ = $1; $1->push_back($2); }
    | member_list ctor_decl   { $$ = $1; $1->push_back($2); }
    | field_decl              { $$ = new std::vector<AST::Node*>(); $$->push_back($1); }
    | method_decl             { $$ = new std::vector<AST::Node*>(); $$->push_back($1); }
    | ctor_decl               { $$ = new std::vector<AST::Node*>(); $$->push_back($1); }
    ;

field_decl
    : VAR IDENTIFIER COLON expr
      {
        AST::VarDecl* v = new AST::VarDecl($2, "", $4);
        free($2);
        $$ = v;
      }
    ;

ctor_decl
    : THIS opt_params IS block_stmt END
      {
        AST::CtorDecl* c = new AST::CtorDecl();
        for (auto* p : *$2) c->params.push_back(p);
        delete $2;
        c->body = $4;
        $$ = c;
      }
    ;

method_decl
    : METHOD IDENTIFIER opt_params opt_ret_type method_body
      {
        AST::MethodDecl* m = new AST::MethodDecl($2, $4 ? $4 : std::string(""), $5);
        for (auto* p : *$3) m->params.push_back(p);
        delete $3;
        if ($4) free($4);
        free($2);
        $$ = m;
      }
    ;

opt_params
    : LPAREN param_list RPAREN { $$ = $2; }
    | LPAREN RPAREN            { $$ = new std::vector<AST::Param*>(); }
    |                          { $$ = new std::vector<AST::Param*>(); }
    ;

param_list
    : param_list COMMA param   { $$ = $1; $1->push_back($3); }
    | param                    { $$ = new std::vector<AST::Param*>(); $$->push_back($1); }
    ;

param
    : IDENTIFIER COLON IDENTIFIER
      {
        AST::Param* p = new AST::Param($1, $3);
        free($1);
        free($3);
        $$ = p;
      }
    ;

opt_ret_type
    : COLON IDENTIFIER { $$ = $2; }
    |                  { $$ = nullptr; }
    ;

method_body
    : IS block_stmt END
      {
        $$ = $2;
      }
    | ARROW expr
      {
        AST::Block* b = new AST::Block();
        b->stmts.push_back(new AST::ReturnStmt($2));
        $$ = b;
      }
    ;

block_stmt
    : stmt_list
      {
        AST::Block* b = new AST::Block();
        for (auto* s : *$1) b->stmts.push_back(s);
        delete $1;
        $$ = b;
      }
    | 
      {
        AST::Block* b = new AST::Block();
        $$ = b;
      }
    ;

stmt_list
    : stmt_list stmt           { $$ = $1; $1->push_back($2); }
    | stmt                     { $$ = new std::vector<AST::Stmt*>(); $$->push_back($1); }
    ;

stmt
    : simple_stmt              { $$ = $1; }
    | if_stmt                  { $$ = $1; }
    | while_stmt               { $$ = $1; }
    ;

simple_stmt
    : RETURN expr              { $$ = new AST::ReturnStmt($2); }
    | RETURN                   { $$ = new AST::ReturnStmt(nullptr); }
    | VAR IDENTIFIER COLON expr
      {
        AST::VarDecl* v = new AST::VarDecl($2, "", $4);
        free($2);
        $$ = new AST::VarDeclStmt(v);
      }
    | IDENTIFIER ASSIGN expr
      {
        AST::Expr* lhs = new AST::Identifier($1);
        free($1);
        AST::Expr* rhs = $3;
        AST::Binary* bin = new AST::Binary(AST::BinOp::Assign, lhs, rhs);
        $$ = new AST::ExprStmt(bin);
      }
    | expr
      {
        $$ = new AST::ExprStmt($1);
      }
    ;

if_stmt
    : IF expr THEN block_stmt opt_else END
      {
        $$ = new AST::IfStmt($2, $4, $5);
      }
    ;

opt_else
    : ELSE block_stmt          { $$ = $2; }
    |                          { $$ = new AST::Block(); }
    ;

while_stmt
    : WHILE expr LOOP block_stmt END
      {
        $$ = new AST::WhileStmt($2, $4);
      }
    ;

expr
    : postfix                  { $$ = $1; }
    ;

postfix
    : primary                  { $$ = $1; }
    | postfix DOT IDENTIFIER
      {
        $$ = new AST::MemberAccess($1, $3);
        free($3);
      }
    | postfix LPAREN opt_args RPAREN
      {
        AST::Call* call = new AST::Call($1);
        for (auto* e : *$3) call->args.push_back(e);
        delete $3;
        $$ = call;
      }
    | IDENTIFIER LPAREN opt_args RPAREN
      {
        AST::Identifier* id = new AST::Identifier($1);
        free($1);
        AST::Call* call = new AST::Call(id);
        for (auto* e : *$3) call->args.push_back(e);
        delete $3;
        $$ = call;
      }
    ;

opt_args
    : arg_list                 { $$ = $1; }
    |                          { $$ = new std::vector<AST::Expr*>(); }
    ;

arg_list
    : arg_list COMMA expr      { $$ = $1; $1->push_back($3); }
    | expr                     { $$ = new std::vector<AST::Expr*>(); $$->push_back($1); }
    ;

primary
    : INT_LITERAL              { $$ = new AST::IntLiteral($1); }
    | REAL_LITERAL             { $$ = new AST::RealLiteral($1); }
    | STRING_LITERAL           { $$ = new AST::StringLiteral($1); free($1); }
    | TRUE                     { $$ = new AST::BoolLiteral(true); }
    | FALSE                    { $$ = new AST::BoolLiteral(false); }
    | THIS                     { $$ = new AST::ThisExpr(); }
    | IDENTIFIER               { $$ = new AST::Identifier($1); free($1); }
    | LPAREN expr RPAREN       { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    std::fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
