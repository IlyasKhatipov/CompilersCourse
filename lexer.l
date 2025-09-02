%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int intValue;
    double realValue;
    int boolean;
    char* string;
} yystype;

yystype yylval;

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}

DIGIT   [0-9]
LETTER  [A-Za-z_]

%%

"class"             { printf("CLASS\n"); }
"extends"           { printf("EXTENDS\n"); }
"is"                { printf("IS\n"); }
"end"               { printf("END\n"); }
"var"               { printf("VAR\n"); }
"method"            { printf("METHOD\n"); }
"this"              { printf("THIS\n"); }
"return"            { printf("RETURN\n"); }
"if"                { printf("IF\n"); }
"then"              { printf("THEN\n"); }
"else"              { printf("ELSE\n"); }
"while"             { printf("WHILE\n"); }
"loop"              { printf("LOOP\n"); }
"true"|"false"      { printf("BOOLEAN_LITERAL(%s)\n", yytext); }

{LETTER}({LETTER}|{DIGIT})*   { printf("IDENTIFIER(%s)\n", yytext); }

{DIGIT}+"."{DIGIT}+           { printf("REAL_LITERAL(%s)\n", yytext); }
{DIGIT}+                      { printf("INTEGER_LITERAL(%s)\n", yytext); }

":="                { printf("ASSIGN\n"); }
"=>"                { printf("ARROW\n"); }
"."                 { printf("DOT\n"); }
","                 { printf("COMMA\n"); }
":"                 { printf("COLON\n"); }
"("                 { printf("LPAREN\n"); }
")"                 { printf("RPAREN\n"); }
"["                 { printf("LBRACKET\n"); }
"]"                 { printf("RBRACKET\n"); }
"{"                 { printf("LBRACE\n"); }
"}"                 { printf("RBRACE\n"); }

[ \t\r\n]+   ;

.                   { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if(argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if(!file) {
            perror("File opening failed");
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}
