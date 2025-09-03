%option noyywrap
%option c++

%{
#include <iostream>
#include <string>
#include <memory>
#include <vector>

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
    KeywordToken(const string& val, int l, int s, int e)
        : Token(l, s, e), value(val) {}

    void print() const override {
        cout << "KEYWORD(" << value << ") at line " << line
             << ", cols " << startCol << "-" << endCol << "\n";
    }
};

class IdentifierToken : public Token {
public:
    string name;
    IdentifierToken(const string& n, int l, int s, int e)
        : Token(l, s, e), name(n) {}

    void print() const override {
        cout << "IDENTIFIER(" << name << ") at line " << line
             << ", cols " << startCol << "-" << endCol << "\n";
    }
};

class IntegerToken : public Token {
public:
    int value;
    IntegerToken(int v, int l, int s, int e)
        : Token(l, s, e), value(v) {}

    void print() const override {
        cout << "INTEGER(" << value << ") at line " << line
             << ", cols " << startCol << "-" << endCol << "\n";
    }
};

class RealToken : public Token {
public:
    double value;
    RealToken(double v, int l, int s, int e)
        : Token(l, s, e), value(v) {}

    void print() const override {
        cout << "REAL(" << value << ") at line " << line
             << ", cols " << startCol << "-" << endCol << "\n";
    }
};

class BooleanToken : public Token {
public:
    string value;
    BooleanToken(const string& v, int l, int s, int e)
        : Token(l, s, e), value(v) {}

    void print() const override {
        cout << "BOOLEAN(" << value << ") at line " << line
             << ", cols " << startCol << "-" << endCol << "\n";
    }
};

class SymbolToken : public Token {
public:
    string symbol;
    SymbolToken(const string& s, int l, int sc, int ec)
        : Token(l, sc, ec), symbol(s) {}

    void print() const override {
        cout << "SYMBOL(" << symbol << ") at line " << line
             << ", cols " << startCol << "-" << endCol << "\n";
    }
};

class UnknownToken : public Token {
public:
    string text;
    UnknownToken(const string& t, int l, int s, int e)
        : Token(l, s, e), text(t) {}

    void print() const override {
        cout << "UNKNOWN(" << text << ") at line " << line
             << ", cols " << startCol << "-" << endCol << "\n";
    }
};

vector<unique_ptr<Token>> tokens;
int currentLine = 1;
int currentCol = 1;

#define YY_USER_ACTION \
    yylloc->first_column = currentCol; \
    yylloc->last_column = currentCol + yyleng - 1; \
    currentCol += yyleng;
%}

DIGIT   [0-9]
LETTER  [A-Za-z_]

%%

"class"|"extends"|"is"|"end"|"var"|"method"|"this"|"return"|"if"|"then"|"else"|"while"|"loop" {
    int start = currentCol;
    currentCol += yyleng;
    tokens.push_back(make_unique<KeywordToken>(yytext, currentLine, start, currentCol - 1));
}

"true"|"false" {
    int start = currentCol;
    currentCol += yyleng;
    tokens.push_back(make_unique<BooleanToken>(yytext, currentLine, start, currentCol - 1));
}

{LETTER}({LETTER}|{DIGIT})* {
    int start = currentCol;
    currentCol += yyleng;
    tokens.push_back(make_unique<IdentifierToken>(yytext, currentLine, start, currentCol - 1));
}

{DIGIT}+"."{DIGIT}+ {
    int start = currentCol;
    currentCol += yyleng;
    tokens.push_back(make_unique<RealToken>(stod(yytext), currentLine, start, currentCol - 1));
}

{DIGIT}+ {
    int start = currentCol;
    currentCol += yyleng;
    tokens.push_back(make_unique<IntegerToken>(stoi(yytext), currentLine, start, currentCol - 1));
}

":="|"=>"|"."|","|":"|"("|")"|"["|"]"|"{"|"}" {
    int start = currentCol;
    currentCol += yyleng;
    tokens.push_back(make_unique<SymbolToken>(yytext, currentLine, start, currentCol - 1));
}

[ \t]+       { currentCol += yyleng; }
"\r\n"       { currentLine++; currentCol = 1; }
"\n"         { currentLine++; currentCol = 1; }
"\r"         { currentLine++; currentCol = 1; }

. {
    int start = currentCol;
    currentCol += yyleng;
    tokens.push_back(make_unique<UnknownToken>(yytext, currentLine, start, currentCol - 1));
}

%%

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

    for (auto& t : tokens) {
        t->print();
    }

    return 0;
}