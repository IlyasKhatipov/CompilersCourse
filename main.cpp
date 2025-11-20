#include <cstdio>
#include <iostream>
#include "ast.hpp"
#include "tokens.hpp"
#include "semantic.hpp"
#include "interpreter.hpp"

extern int yyparse(void);
extern FILE* yyin;
extern AST::Program* g_program;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source .o>\n";
        return 1;
    }

    FILE* src = std::fopen(argv[1], "r");
    if (!src) {
        std::perror("fopen");
        return 1;
    }

    std::cout << "=== SOURCE ===\n";
    int ch;
    while ((ch = std::fgetc(src)) != EOF) {
        std::cout << static_cast<char>(ch);
    }
    std::cout << "\n";
    std::fclose(src);

    yyin = std::fopen(argv[1], "r");
    if (!yyin) {
        std::perror("fopen");
        return 1;
    }

    std::cout << "=== LEXER TOKENS ===\n";
    int rc = yyparse();
    std::fclose(yyin);

    if (rc != 0) {
        std::cerr << "Parse failed.\n";
        return 2;
    }

    if (!g_program) {
        std::cerr << "No AST generated.\n";
        return 2;
    }

    std::cout << "\n=== ORIGINAL AST ===\n";
    g_program->print(std::cout);

    std::cout << "\n=== SEMANTIC ANALYSIS ===\n";
    SemanticAnalyzer analyzer;
    SemanticResult res = analyzer.analyze(g_program);

    if (!res.ok) {
        std::cerr << "Semantic errors found:\n";
        for (const auto& e : res.errors) {
            std::cerr << "  - " << e << "\n";
        }
        delete g_program;
        g_program = nullptr;
        return 3;
    }

    std::cout << "Semantic analysis completed successfully.\n";

    if (!res.warnings.empty()) {
        std::cout << "Warnings:\n";
        for (const auto& w : res.warnings) {
            std::cout << "  - " << w << "\n";
        }
    }

    if (!res.optimizations.empty()) {
        std::cout << "Optimizations applied:\n";
        for (const auto& o : res.optimizations) {
            std::cout << "  * " << o << "\n";
        }
    }

    std::cout << "\n=== Final AST (After Semantic Analysis) ===\n";
    g_program->print(std::cout);

    std::cout << "\n=== INTERPRETATION ===\n";
    Interpreter interp(g_program);
    interp.run();

    delete g_program;
    g_program = nullptr;
    return 0;
}
