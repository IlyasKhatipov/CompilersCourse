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

%union {
    char* str;
    struct VarDecl* var;
    struct ClassDecl* cls;
    vector<VarDecl>* varList;
}

/* Новые токены для ключевых слов */
%token <str> IDENTIFIER
%token <str> STRING BOOLEAN INTEGER REAL SYMBOL
%token CLASS IS END VAR
%token <str> KEYWORD

%type <cls> class_decl
%type <varList> var_decl_list
%type <varList> class_body
%type <var> var_decl

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
    ;

class_body:
      var_decl_list
    | /* empty */
      { $$ = new vector<VarDecl>(); }
    ;

var_decl_list:
      var_decl ';'
      {
          $$ = new vector<VarDecl>();
          $$->push_back(*$1);
          delete $1;
      }
    | var_decl_list var_decl ';'
      {
          $$ = $1;
          $$->push_back(*$2);
          delete $2;
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
