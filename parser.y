%code requires {
#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct Param {
    string name;
    string type;
};

struct Expr {
    string repr;
};

struct VarDecl {
    string name;
    string type;
};

struct MethodDecl {
    string name;
    vector<Param> params;
    string returnType;
    Expr body;
};

struct ClassDecl {
    string name;
    vector<VarDecl> vars;
    vector<MethodDecl> methods;
};

extern std::vector<ClassDecl> classes;
extern std::vector<MethodDecl> currentMethods;
}

%{
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <FlexLexer.h>

using namespace std;

int yylex();
void yyerror(const char *s);
%}

%union {
    char* str;
    struct VarDecl* var;
    struct MethodDecl* method;
    struct ClassDecl* cls;
    struct Expr* expr;
    vector<VarDecl>* varList;
    vector<Param>* paramList;
}

%token <str> IDENTIFIER STRING BOOLEAN INTEGER REAL SYMBOL
%token CLASS IS END VAR
%token METHOD EXTENDS THIS RETURN IF THEN ELSE WHILE LOOP ARROW

%type <cls> class_decl
%type <varList> class_body class_members class_member
%type <var> var_decl
%type <method> method_decl
%type <paramList> param_list param_list_opt
%type <expr> expr method_body

%left '+' '-'
%left '*' '/'
%right UMINUS
%nonassoc LOWER_THAN_ELSE

%start program

%%

program:
    class_list
    ;

class_list:
      class_decl
    | class_list class_decl
    ;

class_decl:
    CLASS IDENTIFIER IS class_body END
    {
        ClassDecl* cls = new ClassDecl();
        cls->name = $2;
        cls->vars = *$4;
        cls->methods = currentMethods;
        currentMethods.clear();
        classes.push_back(*cls);
        delete $4;
        free($2);
    }
  | CLASS IDENTIFIER '{' class_body '}'
    {
        ClassDecl* cls = new ClassDecl();
        cls->name = $2;
        cls->vars = *$4;
        cls->methods = currentMethods;
        currentMethods.clear();
        classes.push_back(*cls);
        delete $4;
        free($2);
    }
    ;

class_body:
      class_members
    |  { $$ = new vector<VarDecl>(); }
    ;

class_members:
      class_member
    | class_members class_member
      {
          $$ = $1;
          $$->insert($$->end(), $2->begin(), $2->end());
          delete $2;
      }
    ;

class_member:
      var_decl ';'
      {
          $$ = new vector<VarDecl>();
          $$->push_back(*$1);
          delete $1;
      }
    | method_decl
      {
          $$ = new vector<VarDecl>();
          currentMethods.push_back(*$1);
          delete $1;
      }
    ;

var_decl:
    VAR IDENTIFIER ':' IDENTIFIER
    {
        $$ = new VarDecl();
        $$->name = $2;
        $$->type = $4;
        free($2);
        free($4);
    }
    ;

method_decl:
    METHOD IDENTIFIER '(' param_list_opt ')' ':' IDENTIFIER ARROW method_body
    {
        MethodDecl* m = new MethodDecl();
        m->name = $2;
        m->params = *$4;
        m->returnType = $7;
        m->body = *$9;
        $$ = m;
        free($2);
        free($7);
        delete $4;
        delete $9;
    }
    ;

param_list_opt:
      { $$ = new vector<Param>(); }
    | param_list { $$ = $1; }
    ;

param_list:
      IDENTIFIER ':' IDENTIFIER
      {
          $$ = new vector<Param>();
          $$->push_back({$1, $3});
          free($1);
          free($3);
      }
    | param_list ',' IDENTIFIER ':' IDENTIFIER
      {
          $$ = $1;
          $$->push_back({$3, $5});
          free($3);
          free($5);
      }
    ;

method_body:
      expr { $$ = $1; }
    | RETURN expr { $$ = $2; }
    | if_stmt { $$ = new Expr(); $$->repr = "if_stmt"; }
    ;

if_stmt:
    IF expr THEN stmt_list %prec LOWER_THAN_ELSE
  | IF expr THEN stmt_list ELSE stmt_list
  ;

stmt_list:
    stmt
  | stmt_list stmt
  ;

stmt:
    RETURN expr
  | expr
  | if_stmt
  ;

expr:
      IDENTIFIER           { $$ = new Expr(); $$->repr = $1; free($1); }
    | INTEGER              { $$ = new Expr(); $$->repr = $1; free($1); }
    | REAL                 { $$ = new Expr(); $$->repr = $1; free($1); }
    | BOOLEAN              { $$ = new Expr(); $$->repr = $1; free($1); }
    | STRING               { $$ = new Expr(); $$->repr = "\"" + string($1) + "\""; free($1); }
    | expr '+' expr        { $$ = new Expr(); $$->repr = "(" + $1->repr + " + " + $3->repr + ")"; delete $1; delete $3; }
    | expr '-' expr        { $$ = new Expr(); $$->repr = "(" + $1->repr + " - " + $3->repr + ")"; delete $1; delete $3; }
    | expr '*' expr        { $$ = new Expr(); $$->repr = "(" + $1->repr + " * " + $3->repr + ")"; delete $1; delete $3; }
    | expr '/' expr        { $$ = new Expr(); $$->repr = "(" + $1->repr + " / " + $3->repr + ")"; delete $1; delete $3; }
    | '-' expr %prec UMINUS { $$ = new Expr(); $$->repr = "(-" + $2->repr + ")"; delete $2; }
    | '(' expr ')'         { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    cerr << "Syntax error: " << s << endl;
}

static yyFlexLexer lexer;
std::vector<ClassDecl> classes;
std::vector<MethodDecl> currentMethods;

int yylex() {
    return lexer.yylex();
}

int main(int argc, char **argv) {
    cout << "Parsing..." << endl;

    cout << "-----------------------------------" << endl;
    cout << "Lexer tracers" << endl;
    cout.flush();  // чтобы трассы сразу шли после этой строки
    
    int result = yyparse();

    cout << "------------------------------" << endl;
    
    if (result == 0) {
        cout << "Parsing completed successfully." << endl;
        for (auto &cls : classes) {
            cout << "Class: " << cls.name << endl;
            for (auto &v : cls.vars)
                cout << "  Var " << v.name << " : " << v.type << endl;
            for (auto &m : cls.methods) {
                cout << "  Method " << m.name << "(";
                for (size_t i=0; i<m.params.size(); ++i) {
                    if (i > 0) cout << ", ";
                    cout << m.params[i].name << " : " << m.params[i].type;
                }
                cout << ") : " << m.returnType << endl;
                cout << "    Body: " << m.body.repr << endl;
            }
        }
    } else {
        cout << "Parsing failed." << endl;
    }
    return 0;
}
