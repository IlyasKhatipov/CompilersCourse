#include <cstdio>
#include <iostream>
#include "ast.hpp"
#include "tokens.hpp"

extern int  yyparse(void);
extern FILE* yyin;
extern AST::Program* g_program;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source .o>\n";
        return 1;
    }
    yyin = std::fopen(argv[1], "r");
    if (!yyin) {
        std::perror("fopen");
        return 1;
    }
    std::cout << "=== LEXER TOKENS ===\n";
    int rc = yyparse();
    std::fclose(yyin);
    if (rc == 0) {
        std::cout << "\n=== AST ===\n";
        if (g_program) {
            g_program->print(std::cout);
            delete g_program;
            g_program = nullptr;
        }
        return 0;
    } else {
        std::cerr << "Parse failed.\n";
        return 2;
    }
}
