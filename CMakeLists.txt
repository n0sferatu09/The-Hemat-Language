cmake_minimum_required(VERSION 3.20)
project(hmc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(hmc
        src/main.c
        src/lexer/lexer.h
        src/hashtable/hashtable.c
        src/hashtable/hashtable.h
        src/lexer/lexer.c
        src/lexer/lexemes/lexemes.c
        src/lexer/lexemes/lexemes.h
        src/lexer/tokens/tokens.h
        src/vector/vector.c
        src/vector/vector.h
        src/lexer/tokens/tokens.c
        src/parser/parser.c
        src/parser/parser.h
        src/ast/ast.c
        src/ast/ast.h
        src/semantic/semantic.c
        src/semantic/semantic.h
        src/symbol_table/symbol_table.c
        src/symbol_table/symbol_table.h
        src/codegen/codegen.c
        src/codegen/codegen.h
)

target_compile_options(hmc PRIVATE -Wall -Wextra -g)