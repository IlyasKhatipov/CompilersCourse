%define parse.error verbose

%{
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include "ast.h"
#include <string>

using namespace std;

unique_ptr<ProgramNode> g_program = nullptr;
size_t parserTokIndex = 0;
vector<SimpleToken> simpleTokens;

void yyerror(const char *s) {
    cerr << "Parse error: " << s << "\n";
}

void printAST() {
    if (g_program) {
        g_program->print(0);
    } else {
        cout << "No AST generated.\n";
    }
}
%}

%code requires {
    #include <vector>
    class ASTNode;  // forward declaration
}

%union {
    char* str;
    ASTNode* node;
    std::vector<ASTNode*>* vec;
}

%token CLASS EXTENDS IS END VAR METHOD THIS RETURN IF THEN ELSE WHILE LOOP TRUE FALSE
%token <str> IDENTIFIER INTEGER REAL STRING
%token SYMBOL UNKNOWN
%token COLON SEMI LPAREN RPAREN COMMA DOT ASSIGN ARROW

%type <vec> top_list class_body method_body
%type <node> top_item class_decl var_decl method_decl class_member method_member
%type <str> maybe_type class_opt_ext
%start program

%%

program:
    top_list {
        g_program = make_unique<ProgramNode>();
        if ($1) {
            for (ASTNode* p : *$1) {
                g_program->decls.emplace_back(unique_ptr<ASTNode>(p));
            }
            delete $1;
        }
    }
;

top_list:
    /* empty */ { $$ = new vector<ASTNode*>(); }
  | top_list top_item {
        $$ = $1;
        if ($2) $$->push_back($2);
    }
;

top_item:
    class_decl { $$ = $1; }
  | var_decl   { $$ = $1; }
  | method_decl { $$ = $1; }
;

class_decl:
    CLASS IDENTIFIER class_opt_ext IS class_body END {
        auto cn = new ClassNode($2 ? string($2) : string());
        if ($3) cn->extendsName = string($3);
        if ($5) {
            for (ASTNode* m : *$5) cn->members.emplace_back(unique_ptr<ASTNode>(m));
            delete $5;
        }
        if ($2) free($2);
        if ($3) free($3);
        $$ = cn;
    }
;

class_opt_ext:
    /* empty */ { $$ = nullptr; }
  | EXTENDS IDENTIFIER { $$ = $2; }
;

class_body:
    /* empty */ { $$ = new vector<ASTNode*>(); }
  | class_body class_member {
        $$ = $1;
        if ($2) $$->push_back($2);
    }
;

class_member:
    var_decl { $$ = $1; }
  | method_decl { $$ = $1; }
;

var_decl:
    VAR IDENTIFIER maybe_type SEMI {
        auto vn = new VarNode($2 ? string($2) : string(), $3 ? string($3) : string());
        if ($2) free($2);
        if ($3) free($3);
        $$ = vn;
    }
;

maybe_type:
    /* empty */ { $$ = nullptr; }
  | COLON IDENTIFIER { $$ = $2; }
;

method_decl:
    METHOD IDENTIFIER LPAREN RPAREN IS method_body END {
        auto mn = new MethodNode($2 ? string($2) : string());
        if ($6) {
            for (ASTNode* b : *$6) mn->body.emplace_back(unique_ptr<ASTNode>(b));
            delete $6;
        }
        if ($2) free($2);
        $$ = mn;
    }
;

method_body:
    /* empty */ { $$ = new vector<ASTNode*>(); }
  | method_body method_member {
        $$ = $1;
        if ($2) $$->push_back($2);
    }
;

method_member:
    var_decl { $$ = $1; }
;

%%

int yylex(void);
