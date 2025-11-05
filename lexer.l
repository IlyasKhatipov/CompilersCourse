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

static int expectClassName = 0;
static int expectMethodName = 0;
static int expectVarName = 0;
static int expectMemberName = 0;

static inline void push_kw(TokenKind k, const char* text) {
    EmitToken(std::make_unique<KeywordToken>(k, text, yylineno, yycolumn));
    yycolumn += yyleng;
}
static inline void push_sym(TokenKind k, const char* text) {
    EmitToken(std::make_unique<SymbolToken>(k, text, yylineno, yycolumn));
    yycolumn += yyleng;
}
static inline int is_upper(const char* s) {
    return std::isupper((unsigned char)s[0]);
}
%}

%option noyywrap
%option nodefault
%option yylineno

ID      [A-Za-z_][A-Za-z0-9_]*
INT     [0-9]+
ESC     \\.
STR     \"([^\\\"]|{ESC})*\"
WS      [ \t\r]+

%%

"class"     { push_kw(TokenKind::CLASS, yytext); expectClassName = 1; return CLASS; }
"var"       { push_kw(TokenKind::VAR,   yytext); expectVarName = 1;  return VAR; }
"is"        { push_kw(TokenKind::IS,    yytext); return IS; }
"end"       { push_kw(TokenKind::END,   yytext); return END; }

"method"    { push_kw(TokenKind::METHOD, yytext); expectMethodName = 1; return METHOD; }
"return"    { push_kw(TokenKind::RETURN, yytext); return RETURN; }
"if"        { push_kw(TokenKind::IF, yytext); return IF; }
"then"      { push_kw(TokenKind::THEN, yytext); return THEN; }
"else"      { push_kw(TokenKind::ELSE, yytext); return ELSE; }
"true"      { push_kw(TokenKind::TRUEKW, yytext); return TRUE; }
"false"     { push_kw(TokenKind::FALSEKW, yytext); return FALSE; }

"Int"       { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }
"String"    { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }
"Bool"      { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }
"Float"     { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }
"Void"      { EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
              yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME; }

{STR}       { std::string s(yytext);
              EmitToken(std::make_unique<StringToken>(yytext, s, yylineno, yycolumn));
              yylval.cstr = strdup(s.c_str()); yycolumn += yyleng; return STRING_LITERAL; }

{ID}        {
              if (expectClassName) { expectClassName = 0;
                  EmitToken(std::make_unique<IdentifierToken>(yytext, yylineno, yycolumn));
                  yylval.cstr = strdup(yytext); yycolumn += yyleng; return IDENTIFIER;
              }
              if (expectMethodName) { expectMethodName = 0;
                  EmitToken(std::make_unique<IdentifierToken>(yytext, yylineno, yycolumn));
                  yylval.cstr = strdup(yytext); yycolumn += yyleng; return IDENTIFIER;
              }
              if (expectVarName) { expectVarName = 0;
                  EmitToken(std::make_unique<IdentifierToken>(yytext, yylineno, yycolumn));
                  yylval.cstr = strdup(yytext); yycolumn += yyleng; return IDENTIFIER;
              }
              if (expectMemberName) { expectMemberName = 0;
                  EmitToken(std::make_unique<IdentifierToken>(yytext, yylineno, yycolumn));
                  yylval.cstr = strdup(yytext); yycolumn += yyleng; return IDENTIFIER;
              }
              if (is_upper(yytext)) {
                  EmitToken(std::make_unique<TypeNameToken>(yytext, yylineno, yycolumn));
                  yylval.cstr = strdup(yytext); yycolumn += yyleng; return TYPE_NAME;
              } else {
                  EmitToken(std::make_unique<IdentifierToken>(yytext, yylineno, yycolumn));
                  yylval.cstr = strdup(yytext); yycolumn += yyleng; return IDENTIFIER;
              }
            }

":="        { push_sym(TokenKind::ASSIGN, yytext); return ASSIGN; }
"=>"        { push_sym(TokenKind::ARROW, yytext); return ARROW; }
":"         { push_sym(TokenKind::COLON, yytext); return COLON; }
";"         { push_sym(TokenKind::SEMICOLON, yytext); return SEMICOLON; }
","         { push_sym(TokenKind::COMMA, yytext); return COMMA; }
"("         { push_sym(TokenKind::LPAREN, yytext); return LPAREN; }
")"         { push_sym(TokenKind::RPAREN, yytext); return RPAREN; }
"{"         { push_sym(TokenKind::LBRACE, yytext); return LBRACE; }
"}"         { push_sym(TokenKind::RBRACE, yytext); return RBRACE; }
"="         { push_sym(TokenKind::EQUAL, yytext); return EQUAL; }
"+"         { push_sym(TokenKind::PLUS, yytext); return PLUS; }
"-"         { push_sym(TokenKind::MINUS, yytext); return MINUS; }
"*"         { push_sym(TokenKind::STAR, yytext); return STAR; }
"/"         { push_sym(TokenKind::SLASH, yytext); return SLASH; }
"."         { push_sym(TokenKind::DOT, yytext); expectMemberName = 1; return DOT; }
">"         { push_sym(TokenKind::GT, yytext); return GT; }

"//".*      { yycolumn += yyleng; }
{WS}        { yycolumn += yyleng; }
\n          { yycolumn = 1; }

.           { std::fprintf(stderr, "Unknown char '%s' at %d:%d\n", yytext, yylineno, yycolumn);
              yycolumn += yyleng; }

%%
