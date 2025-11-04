#include <cstdio>
#include <iostream>
extern FILE* yyin;
extern int yyparse();
extern void printAST();

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>\n";
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        std::cerr << "Failed to open input file\n";
        return 1;
    }
    int res = yyparse();
    if (res == 0) {
        printAST();
    } else {
        std::cerr << "Parsing failed\n";
    }
    fclose(yyin);
    return res;
}
