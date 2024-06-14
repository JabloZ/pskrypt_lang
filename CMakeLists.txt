cmake_minimum_required(VERSION 3.16)
project(pskrypt C)
set(SOURCES
    src/main.c
    src/tokenizer.c
    src/asm_generate.c
    src/parser.c
)

set(HEADERS
    src/tokenizer.h
    src/asm_generate.h
    src/parser.h
)
add_executable(${PROJECT_NAME} ${SOURCES})