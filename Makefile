CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

all: mycompiler

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

lexer.cpp: lexer.l parser.hpp
	flex -o lexer.cpp lexer.l

mycompiler: parser.cpp lexer.cpp main.cpp semantic.cpp interpreter.cpp
	$(CXX) $(CXXFLAGS) -o $@ parser.cpp lexer.cpp main.cpp semantic.cpp interpreter.cpp -lfl

clean:
	rm -f parser.cpp parser.hpp lexer.cpp mycompiler

wasm: parser.cpp lexer.cpp main.cpp semantic.cpp interpreter.cpp
	em++ -std=c++17 \
		parser.cpp lexer.cpp main.cpp semantic.cpp interpreter.cpp \
		-s WASM=1 \
		-s ALLOW_MEMORY_GROWTH=1 \
		-s EXPORTED_FUNCTIONS='["_main"]' \
		-s EXPORTED_RUNTIME_METHODS='["callMain"]' \
		--preload-file tests \
		-o mycompiler.html

