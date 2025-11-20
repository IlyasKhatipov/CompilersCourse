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
    struct Node; struct Program; struct ClassDecl; struct VarDecl; struct Expr; struct Stmt; struct MethodDecl; struct Param; struct Block;
  }
}

%defines "parser.hpp"
%define parse.error verbose

%union {
    long long                        ival;
    char*                            cstr;
    AST::Program*                    program;
    AST::ClassDecl*                  classdecl;
    AST::VarDecl*                    vardecl;
    AST::Expr*                       expr;
    AST::Stmt*                       stmt;
    AST::MethodDecl*                 methoddecl;
    AST::Param*                      param;
    AST::Node*                       node;
    std::vector<AST::ClassDecl*>*    classlist;
    std::vector<AST::Node*>*         memberlist;
    std::vector<AST::VarDecl*>*      varlist;
    std::vector<AST::Param*>*        paramlist;
    std::vector<AST::Stmt*>*         stmtlist;
    std::vector<AST::Expr*>*         exprlist;
    std::vector<char*>*              strlist;
}

%token CLASS VAR IS END
%token METHOD RETURN IF THEN ELSE ELSEIF
%token WHILE DO
%token TRUE FALSE
%token COLON SEMICOLON COMMA
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token ASSIGN ARROW PLUS MINUS STAR SLASH
%token DOT GT LT EQEQ EQUAL
%token <cstr> IDENTIFIER
%token <cstr> TYPE_NAME
%token <ival> INT_LITERAL
%token <cstr> STRING_LITERAL

%type  <program>   program
%type  <classlist> class_list
%type  <classdecl> class_decl
%type  <memberlist> class_body member_list
%type  <node>      member
%type  <vardecl>   var_decl
%type  <methoddecl> method_decl
%type  <paramlist> opt_params param_list
%type  <param>     param
%type  <cstr>      type_spec type_list
%type  <stmt>      method_body stmt simple_stmt if_stmt while_stmt block_stmt elif_tail opt_else
%type  <stmtlist>  stmt_list
%type  <expr>      expr assign_expr equality_expr relational_expr additive_expr multiplicative_expr unary_expr postfix_expr primary_expr lvalue type_as_expr
%type  <exprlist>  arg_list opt_args

%%

program
    : class_list
      { g_program = new AST::Program(); for (auto* c : *$1) g_program->classes.push_back(c); delete $1; }
    ;

class_list
    : class_list class_decl { $$ = $1; $1->push_back($2); }
    | class_decl            { $$ = new std::vector<AST::ClassDecl*>(); $$->push_back($1); }
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
    |             { $$ = new std::vector<AST::Node*>(); }
    ;

member_list
    : member_list member { $$ = $1; $1->push_back($2); }
    | member             { $$ = new std::vector<AST::Node*>(); $$->push_back($1); }
    ;

member
    : var_decl    { $$ = $1; }
    | method_decl { $$ = $1; }
    ;

type_spec
    : TYPE_NAME
      { $$ = $1; }
    | TYPE_NAME LT type_list GT
      {
        std::string s = std::string($1) + "<" + std::string($3) + ">";
        $$ = strdup(s.c_str());
        free($1);
        free($3);
      }
    ;

type_list
    : type_spec
      { $$ = $1; }
    | type_list COMMA type_spec
      {
        std::string s = std::string($1) + "," + std::string($3);
        $$ = strdup(s.c_str());
        free($1);
        free($3);
      }
    ;

var_decl
    : VAR IDENTIFIER COLON type_spec SEMICOLON
      { $$ = new AST::VarDecl($2, $4, nullptr); free($2); free($4); }
    | VAR IDENTIFIER COLON type_spec EQUAL expr SEMICOLON
      { $$ = new AST::VarDecl($2, $4, $6); free($2); free($4); }
    | VAR IDENTIFIER COLON type_spec ASSIGN expr SEMICOLON
      { $$ = new AST::VarDecl($2, $4, $6); free($2); free($4); }
    ;

method_decl
    : METHOD IDENTIFIER LPAREN opt_params RPAREN COLON type_spec ARROW method_body
      {
        $$ = new AST::MethodDecl($2, $7, $9);
        if ($4) {
          for (auto* p : *$4) $$->params.push_back(p);
          delete $4;
        }
        free($2);
        free($7);
      }
    ;

opt_params
    : param_list { $$ = $1; }
    |            { $$ = new std::vector<AST::Param*>(); }
    ;

param_list
    : param_list COMMA param { $$ = $1; $1->push_back($3); }
    | param                  { $$ = new std::vector<AST::Param*>(); $$->push_back($1); }
    ;

param
    : IDENTIFIER COLON type_spec
      { $$ = new AST::Param($1, $3); free($1); free($3); }
    ;

method_body
    : stmt_list
      {
        auto* b = new AST::Block();
        for (auto* s : *$1) b->stmts.push_back(s);
        delete $1;
        $$ = b;
      }
    ;

stmt_list
    : stmt_list simple_stmt SEMICOLON { $$ = $1; $1->push_back($2); }
    | stmt_list if_stmt              { $$ = $1; $1->push_back($2); }
    | stmt_list while_stmt           { $$ = $1; $1->push_back($2); }
    | stmt_list simple_stmt          { $$ = $1; $1->push_back($2); }
    | simple_stmt SEMICOLON          { $$ = new std::vector<AST::Stmt*>(); $$->push_back($1); }
    | if_stmt                        { $$ = new std::vector<AST::Stmt*>(); $$->push_back($1); }
    | while_stmt                     { $$ = new std::vector<AST::Stmt*>(); $$->push_back($1); }
    | simple_stmt                    { $$ = new std::vector<AST::Stmt*>(); $$->push_back($1); }
    ;

