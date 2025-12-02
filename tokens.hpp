#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdint>

enum class TokenKind {
    // Keywords (только из грамматики)
    CLASS, EXTENDS, IS, END,
    VAR, METHOD, THIS,
    WHILE, LOOP, IF, THEN, ELSE,
    RETURN,
    TRUE, FALSE,                     // Булевы литералы
    
    // Identifiers and literals
    IDENTIFIER,                      // Включая имена стандартных классов
    INTEGER_LITERAL, REAL_LITERAL,   // Числовые литералы
    
    // Symbols
    COLON, COMMA, DOT,
    LPAREN, RPAREN, LBRACKET, RBRACKET,
    ASSIGN, ARROW,
    END_OF_FILE
};

struct Token {
    TokenKind kind;
    std::string lexeme;
    int line;
    int column;
    Token(TokenKind k, std::string lx, int ln, int col)
        : kind(k), lexeme(std::move(lx)), line(ln), column(col) {}
    virtual ~Token() = default;
};

struct KeywordToken : Token {
    KeywordToken(TokenKind k, const std::string& lx, int ln, int col)
        : Token(k, lx, ln, col) {}
};

struct IdentifierToken : Token {
    IdentifierToken(const std::string& lx, int ln, int col)
        : Token(TokenKind::IDENTIFIER, lx, ln, col) {}
};

struct IntegerToken : Token {
    std::int64_t value;
    IntegerToken(const std::string& lx, std::int64_t v, int ln, int col)
        : Token(TokenKind::INTEGER_LITERAL, lx, ln, col), value(v) {}
};

struct RealToken : Token {
    double value;
    RealToken(const std::string& lx, double v, int ln, int col)
        : Token(TokenKind::REAL_LITERAL, lx, ln, col), value(v) {}
};

struct SymbolToken : Token {
    SymbolToken(TokenKind k, const std::string& lx, int ln, int col)
        : Token(k, lx, ln, col) {}
};

inline const char* TokenKindToString(TokenKind k) {
    switch (k) {
        case TokenKind::CLASS: return "CLASS";
        case TokenKind::EXTENDS: return "EXTENDS";
        case TokenKind::IS: return "IS";
        case TokenKind::END: return "END";
        case TokenKind::VAR: return "VAR";
        case TokenKind::METHOD: return "METHOD";
        case TokenKind::THIS: return "THIS";
        case TokenKind::WHILE: return "WHILE";
        case TokenKind::LOOP: return "LOOP";
        case TokenKind::IF: return "IF";
        case TokenKind::THEN: return "THEN";
        case TokenKind::ELSE: return "ELSE";
        case TokenKind::RETURN: return "RETURN";
        case TokenKind::TRUE: return "TRUE";
        case TokenKind::FALSE: return "FALSE";
        case TokenKind::IDENTIFIER: return "IDENTIFIER";
        case TokenKind::INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TokenKind::REAL_LITERAL: return "REAL_LITERAL";
        case TokenKind::COLON: return "COLON";
        case TokenKind::COMMA: return "COMMA";
        case TokenKind::DOT: return "DOT";
        case TokenKind::LPAREN: return "LPAREN";
        case TokenKind::RPAREN: return "RPAREN";
        case TokenKind::LBRACKET: return "LBRACKET";
        case TokenKind::RBRACKET: return "RBRACKET";
        case TokenKind::ASSIGN: return "ASSIGN";
        case TokenKind::ARROW: return "ARROW";
        case TokenKind::END_OF_FILE: return "EOF";
    }
    return "UNKNOWN";
}

inline std::vector<std::unique_ptr<Token>> g_tokens;

inline void EmitToken(std::unique_ptr<Token> t) {
    std::cout << TokenKindToString(t->kind);
    if (t->kind == TokenKind::IDENTIFIER) {
        std::cout << "(" << t->lexeme << ")";
    } else if (t->kind == TokenKind::INTEGER_LITERAL) {
        auto* it = static_cast<IntegerToken*>(t.get());
        std::cout << "(" << it->value << ")";
    } else if (t->kind == TokenKind::REAL_LITERAL) {
        auto* rt = static_cast<RealToken*>(t.get());
        std::cout << "(" << rt->value << ")";
    }
    std::cout << "\n";
    g_tokens.emplace_back(std::move(t));
}