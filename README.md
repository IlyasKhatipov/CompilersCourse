# Simple Object-Oriented Language Compiler & Interpreter

## Project Overview

This is a compiler and interpreter for a simple object-oriented programming language, developed as part of the Compilers course at Innopolis University during the Fall 2025 semester. The project implements a complete pipeline from source code to execution, 
including lexical analysis, parsing, semantic analysis, and interpretation.

## Language Features

### Basic Syntax
- **Classes** with fields and methods
- **Primitive types**: `Int`, `Bool`, `String`, `Float`, `Void`
- **Variables** with type annotations
- **Control structures**: `if-elseif-else`, `while` loops
- **Expressions**: arithmetic, relational, logical operations
- **Method calls** and **member access**
- **Return statements** with optional values

## Project Structure

### Core Components

| File | Purpose |
|------|---------|
| `lexer.l` | Flex lexer specification (tokenization) |
| `parser.y` | Bison parser specification (grammar rules) |
| `tokens.hpp` | Token definitions and token stream management |
| `ast.hpp` | Abstract Syntax Tree node definitions |
| `semantic.hpp/.cpp` | Semantic analysis with type checking and optimizations |
| `interpreter.hpp/.cpp` | AST interpreter for execution |
| `main.cpp` | Driver program coordinating all phases |

### Build System
- **Makefile**: Handles compilation of lexer, parser, and all C++ sources

## Building and Running

### Prerequisites
```bash
sudo apt-get install flex bison g++
```

### Compilation
```bash
make clean
make
```

### Execution
```bash
./mycompiler <source_file.o>
```

## Compiler Pipeline

### 1. Lexical Analysis
- Converts source code to tokens
- Recognizes keywords, identifiers, literals, and symbols
- Tracks line and column numbers for error reporting

### 2. Syntax Analysis
- Uses Bison
- Builds Abstract Syntax Tree (AST)
- Validates program structure against grammar

### 3. Semantic Analysis
- Type checking and validation
- Constant folding optimization
- Unreachable code detection
- Variable usage analysis

### 4. Interpretation
- Executes the validated AST
- Supports method calls, loops, and conditionals
- Built-in `output` function for printing

## Key Optimizations

The compiler implements several optimizations:

1. **Constant Folding**: Evaluates constant expressions at compile time
2. **Dead Code Elimination**: Removes unreachable code after returns
3. **Condition Simplification**: Optimizes if-statements with constant conditions
4. **Unused Variable Detection**: Warns about variables declared but never used

## Error Reporting

The compiler provides comprehensive error messages:

- **Lexical errors**: Invalid characters or tokens
- **Syntax errors**: Grammar violations
- **Semantic errors**: Type mismatches, undefined variables
- **Warnings**: Unused variables, potential optimizations

## Academic Context

**Course**: Compilers (Fall 2025)  
**Institution**: Innopolis University   

### Learning Outcomes
- Understanding of compiler architecture and phases
- Experience with parser generators (Flex/Bison)
- Implementation of semantic analysis and type systems
- Design of intermediate representations (AST)
- Building execution engines (interpreters)


