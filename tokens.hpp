#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdint>

enum class TokenKind {
    CLASS, VAR, IS, END,
    METHOD, RETURN, IF, THEN, ELSE,
    WHILE, DO,
    TRUEKW, FALSEKW,
    IDENTIFIER, TYPE_NAME, INT_LITERAL, STRING_LITERAL,
    COLON, SEMICOLON, COMMA,
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
    ASSIGN, ARROW, PLUS, MINUS, STAR, SLASH,
    DOT, GT, LT, EQEQ, EQUAL,
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

struct TypeNameToken : Token {
    TypeNameToken(const std::string& lx, int ln, int col)
        : Token(TokenKind::TYPE_NAME, lx, ln, col) {}
};

struct IntegerToken : Token {
    std::int64_t value;
    IntegerToken(const std::string& lx, std::int64_t v, int ln, int col)
        : Token(TokenKind::INT_LITERAL, lx, ln, col), value(v) {}
};

struct StringToken : Token {
    std::string value;
    StringToken(const std::string& lx, std::string v, int ln, int col)
        : Token(TokenKind::STRING_LITERAL, lx, ln, col), value(std::move(v)) {}
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
        case TokenKind::METHOD: return "METHOD";
        case TokenKind::RETURN: return "RETURN";
        case TokenKind::IF: return "IF";
        case TokenKind::THEN: return "THEN";
        case TokenKind::ELSE: return "ELSE";
        case TokenKind::WHILE: return "WHILE";
        case TokenKind::DO: return "DO";
        case TokenKind::TRUEKW: return "TRUE";
        case TokenKind::FALSEKW: return "FALSE";
        case TokenKind::IDENTIFIER: return "IDENTIFIER";
        case TokenKind::TYPE_NAME: return "TYPE_NAME";
        case TokenKind::INT_LITERAL: return "INT_LITERAL";
        case TokenKind::STRING_LITERAL: return "STRING_LITERAL";
        case TokenKind::COLON: return "COLON";
        case TokenKind::SEMICOLON: return "SEMICOLON";
        case TokenKind::COMMA: return "COMMA";
        case TokenKind::LPAREN: return "LPAREN";
        case TokenKind::RPAREN: return "RPAREN";
        case TokenKind::LBRACE: return "LBRACE";
        case TokenKind::RBRACE: return "RBRACE";
        case TokenKind::LBRACKET: return "LBRACKET";
        case TokenKind::RBRACKET: return "RBRACKET";
        case TokenKind::ASSIGN: return "ASSIGN";
        case TokenKind::ARROW: return "ARROW";
        case TokenKind::PLUS: return "PLUS";
        case TokenKind::MINUS: return "MINUS";
        case TokenKind::STAR: return "STAR";
        case TokenKind::SLASH: return "SLASH";
        case TokenKind::DOT: return "DOT";
        case TokenKind::GT: return "GT";
        case TokenKind::LT: return "LT";
        case TokenKind::EQEQ: return "EQEQ";
        case TokenKind::EQUAL: return "EQUAL";
        case TokenKind::END_OF_FILE: return "EOF";
    }
    return "UNKNOWN";
}

inline std::vector<std::unique_ptr<Token>> g_tokens;

inline void EmitToken(std::unique_ptr<Token> t) {
    std::cout << TokenKindToString(t->kind);
    if (t->kind == TokenKind::IDENTIFIER || t->kind == TokenKind::TYPE_NAME) {
        std::cout << "(" << t->lexeme << ")";
    } else if (t->kind == TokenKind::INT_LITERAL) {
        auto* it = static_cast<IntegerToken*>(t.get());
        std::cout << "(" << it->value << ")";
    } else if (t->kind == TokenKind::STRING_LITERAL) {
        std::cout << "(" << t->lexeme << ")";
    }
    std::cout << "\n";
    g_tokens.emplace_back(std::move(t));
}