stmt
    : simple_stmt { $$ = $1; }
    | if_stmt     { $$ = $1; }
    | while_stmt  { $$ = $1; }
    ;

simple_stmt
    : RETURN expr                                { $$ = new AST::ReturnStmt($2); }
    | RETURN                                     { $$ = new AST::ReturnStmt(nullptr); }
    | VAR IDENTIFIER COLON type_spec             { $$ = new AST::VarDeclStmt(new AST::VarDecl($2, $4, nullptr)); free($2); free($4); }
    | VAR IDENTIFIER COLON type_spec EQUAL expr  { $$ = new AST::VarDeclStmt(new AST::VarDecl($2, $4, $6)); free($2); free($4); }
    | VAR IDENTIFIER COLON type_spec ASSIGN expr { $$ = new AST::VarDeclStmt(new AST::VarDecl($2, $4, $6)); free($2); free($4); }
    | lvalue ASSIGN expr                         { $$ = new AST::ExprStmt(new AST::Binary(AST::BinOp::Assign, $1, $3)); }
    | expr                                       { $$ = new AST::ExprStmt($1); }
    ;

block_stmt
    : stmt_list
      {
        auto* b = new AST::Block();
        for (auto* s : *$1) b->stmts.push_back(s);
        delete $1;
        $$ = b;
      }
    ;

if_stmt
    : IF expr THEN block_stmt elif_tail END
      {
        $$ = new AST::IfStmt($2, $4, $5);
      }
    ;

elif_tail
    : ELSEIF expr THEN block_stmt elif_tail
      {
        $$ = new AST::IfStmt($2, $4, $5);
      }
    | opt_else
      {
        $$ = $1 ? $1 : static_cast<AST::Stmt*>(new AST::Block());
      }
    ;

opt_else
    : ELSE block_stmt { $$ = $2; }
    |                 { $$ = nullptr; }
    ;

while_stmt
    : WHILE expr DO stmt_list END
      {
        auto* b = new AST::Block();
        for (auto* s : *$4) b->stmts.push_back(s);
        delete $4;
        $$ = new AST::WhileStmt($2, b);
      }
    ;

expr
    : assign_expr { $$ = $1; }
    ;

assign_expr
    : lvalue ASSIGN assign_expr { $$ = new AST::Binary(AST::BinOp::Assign, $1, $3); }
    | equality_expr             { $$ = $1; }
    ;

equality_expr
    : equality_expr EQEQ relational_expr { $$ = new AST::Binary(AST::BinOp::Eq, $1, $3); }
    | relational_expr                    { $$ = $1; }
    ;

relational_expr
    : relational_expr GT additive_expr { $$ = new AST::Binary(AST::BinOp::Gt, $1, $3); }
    | relational_expr LT additive_expr { $$ = new AST::Binary(AST::BinOp::Lt, $1, $3); }
    | additive_expr                    { $$ = $1; }
    ;

additive_expr
    : additive_expr PLUS multiplicative_expr  { $$ = new AST::Binary(AST::BinOp::Add, $1, $3); }
    | additive_expr MINUS multiplicative_expr { $$ = new AST::Binary(AST::BinOp::Sub, $1, $3); }
    | multiplicative_expr                     { $$ = $1; }
    ;

multiplicative_expr
    : multiplicative_expr STAR unary_expr  { $$ = new AST::Binary(AST::BinOp::Mul, $1, $3); }
    | multiplicative_expr SLASH unary_expr { $$ = new AST::Binary(AST::BinOp::Div, $1, $3); }
    | unary_expr                           { $$ = $1; }
    ;

unary_expr
    : MINUS unary_expr  { $$ = new AST::Unary(AST::Unary::Op::Neg, $2); }
    | postfix_expr      { $$ = $1; }
    ;

postfix_expr
    : postfix_expr LPAREN opt_args RPAREN
      { auto* call = new AST::Call($1); for (auto* e : *$3) call->args.push_back(e); delete $3; $$ = call; }
    | postfix_expr DOT IDENTIFIER
      { $$ = new AST::MemberAccess($1, $3); free($3); }
    | postfix_expr LBRACKET expr RBRACKET
      { $$ = new AST::Index($1, $3); }
    | primary_expr
      { $$ = $1; }
    ;

opt_args
    : arg_list { $$ = $1; }
    |          { $$ = new std::vector<AST::Expr*>(); }
    ;

arg_list
    : arg_list COMMA expr { $$ = $1; $1->push_back($3); }
    | expr                { $$ = new std::vector<AST::Expr*>(); $$->push_back($1); }
    ;

primary_expr
    : INT_LITERAL      { $$ = new AST::IntLiteral($1); }
    | STRING_LITERAL   { $$ = new AST::StringLiteral($1); free($1); }
    | TRUE             { $$ = new AST::BoolLiteral(true); }
    | FALSE            { $$ = new AST::BoolLiteral(false); }
    | IDENTIFIER       { $$ = new AST::Identifier($1); free($1); }
    | type_as_expr     { $$ = $1; }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

type_as_expr
    : type_spec
      { $$ = new AST::Identifier($1); free($1); }
    ;

lvalue
    : IDENTIFIER                 { $$ = new AST::Identifier($1); free($1); }
    | lvalue DOT IDENTIFIER      { $$ = new AST::MemberAccess($1, $3); free($3); }
    | lvalue LBRACKET expr RBRACKET { $$ = new AST::Index($1, $3); }
    ;

%%

void yyerror(const char* s) { std::fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s); }
