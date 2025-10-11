%{
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Объявим yylex(), который будет вызываться из Flex
int yylex();
void yyerror(const char *s);

// Простая структура для AST (можно потом вынести в отдельный файл)
struct VarDecl {
    string name;
    string type;
};

struct ClassDecl {
    string name;
    vector<VarDecl> vars;
};

vector<ClassDecl> classes;
%}

// Типы значений
%union {
    char* str;
    VarDecl* var;
    ClassDecl* cls;
    vector<VarDecl>* varList;
}

// Терминалы
%token <str> IDENTIFIER
%token <str> KEYWORD
%token <str> SYMBOL
%token <str> STRING
%token <str> BOOLEAN
%token <str> INTEGER
%token <str> REAL

// Правила будут использовать только часть этих токенов
%type <cls> class_decl
%type <varList> var_decl_list
%type <var> var_decl

// Символ начала
%start program

%%

// ======= Грамматика =======

program:
    class_list
    ;

class_list:
      class_decl
    | class_list class_decl
    ;

class_decl:
    KEYWORD IDENTIFIER KEYWORD class_body KEYWORD
    {
        // ожидаем: class <id> is <body> end
        if (std::string($1) != "class" || std::string($3) != "is" || std::string($5) != "end") {
            yyerror("Invalid class declaration syntax");
        } else {
            ClassDecl cls;
            cls.name = $2;
            cls.vars = *$4;
            classes.push_back(cls);
        }
    }
    ;

class_body:
      var_decl_list
    ;

var_decl_list:
      var_decl
    | var_decl_list var_decl
    {
        $$ = $1;
        $1->push_back(*$2);
    }
    ;

var_decl:
    KEYWORD IDENTIFIER SYMBOL IDENTIFIER
    {
        // ожидаем: var x : Int
        if (std::string($1) != "var" || std::string($3) != ":")
            yyerror("Invalid variable declaration syntax");
        else {
            $$ = new VarDecl{$2, $4};
        }
    }
    ;

%%

// ======= Вспомогательные функции =======

void yyerror(const char *s) {
    cerr << "Syntax error: " << s << endl;
}

int main() {
    cout << "Parsing..." << endl;
    if (yyparse() == 0) {
        cout << "Parsing completed successfully.\n";
        for (auto &cls : classes) {
            cout << "Class: " << cls.name << endl;
            for (auto &v : cls.vars)
                cout << "  Var " << v.name << " : " << v.type << endl;
        }
    }
    return 0;
}
