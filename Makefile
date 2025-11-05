CXX=g++
CXXFLAGS=-std=c++17 -O2
LEX=flex
YACC=bison

all: mycompiler

parser.cpp parser.tab.h: parser.y
	$(YACC) -d parser.y -o parser.cpp

lexer.cpp: lexer.l parser.tab.h
	$(LEX) -o lexer.cpp lexer.l

mycompiler: parser.cpp lexer.cpp main.cpp tokens.hpp ast.hpp
	$(CXX) $(CXXFLAGS) -o mycompiler parser.cpp lexer.cpp main.cpp -lfl

run:
	./mycompiler tests/test1.o

clean:
	rm -f mycompiler parser.cpp parser.tab.h lexer.cpp
