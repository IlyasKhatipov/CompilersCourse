// tokens.hpp
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdint>

enum class TokenKind {
    // Ключевые
    CLASS, VAR, IS, END,
    // Идентификаторы / типы / литералы
    IDENTIFIER, TYPE_NAME, INT_LITERAL,
    // Знаки
    COLON, SEMICOLON, COMMA,
    LPAREN, RPAREN, LBRACE, RBRACE,
    ASSIGN, PLUS, MINUS, STAR, SLASH,
    END_OF_FILE
};

struct Token {
    TokenKind   kind;
    std::string lexeme;
    int         line;
    int         column;

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

struct TypeNameToken : Token {
    TypeNameToken(const std::string& lx, int ln, int col)
        : Token(TokenKind::TYPE_NAME, lx, ln, col) {}
};

struct IntegerToken : Token {
    std::int64_t value;
    IntegerToken(const std::string& lx, std::int64_t v, int ln, int col)
        : Token(TokenKind::INT_LITERAL, lx, ln, col), value(v) {}
};

struct SymbolToken : Token {
    SymbolToken(TokenKind k, const std::string& lx, int ln, int col)
        : Token(k, lx, ln, col) {}
};

inline const char* TokenKindToString(TokenKind k) {
    switch (k) {
        case TokenKind::CLASS: return "CLASS";
        case TokenKind::VAR: return "VAR";
        case TokenKind::IS: return "IS";
        case TokenKind::END: return "END";
        case TokenKind::IDENTIFIER: return "IDENTIFIER";
        case TokenKind::TYPE_NAME: return "TYPE_NAME";
        case TokenKind::INT_LITERAL: return "INT_LITERAL";
        case TokenKind::COLON: return "COLON";
        case TokenKind::SEMICOLON: return "SEMICOLON";
        case TokenKind::COMMA: return "COMMA";
        case TokenKind::LPAREN: return "LPAREN";
        case TokenKind::RPAREN: return "RPAREN";
        case TokenKind::LBRACE: return "LBRACE";
        case TokenKind::RBRACE: return "RBRACE";
        case TokenKind::ASSIGN: return "ASSIGN";
        case TokenKind::PLUS: return "PLUS";
        case TokenKind::MINUS: return "MINUS";
        case TokenKind::STAR: return "STAR";
        case TokenKind::SLASH: return "SLASH";
        case TokenKind::END_OF_FILE: return "EOF";
    }
    return "UNKNOWN";
}

// Хранилище всех токенов для отладки (inline, чтобы не требовать .cpp)
inline std::vector<std::unique_ptr<Token>> g_tokens;

inline void EmitToken(std::unique_ptr<Token> t) {
    std::cout << TokenKindToString(t->kind);
    if (t->kind == TokenKind::IDENTIFIER || t->kind == TokenKind::TYPE_NAME) {
        std::cout << "(" << t->lexeme << ")";
    } else if (t->kind == TokenKind::INT_LITERAL) {
        auto* it = static_cast<IntegerToken*>(t.get());
        std::cout << "(" << it->value << ")";
    }
    std::cout << "\n";
    g_tokens.emplace_back(std::move(t));
}
