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
#define TRACE(name) cerr << "LEX: " << name << " [" << (yytext?yytext:"") << "] at " << currentLine << ":" << currentCol << "\n";
%}

DIGIT   [0-9]
LETTER  [A-Za-z_]

%%

[ \t]+            { currentCol += yyleng; }
\r\n              { currentLine++; currentCol = 1; }
\n                { currentLine++; currentCol = 1; }
\r                { currentLine++; currentCol = 1; }

"class"      { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("CLASS"); RET(CLASS); }
"is"         { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("IS"); RET(IS); }
"end"        { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("END"); RET(END); }
"var"        { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("VAR"); RET(VAR); }
"extends"    { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("EXTENDS"); RET(EXTENDS); }
"method"     { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("METHOD"); RET(METHOD); }
"this"       { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("THIS"); RET(THIS); }
"return"     { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("RETURN"); RET(RETURN); }
"if"         { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("IF"); RET(IF); }
"then"       { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("THEN"); RET(THEN); }
"else"       { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("ELSE"); RET(ELSE); }
"while"      { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("WHILE"); RET(WHILE); }
"loop"       { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("LOOP"); RET(LOOP); }

"true"|"false" { currentCol += yyleng; yylval.str = strdup(yytext); TRACE("BOOLEAN"); RET(BOOLEAN); }

{LETTER}({LETTER}|{DIGIT})* {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    TRACE("IDENTIFIER");
    RET(IDENTIFIER);
}

"=>" {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    TRACE("ARROW");
    RET(ARROW);
}

{DIGIT}+"."{DIGIT}+ {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    TRACE("REAL");
    RET(REAL);
}

{DIGIT}+ {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    TRACE("INTEGER");
    RET(INTEGER);
}

\"([^\"\\\n]|\\.)*\" {
    string s(yytext);
    if (s.size() >= 2) s = s.substr(1, s.size() - 2);
    currentCol += yyleng;
    yylval.str = strdup(s.c_str());
    TRACE("STRING");
    RET(STRING);
}

":=" {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    TRACE("SYMBOL(:=)");
    RET(SYMBOL);
}

[+\-*/] {
    currentCol += yyleng;
    yylval.str = strdup(yytext);
    TRACE("OP");
    return yytext[0];
}

[.,:();\[\]\{\}] {
    currentCol += yyleng;
    TRACE(string("SYM:")+string(yytext).c_str());
    return yytext[0];
}

. {
    currentCol += yyleng;
    TRACE("UNKNOWN");
}

%%
