To compile parser.
```bash
bison -d parser.y
flex lexer.l
g++ -std=c++17 -o compiler lex.yy.cc parser.tab.cc -lfl
```

To run test
```bash
./compiler tests/test1.o
```