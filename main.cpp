#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include "ast.hpp"
#include "tokens.hpp"
#include "semantic.hpp"
#include "wasm_codegen.hpp"

extern int yyparse(void);
extern FILE* yyin;
extern AST::Program* g_program;

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <source.o> <out.wat>\n";
        return 1;
    }

    const char* srcPath = argv[1];
    const char* outPath = argv[2];

    FILE* src = std::fopen(srcPath, "r");
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

    yyin = std::fopen(srcPath, "r");
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

    std::ofstream out(outPath);
    if (!out) {
        std::cerr << "Cannot open output file: " << outPath << "\n";
        delete g_program;
        g_program = nullptr;
        return 4;
    }

    std::cout << "\n=== WASM CODEGEN ===\n";
    WasmGenerator gen(g_program, res);
    gen.generateToWat(out, "Main");
    out.close();

    std::cout << "Generated WAT file: " << outPath << "\n";

    delete g_program;
    g_program = nullptr;
    return 0;
}
