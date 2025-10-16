%option noyywrap
%option c++

%{
#include <iostream>
#include <string>
#include <cstring>
#include "parser.tab.hh"

using namespace std;

int currentLine = 1;
int currentCol = 1;

#define RET(t) do { return t; } while(0)
%}

DIGIT   [0-9]
LETTER  [A-Za-z_]

%%

[ \t]+            { currentCol += yyleng; }
\r\n              { currentLine++; currentCol = 1; }
\n                { currentLine++; currentCol = 1; }
\r                { currentLine++; currentCol = 1; }

"class"      { currentCol += yyleng; yylval.str = strdup(yytext); RET(CLASS); }
"is"         { currentCol += yyleng; yylval.str = strdup(yytext); RET(IS); }
"end"        { currentCol += yyleng; yylval.str = strdup(yytext); RET(END); }
"var"        { currentCol += yyleng; yylval.str = strdup(yytext); RET(VAR); }
"extends"    { currentCol += yyleng; yylval.str = strdup(yytext); RET(EXTENDS); }
"method"     { currentCol += yyleng; yylval.str = strdup(yytext); RET(METHOD); }
"this"       { currentCol += yyleng; yylval.str = strdup(yytext); RET(THIS); }
"return"     { currentCol += yyleng; yylval.str = strdup(yytext); RET(RETURN); }
"if"         { currentCol += yyleng; yylval.str = strdup(yytext); RET(IF); }
"then"       { currentCol += yyleng; yylval.str = strdup(yytext); RET(THEN); }
"else"       { currentCol += yyleng; yylval.str = strdup(yytext); RET(ELSE); }
"while"      { currentCol += yyleng; yylval.str = strdup(yytext); RET(WHILE); }
"loop"       { currentCol += yyleng; yylval.str = strdup(yytext); RET(LOOP); }

"true"|"false" { currentCol += yyleng; yylval.str = strdup(yytext); RET(BOOLEAN); }

{LETTER}({LETTER}|{DIGIT})* {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    RET(IDENTIFIER);
}

"=>" {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    RET(ARROW);
}

{DIGIT}+"."{DIGIT}+ {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    RET(REAL);
}

{DIGIT}+ {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    RET(INTEGER);
}

\"([^\"\\\n]|\\.)*\" {
    string s(yytext);
    if (s.size() >= 2) s = s.substr(1, s.size() - 2);
    currentCol += yyleng;
    yylval.str = strdup(s.c_str());
    RET(STRING);
}

":=" {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    RET(SYMBOL);
}

[+\-*/] {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    return yytext[0];
}

[.,:();\[\]\{\}] {
    currentCol += yyleng;
    return yytext[0];
}

. {
    currentCol += yyleng;
}

%%
