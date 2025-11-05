// tokens.hpp
#pragma once
#include <string>
#include <iostream>
#include <memory>

enum class TokenKind {
    Class, Is, Var, End,
    Identifier, TypeName,
    IntegerLiteral,
    Colon, Semicolon, Assign,
    LParen, RParen, Plus, Minus, Star, Slash,
    Dot,
};

struct Token {
    TokenKind kind;
    std::string lexeme;
    int line = 1;
    int column = 1;
    Token(TokenKind k, std::string lx, int ln=1, int col=1)
        : kind(k), lexeme(std::move(lx)), line(ln), column(col) {}
    virtual ~Token() = default;
    virtual std::string info() const { return lexeme; }
};

struct KeywordToken : Token {
    KeywordToken(TokenKind k, const std::string& lx, int ln, int col)
        : Token(k, lx, ln, col) {}
};

struct SymbolToken : Token {
    SymbolToken(TokenKind k, const std::string& lx, int ln, int col)
        : Token(k, lx, ln, col) {}
};

struct IdentifierToken : Token {
    IdentifierToken(const std::string& name, int ln, int col)
        : Token(TokenKind::Identifier, name, ln, col) {}
};

struct TypeToken : Token {
    TypeToken(const std::string& name, int ln, int col)
        : Token(TokenKind::TypeName, name, ln, col) {}
};

struct IntegerToken : Token {
    long long value;
    IntegerToken(long long v, const std::string& lx, int ln, int col)
        : Token(TokenKind::IntegerLiteral, lx, ln, col), value(v) {}
    std::string info() const override { return std::to_string(value); }
};

// Утилита для красивого имени токена
inline const char* tokenKindName(TokenKind k) {
    switch (k) {
        case TokenKind::Class: return "CLASS";
        case TokenKind::Is: return "IS";
        case TokenKind::Var: return "VAR";
        case TokenKind::End: return "END";
        case TokenKind::Identifier: return "IDENTIFIER";
        case TokenKind::TypeName: return "TYPE";
        case TokenKind::IntegerLiteral: return "INTEGER";
        case TokenKind::Colon: return "COLON";
        case TokenKind::Semicolon: return "SEMICOLON";
        case TokenKind::Assign: return "ASSIGN";
        case TokenKind::LParen: return "LPAREN";
        case TokenKind::RParen: return "RPAREN";
        case TokenKind::Plus: return "PLUS";
        case TokenKind::Minus: return "MINUS";
        case TokenKind::Star: return "STAR";
        case TokenKind::Slash: return "SLASH";
        case TokenKind::Dot: return "DOT";
    }
    return "UNKNOWN";
}

// Печать «следа» токенов из лексера
inline void printToken(const Token* t) {
    std::cout << tokenKindName(t->kind);
    if (t->kind == TokenKind::Identifier || t->kind == TokenKind::TypeName)
        std::cout << "(" << t->lexeme << ")";
    else if (t->kind == TokenKind::IntegerLiteral)
        std::cout << "(" << static_cast<const IntegerToken*>(t)->value << ")";
    std::cout << "\n";
}
