%option noyywrap

%{
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
#include "parser.hpp"
#include "ast.h"
#undef yyFlexLexer
extern YYSTYPE yylval;
using namespace std;

class Token {
public:
    int line;
    int startCol;
    int endCol;

    Token(int l, int s, int e) : line(l), startCol(s), endCol(e) {}
    virtual ~Token() = default;
    virtual void print() const = 0;
};

class KeywordToken : public Token {
public:
    string value;
    KeywordToken(const string& val, int l, int s, int e) : Token(l,s,e), value(val) {}
    void print() const override { cout << "KEYWORD(" << value << ")\n"; }
};

class IdentifierToken : public Token {
public:
    string name;
    IdentifierToken(const string& n, int l, int s, int e) : Token(l,s,e), name(n) {}
    void print() const override { cout << "IDENTIFIER(" << name << ")\n"; }
};

class IntegerToken : public Token {
public:
    int value;
    IntegerToken(int v, int l, int s, int e) : Token(l,s,e), value(v) {}
    void print() const override { cout << "INTEGER(" << value << ")\n"; }
};

class RealToken : public Token {
public:
    double value;
    RealToken(double v, int l, int s, int e) : Token(l,s,e), value(v) {}
    void print() const override { cout << "REAL(" << value << ")\n"; }
};

class BooleanToken : public Token {
public:
    string value;
    BooleanToken(const string& v, int l, int s, int e) : Token(l,s,e), value(v) {}
    void print() const override { cout << "BOOLEAN(" << value << ")\n"; }
};

class StringToken : public Token {
public:
    string value;
    StringToken(const string& v, int l, int s, int e) : Token(l,s,e), value(v) {}
    void print() const override { cout << "STRING(\"" << value << "\")\n"; }
};

class SymbolToken : public Token {
public:
    string symbol;
    SymbolToken(const string& s, int l, int sc, int ec) : Token(l,sc,ec), symbol(s) {}
    void print() const override { cout << "SYMBOL(" << symbol << ")\n"; }
};

class UnknownToken : public Token {
public:
    string text;
    UnknownToken(const string& t, int l, int s, int e) : Token(l,s,e), text(t) {}
    void print() const override { cout << "UNKNOWN(" << text << ")\n"; }
};

int currentLine = 1;
int currentCol = 1;

%}

%%

[ \t]+              { currentCol += yyleng; /* игнорируем */ }
\r?\n               { currentLine++; currentCol = 1; }

"if"|"else"|"while"|"for"|"return"|"true"|"false"|"class"|"extends"|"is"|"end"|"var"|"method"|"this"|"then"|"loop" {
    yylval.str = strdup(yytext);
    int startCol = currentCol;
    currentCol += yyleng;
    if (strcmp(yytext, "if") == 0) return IF;
    if (strcmp(yytext, "else") == 0) return ELSE;
    if (strcmp(yytext, "while") == 0) return WHILE;
    if (strcmp(yytext, "for") == 0) return LOOP; // если надо FOR - добавь
    if (strcmp(yytext, "return") == 0) return RETURN;
    if (strcmp(yytext, "true") == 0) return TRUE;
    if (strcmp(yytext, "false") == 0) return FALSE;
    if (strcmp(yytext, "class") == 0) return CLASS;
    if (strcmp(yytext, "extends") == 0) return EXTENDS;
    if (strcmp(yytext, "is") == 0) return IS;
    if (strcmp(yytext, "end") == 0) return END;
    if (strcmp(yytext, "var") == 0) return VAR;
    if (strcmp(yytext, "method") == 0) return METHOD;
    if (strcmp(yytext, "this") == 0) return THIS;
    if (strcmp(yytext, "then") == 0) return THEN;
    if (strcmp(yytext, "loop") == 0) return LOOP;
    return IDENTIFIER; // если не keyword — идентификатор
}

[0-9]+\.[0-9]+ {
    yylval.str = strdup(yytext);
    int startCol = currentCol;
    currentCol += yyleng;
    return REAL;
}

[0-9]+ {
    yylval.str = strdup(yytext);
    int startCol = currentCol;
    currentCol += yyleng;
    return INTEGER;
}

[A-Za-z_][A-Za-z0-9_]* {
    yylval.str = strdup(yytext);
    int startCol = currentCol;
    currentCol += yyleng;
    return IDENTIFIER;
}

\"([^\\\"]|\\.)*\" {
    string val(yytext + 1, yyleng - 2);
    yylval.str = strdup(val.c_str());
    int startCol = currentCol;
    currentCol += yyleng;
    return STRING;
}

(:=|=>|[+\-*/=(){};,<>:\[\]]) {
    yylval.str = strdup(yytext);
    int startCol = currentCol;
    currentCol += yyleng;
    if (strcmp(yytext, ":") == 0) return COLON;
    if (strcmp(yytext, ";") == 0) return SEMI;
    if (strcmp(yytext, "(") == 0) return LPAREN;
    if (strcmp(yytext, ")") == 0) return RPAREN;
    if (strcmp(yytext, ",") == 0) return COMMA;
    if (strcmp(yytext, ".") == 0) return DOT;
    if (strcmp(yytext, ":=") == 0) return ASSIGN;
    if (strcmp(yytext, "=>") == 0) return ARROW;
    return SYMBOL;
}

. {
    yylval.str = strdup(yytext);
    int startCol = currentCol;
    currentCol += yyleng;
    return UNKNOWN;
}

%%