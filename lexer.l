%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
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
REAL    [0-9]+\.[0-9]+
WS      [ \t\r]+

%%

"class"     { push_kw(TokenKind::CLASS, yytext); return CLASS; }
"extends"   { push_kw(TokenKind::EXTENDS, yytext); return EXTENDS; }
"is"        { push_kw(TokenKind::IS, yytext); return IS; }
"end"       { push_kw(TokenKind::END, yytext); return END; }
"var"       { push_kw(TokenKind::VAR, yytext); return VAR; }
"method"    { push_kw(TokenKind::METHOD, yytext); return METHOD; }
"this"      { push_kw(TokenKind::THIS, yytext); return THIS; }
"while"     { push_kw(TokenKind::WHILE, yytext); return WHILE; }
"loop"      { push_kw(TokenKind::LOOP, yytext); return LOOP; }
"if"        { push_kw(TokenKind::IF, yytext); return IF; }
"then"      { push_kw(TokenKind::THEN, yytext); return THEN; }
"else"      { push_kw(TokenKind::ELSE, yytext); return ELSE; }
"return"    { push_kw(TokenKind::RETURN, yytext); return RETURN; }

"true"      { push_kw(TokenKind::TRUE, yytext); return TRUE; }
"false"     { push_kw(TokenKind::FALSE, yytext); return FALSE; }
"new"        { return NEW; }

{INT}       { 
    long long v = atoll(yytext); 
    EmitToken(std::make_unique<IntegerToken>(yytext, v, yylineno, yycolumn)); 
    yylval.ival = v; 
    yycolumn += yyleng; 
    return INTEGER_LITERAL; 
}
{REAL}      { 
    double v = atof(yytext); 
    EmitToken(std::make_unique<RealToken>(yytext, v, yylineno, yycolumn)); 
    yylval.dval = v; 
    yycolumn += yyleng; 
    return REAL_LITERAL; 
}

{ID}        { 
    EmitToken(std::make_unique<IdentifierToken>(yytext, yylineno, yycolumn)); 
    yylval.cstr = strdup(yytext); 
    yycolumn += yyleng; 
    return IDENTIFIER; 
}

":="        { push_sym(TokenKind::ASSIGN, yytext); return ASSIGN; }
"=>"        { push_sym(TokenKind::ARROW, yytext); return ARROW; }
":"         { push_sym(TokenKind::COLON, yytext); return COLON; }
","         { push_sym(TokenKind::COMMA, yytext); return COMMA; }
"."         { push_sym(TokenKind::DOT, yytext); return DOT; }
"("         { push_sym(TokenKind::LPAREN, yytext); return LPAREN; }
")"         { push_sym(TokenKind::RPAREN, yytext); return RPAREN; }
"["         { push_sym(TokenKind::LBRACKET, yytext); return LBRACKET; }
"]"         { push_sym(TokenKind::RBRACKET, yytext); return RBRACKET; }

{WS}        { yycolumn += yyleng; }
\n          { yycolumn = 1; }
"//".*      { yycolumn += yyleng; }

.           { 
    std::fprintf(stderr, "Unknown char '%s' at %d:%d\n", yytext, yylineno, yycolumn); 
    yycolumn += yyleng; 
}

%%