%option noyywrap
%option c++

%{
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>


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

%}


DIGIT   [0-9]
LETTER  [A-Za-z_]

%%

[ \t]+            { currentCol += yyleng; }
\r\n              { currentLine++; currentCol = 1; }
\n                { currentLine++; currentCol = 1; }
\r                { currentLine++; currentCol = 1; }


"class"|"extends"|"is"|"end"|"var"|"method"|"this"|"return"|"if"|"then"|"else"|"while"|"loop" {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<KeywordToken>(string(yytext), currentLine, start, currentCol - 1));
}


"true"|"false" {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<BooleanToken>(string(yytext), currentLine, start, currentCol - 1));
}


{DIGIT}+\.{DIGIT}+ {
    int start = currentCol;
    currentCol += yyleng;
    if (yytext[yyleng] == '.') {
        addToken(make_unique<UnknownToken>(string(yytext), currentLine, start, currentCol - 1));
        cerr << "Invalid real number at line " << currentLine << ", col " << start << ": " << yytext << "\n";
    } else {
        addToken(make_unique<RealToken>(stod(string(yytext)), currentLine, start, currentCol - 1));
    }
}

{DIGIT}+(\.{DIGIT}+)+ {
    int start = currentCol;
    currentCol += yyleng;
    string text(yytext);
    size_t countDots = std::count(text.begin(), text.end(), '.');
    if (countDots > 1) {
        addToken(make_unique<UnknownToken>(text, currentLine, start, currentCol - 1));
        cerr << "Invalid real number at line " << currentLine << ", col " << start << ": " << text << "\n";
    } else {
        addToken(make_unique<RealToken>(stod(text), currentLine, start, currentCol - 1));
    }
}



{DIGIT}+ {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<IntegerToken>(stoi(string(yytext)), currentLine, start, currentCol - 1));
}


\"([^"\\\n]|\\.)*\" {
    int start = currentCol;
    currentCol += yyleng;
    string s(yytext);
    if (s.size() >= 2) s = s.substr(1, s.size() - 2); /* remove surrounding " */
    /* Unescape common sequences */
    string unescaped;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            char c = s[i+1];
            switch (c) {
                case 'n': unescaped.push_back('\n'); break;
                case 't': unescaped.push_back('\t'); break;
                case 'r': unescaped.push_back('\r'); break;
                case '\\': unescaped.push_back('\\'); break;
                case '"': unescaped.push_back('"'); break;
                default: unescaped.push_back(c); break;
            }
            ++i;
        } else {
            unescaped.push_back(s[i]);
        }
    }
    addToken(make_unique<StringToken>(unescaped, currentLine, start, currentCol - 1));
}


{LETTER}({LETTER}|{DIGIT})* {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<IdentifierToken>(string(yytext), currentLine, start, currentCol - 1));
}


":="|"=>" {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<SymbolToken>(string(yytext), currentLine, start, currentCol - 1));
}


[.,:()\[\]\{\}] {
    int start = currentCol;
    currentCol += yyleng;
    addToken(make_unique<SymbolToken>(string(yytext), currentLine, start, currentCol - 1));
}


. {
    int start = currentCol;
    /* yytext may be multichar for some patterns, but here it's single char */
    currentCol += yyleng;
    cerr << "Unknown char at line " << currentLine << " col " << start << ": '" << yytext[0] << "'\n";
    addToken(make_unique<UnknownToken>(string(yytext), currentLine, start, currentCol - 1));
}

%%

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

    while (lexer.yylex() != 0) {

    }

    for (auto &t : tokens) t->print();

    return 0;
}
