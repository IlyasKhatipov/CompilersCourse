%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "parser.hpp"
#include "tokens.hpp"

int yycolumn = 1;
extern int yylineno;

static inline void push_kw(TokenKind k, const char* text) {
    EmitToken(std::make_unique<KeywordToken>(k, text, yylineno, yycolumn));
    yycolumn += yyleng;
}
static inline void push_sym(TokenKind k, const char* text) {
    EmitToken(std::make_unique<SymbolToken>(k, text, yylineno, yycolumn));
    yycolumn += yyleng;
}
%}

%option noyywrap
%option nodefault
%option yylineno

ID      [A-Za-z_][A-Za-z0-9_]*
INT     [0-9]+
WS      [ \t\r]+

%%

"class"     { push_kw(TokenKind::CLASS, yytext); return CLASS; }
"var"       { push_kw(TokenKind::VAR,   yytext); return VAR; }
"is"        { push_kw(TokenKind::IS,    yytext); return IS; }
"end"       { push_kw(TokenKind::END,   yytext); return END; }

"Int"       { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }
"String"    { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }
"Bool"      { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }
"Float"     { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }

{ID}        { EmitToken(std::make_unique<IdentifierToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return IDENTIFIER; }

{INT}       { long long v = atoll(yytext);
              EmitToken(std::make_unique<IntegerToken>(yytext, v, yylineno, yycolumn));
              yylval.ival = v; yycolumn += yyleng; return INT_LITERAL; }

":"         { push_sym(TokenKind::COLON,      yytext); return COLON; }
";"         { push_sym(TokenKind::SEMICOLON,  yytext); return SEMICOLON; }
","         { push_sym(TokenKind::COMMA,      yytext); return COMMA; }
"("         { push_sym(TokenKind::LPAREN,     yytext); return LPAREN; }
")"         { push_sym(TokenKind::RPAREN,     yytext); return RPAREN; }
"{"         { push_sym(TokenKind::LBRACE,     yytext); return LBRACE; }
"}"         { push_sym(TokenKind::RBRACE,     yytext); return RBRACE; }
"="         { push_sym(TokenKind::ASSIGN,     yytext); return ASSIGN; }
"+"         { push_sym(TokenKind::PLUS,       yytext); return PLUS; }
"-"         { push_sym(TokenKind::MINUS,      yytext); return MINUS; }
"*"         { push_sym(TokenKind::STAR,       yytext); return STAR; }
"/"         { push_sym(TokenKind::SLASH,      yytext); return SLASH; }

"//".*      { yycolumn += yyleng; }
{WS}        { yycolumn += yyleng; }
\n          { yycolumn = 1; }

.           { std::fprintf(stderr, "Unknown char '%s' at %d:%d\n", yytext, yylineno, yycolumn);
              yycolumn += yyleng; }

%%
