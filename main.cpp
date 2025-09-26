#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstdio>

extern "C" {
    extern int yylex();       // сама функция лексера
    extern FILE* yyin;        // входной поток для лексера
    extern char* yytext;      // текущий текст токена
}


const std::string TEST_DIR = "tests";

int main() {
    namespace fs = std::filesystem;

    // Перебор файлов в tests/
    for (const auto& entry : fs::directory_iterator(TEST_DIR)) {
        if (entry.is_regular_file() && entry.path().extension() == ".o") {
            std::string filename = entry.path().string();
            std::cout << "=== Running lexer on " << filename << " ===\n";

            FILE* file = fopen(filename.c_str(), "r");
            if (!file) {
                std::cerr << "Failed to open file: " << filename << "\n";
                continue;
            }

            yyin = file;

            int token;
            while ((token = yylex()) != 0) {
                std::cout << "Token: " << token << "  (" << yytext << ")\n";
            }

            fclose(file);
            std::cout << "\n";
        }
    }

    return 0;
}
