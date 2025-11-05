// main.cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "ast.hpp"

extern int yyparse(void);
extern FILE* yyin;
extern AST::Program* g_program;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./mycompiler <input .o>\n";
        return 1;
    }
    const char* path = argv[1];
    yyin = fopen(path, "r");
    if (!yyin) {
        std::perror("fopen");
        return 1;
    }

    // Парсим; лексер уже печатает поток токенов:
    // например:
    // CLASS
    // IDENTIFIER(Point)
    // IS
    // VAR
    // IDENTIFIER(x)
    // COLON
    // TYPE(Int)
    // ...
    if (yyparse() == 0) {
        // Печать нормализованного AST (раскладывание)
        if (g_program) {
            std::cout << "\n--- AST ---\n";
            g_program->printNormalized(std::cout);
        }
    } else {
        std::cerr << "Parsing failed.\n";
    }

    fclose(yyin);
    return 0;
}
