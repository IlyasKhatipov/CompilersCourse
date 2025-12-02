CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

all: mycompiler

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

lexer.cpp: lexer.l parser.hpp
	flex -o lexer.cpp lexer.l

mycompiler: parser.cpp lexer.cpp main.cpp semantic.cpp wasm_codegen.cpp ast.hpp tokens.hpp
	$(CXX) $(CXXFLAGS) -o $@ parser.cpp lexer.cpp main.cpp semantic.cpp wasm_codegen.cpp -lfl

%.wat: %.o mycompiler
	./mycompiler $< $@

%.wasm: %.wat
	wat2wasm $< -o $@

clean:
	rm -f parser.cpp parser.hpp lexer.cpp mycompiler *.wat *.wasm
