%option noyywrap
%option outfile="lexer.cpp"
%option c++
%{
#include "tokens.hpp"
#include "parser.tab.h"  // bison сгенерит
#include <cstdlib>

using namespace std;

static int cur_line = 1;
static int cur_col  = 1;

#define YY_USER_ACTION \
    /* обновим столбцы: */ \
    cur_col += yyleng;

static int start_col_for_rule() {
    return cur_col - yyleng + 1;
}

// Утилита: создать токен и вывести его
template <typename T, typename... Args>
static T* make_token_and_echo(Args&&... args) {
    T* t = new T(std::forward<Args>(args)...);
    printToken(t);
    return t;
}
%}

ws          [ \t\r]+
newline     \n
id          [A-Za-z_][A-Za-z0-9_]*
intlit      [0-9]+

%%

{ws}         {/* пропуск, столбец уже учтён */}
{newline}    { cur_line++; cur_col = 1; }

"class"      { auto t = make_token_and_echo<KeywordToken>(TokenKind::Class, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_CLASS; }
"is"         { auto t = make_token_and_echo<KeywordToken>(TokenKind::Is, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_IS; }
"var"        { auto t = make_token_and_echo<KeywordToken>(TokenKind::Var, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_VAR; }
"end"        { auto t = make_token_and_echo<KeywordToken>(TokenKind::End, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_END; }

"Int"        { auto t = make_token_and_echo<TypeToken>("Int", cur_line, start_col_for_rule()); yylval.tok = t; return T_INT_TYPE; }

":"          { auto t = make_token_and_echo<SymbolToken>(TokenKind::Colon, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_COLON; }
";"          { auto t = make_token_and_echo<SymbolToken>(TokenKind::Semicolon, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_SEMI; }
"="          { auto t = make_token_and_echo<SymbolToken>(TokenKind::Assign, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_ASSIGN; }
"("          { auto t = make_token_and_echo<SymbolToken>(TokenKind::LParen, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_LPAREN; }
")"          { auto t = make_token_and_echo<SymbolToken>(TokenKind::RParen, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_RPAREN; }
"\\+"        { auto t = make_token_and_echo<SymbolToken>(TokenKind::Plus, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_PLUS; }
"-"          { auto t = make_token_and_echo<SymbolToken>(TokenKind::Minus, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_MINUS; }
"\\*"        { auto t = make_token_and_echo<SymbolToken>(TokenKind::Star, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_STAR; }
"/"          { auto t = make_token_and_echo<SymbolToken>(TokenKind::Slash, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_SLASH; }
"\\."        { auto t = make_token_and_echo<SymbolToken>(TokenKind::Dot, yytext, cur_line, start_col_for_rule()); yylval.tok = t; return T_DOT; }

{intlit}     {
                long long v = atoll(yytext);
                auto t = make_token_and_echo<IntegerToken>(v, yytext, cur_line, start_col_for_rule());
                yylval.tok = t; return T_INTEGER;
             }

{id}         {
                std::string s(yytext);
                // Если не ключевое слово/тип — идентификатор
                auto t = make_token_and_echo<IdentifierToken>(s, cur_line, start_col_for_rule());
                yylval.tok = t; return T_IDENTIFIER;
             }

"//".*       { /* комментарии до конца строки */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* блочный комментарий */ }

.            {
                fprintf(stderr, "Unknown char '%s' at %d:%d\n", yytext, cur_line, start_col_for_rule());
             }

%%
// yywrap по умолчанию отключён опцией
