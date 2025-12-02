CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

all: mycompiler

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

lexer.cpp: lexer.l parser.hpp
	flex -o lexer.cpp lexer.l

mycompiler: parser.cpp lexer.cpp main.cpp semantic.cpp ast.hpp tokens.hpp
	$(CXX) $(CXXFLAGS) -o $@ parser.cpp lexer.cpp main.cpp semantic.cpp -lfl

clean:
	rm -f parser.cpp parser.hpp lexer.cpp mycompiler

test: mycompiler
	./mycompiler tests/test1.o
	./mycompiler tests/test2.o
	./mycompiler tests/test3.o
	./mycompiler tests/test4.o
	./mycompiler tests/test5.o

.PHONY: all clean test