%code requires {
    #include <string>
    #include <vector>
    #include <memory>
    #include <iostream>

    using namespace std;

    struct VarDecl {
        string name;
        string type;
    };

    struct ClassDecl {
        string name;
        vector<VarDecl> vars;
    };

    extern vector<ClassDecl> classes;
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

/* value */
%union {
    char* str;
    struct VarDecl* var;
    struct ClassDecl* cls;
    vector<VarDecl>* varList;
}

/* terminals */
%token <str> IDENTIFIER STRING BOOLEAN INTEGER REAL SYMBOL
%token CLASS IS END VAR
%token METHOD EXTENDS THIS RETURN IF THEN ELSE WHILE LOOP ARROW

/* nonterminals */
%type <cls> class_decl
%type <varList> class_body class_members class_member
%type <var> var_decl

%left '+' '-'
%left '*' '/'
%right UMINUS

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
        classes.push_back(*cls);
        delete $4;
        free($2);
    }
  | CLASS IDENTIFIER '{' class_body '}'
    {
        ClassDecl* cls = new ClassDecl();
        cls->name = $2;
        cls->vars = *$4;
        classes.push_back(*cls);
        delete $4;
        free($2);
    }
    ;

class_body:
      class_members
    | /* empty */ { $$ = new vector<VarDecl>(); }
    ;

class_members:
      class_member
    | class_members class_member
      {
          /* merge vectors */
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
          /* methods do not contribute vars -> return empty list */
          $$ = new vector<VarDecl>();
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

/* minimal method / statements / expressions to accept tests */
method_decl:
    METHOD IDENTIFIER '(' param_list_opt ')' ':' IDENTIFIER ARROW method_body
    { /* no semantic data needed here */ free($2); free($7); }
    ;

param_list_opt:
    /* empty */ { }
    | param_list { }
    ;

param_list:
    IDENTIFIER ':' IDENTIFIER
    | param_list ',' IDENTIFIER ':' IDENTIFIER
    ;

/* method_body can be expression or if-statement or return */
method_body:
      expr
    | if_stmt
    | RETURN expr
    ;

if_stmt:
    IF expr THEN stmt_list ELSE stmt_list END
    ;

stmt_list:
    stmt
  | stmt_list stmt
  ;

stmt:
    RETURN expr
  | expr
  ;

/* very small expression grammar */
expr:
    IDENTIFIER
  | INTEGER
  | REAL
  | BOOLEAN
  | STRING
  | '(' expr ')'
  | expr '+' expr
  | expr '-' expr
  | expr '*' expr
  | expr '/' expr
  | '-' expr %prec UMINUS
  ;

%%

vector<ClassDecl> classes;

void yyerror(const char *s) {
    cerr << "Syntax error: " << s << endl;
}

static yyFlexLexer lexer;

int yylex() {
    return lexer.yylex();
}

int main(int argc, char **argv) {
    cout << "Parsing..." << endl;

    int result = yyparse();
    if (result == 0) {
        cout << "Parsing completed successfully.\n";
        for (auto &cls : classes) {
            cout << "Class: " << cls.name << endl;
            for (auto &v : cls.vars)
                cout << "  Var " << v.name << " : " << v.type << endl;
        }
    } else {
        cout << "Parsing failed.\n";
    }

    return 0;
}
