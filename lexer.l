%option noyywrap
%option c++

%{
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>

// ✅ ВОТ СЮДА вставляем include — сразу после стандартных инклудов:
#include "parser.tab.h"   // <- добавлено для связи с Bison

using namespace std;

// --- Твоя структура токенов (оставляем для отладки) ---
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

// --- Ключевые слова ---
"class"|"extends"|"is"|"end"|"var"|"method"|"this"|"return"|"if"|"then"|"else"|"while"|"loop" {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<KeywordToken>(string(yytext), currentLine, start, currentCol - 1));
    yylval.str = strdup(yytext);
    RET(KEYWORD);
}

// --- Булевые значения ---
"true"|"false" {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<BooleanToken>(string(yytext), currentLine, start, currentCol - 1));
    yylval.str = strdup(yytext);
    RET(BOOLEAN);
}

// --- Числа ---
{DIGIT}+\.{DIGIT}+ {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<RealToken>(stod(string(yytext)), currentLine, start, currentCol - 1));
    yylval.str = strdup(yytext);
    RET(REAL);
}

{DIGIT}+ {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<IntegerToken>(stoi(string(yytext)), currentLine, start, currentCol - 1));
    yylval.str = strdup(yytext);
    RET(INTEGER);
}

// --- Строки ---
\"([^"\\\n]|\\.)*\" {
    int start = currentCol;
    currentCol += yyleng;
    string s(yytext);
    if (s.size() >= 2) s = s.substr(1, s.size() - 2);
    addToken(make_unique<StringToken>(s, currentLine, start, currentCol - 1));
    yylval.str = strdup(s.c_str());
    RET(STRING);
}

// --- Идентификаторы ---
{LETTER}({LETTER}|{DIGIT})* {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<IdentifierToken>(string(yytext), currentLine, start, currentCol - 1));
    yylval.str = strdup(yytext);
    RET(IDENTIFIER);
}

// --- Символы ---
":="|"=>"|[.,:()\[\]\{\}] {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<SymbolToken>(string(yytext), currentLine, start, currentCol - 1));
    yylval.str = strdup(yytext);
    RET(SYMBOL);
}

// --- Остальное ---
. {
    int start = currentCol;
    currentCol += yyleng;
    cerr << "Unknown char at line " << currentLine << " col " << start << ": '" << yytext[0] << "'\n";
    addToken(make_unique<UnknownToken>(string(yytext), currentLine, start, currentCol - 1));
}

%%

// --- Точка входа ---
int main(int argc, char **argv) {
    yyFlexLexer lexer;

    std::ifstream file;
    if (argc > 1) {
        file.open(argv[1]);
        if (!file.is_open()) {
            perror("File opening failed");
            return 1;
        }
        lexer.switch_streams(&file, &std::cout);
    }

    yyparse();  // 🧠 теперь парсер управляет лексером

    for (auto &t : tokens) t->print();
    return 0;
}
