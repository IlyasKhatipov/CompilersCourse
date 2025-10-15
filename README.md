To compile parser.
```bash
rm -f parser.tab.* lex.yy.* compiler
bison -d -o parser.tab.cc parser.y
flex -+ lexer.l
g++ -std=c++17 -o compiler lex.yy.cc parser.tab.cc -lfl
```

To run test
```bash
./compiler < tests/test1.o
```