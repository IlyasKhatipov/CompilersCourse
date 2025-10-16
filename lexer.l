%option noyywrap
%option c++

%{
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include "parser.tab.hh"

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

vector<unique_ptr<Token>> tokens;
int currentLine = 1;
int currentCol = 1;

static inline void addToken(unique_ptr<Token> t) { tokens.push_back(move(t)); }

#define RET(t) do { return t; } while(0)
%}

DIGIT   [0-9]
LETTER  [A-Za-z_]

%%

[ \t]+            { currentCol += yyleng; }
\r\n              { currentLine++; currentCol = 1; }
\n                { currentLine++; currentCol = 1; }
\r                { currentLine++; currentCol = 1; }

"class"      { int start=currentCol; currentCol+=yyleng; addToken(make_unique<KeywordToken>("class", currentLine,start,currentCol-1)); RET(CLASS); }
"is"         { int start=currentCol; currentCol+=yyleng; addToken(make_unique<KeywordToken>("is", currentLine,start,currentCol-1)); RET(IS); }
"end"        { int start=currentCol; currentCol+=yyleng; addToken(make_unique<KeywordToken>("end", currentLine,start,currentCol-1)); RET(END); }
"var"        { int start=currentCol; currentCol+=yyleng; addToken(make_unique<KeywordToken>("var", currentLine,start,currentCol-1)); RET(VAR); }

"extends"|"method"|"this"|"return"|"if"|"then"|"else"|"while"|"loop" {
    int start=currentCol; currentCol+=yyleng; addToken(make_unique<KeywordToken>(yytext, currentLine,start,currentCol-1)); yylval.str=strdup(yytext); RET(KEYWORD);
}

"true"|"false" {
    int start=currentCol; currentCol+=yyleng; addToken(make_unique<BooleanToken>(yytext,currentLine,start,currentCol-1)); yylval.str=strdup(yytext); RET(BOOLEAN);
}

{LETTER}({LETTER}|{DIGIT})* {
    int start=currentCol;
    currentCol += yyleng;
    addToken(make_unique<IdentifierToken>(string(yytext),currentLine,start,currentCol-1));
    yylval.str = strdup(yytext);
    RET(IDENTIFIER);
}

{DIGIT}+"."{DIGIT}+ {
    int start=currentCol; currentCol+=yyleng; addToken(make_unique<RealToken>(stod(string(yytext)),currentLine,start,currentCol-1)); yylval.str=strdup(yytext); RET(REAL);
}

{DIGIT}+ {
    int start=currentCol; currentCol+=yyleng; addToken(make_unique<IntegerToken>(stoi(string(yytext)),currentLine,start,currentCol-1)); yylval.str=strdup(yytext); RET(INTEGER);
}

\"([^\"\\\n]|\\.)*\" {
    int start=currentCol; currentCol+=yyleng;
    string s(yytext);
    if (s.size()>=2) s=s.substr(1,s.size()-2);
    addToken(make_unique<StringToken>(s,currentLine,start,currentCol-1));
    yylval.str=strdup(s.c_str());
    RET(STRING);
}

{LETTER}({LETTER}|{DIGIT})* {
    int start=currentCol; currentCol+=yyleng; addToken(make_unique<IdentifierToken>(yytext,currentLine,start,currentCol-1)); yylval.str=strdup(yytext); RET(IDENTIFIER);
}

":="|"=>" {
    int start=currentCol; currentCol+=yyleng;
    addToken(make_unique<SymbolToken>(yytext,currentLine,start,currentCol-1));
    yylval.str = strdup(yytext);
    RET(SYMBOL);
}

[.,:();\[\]\{\}] {
    int start=currentCol; currentCol+=yyleng;
    addToken(make_unique<SymbolToken>(yytext,currentLine,start,currentCol-1));
    return yytext[0];
}

. {
    int start=currentCol; currentCol+=yyleng;
    cerr << "Unknown char at line " << currentLine << " col " << start << ": '" << yytext[0] << "'\n";
    addToken(make_unique<UnknownToken>(yytext,currentLine,start,currentCol-1));
}

%%


