cmake_minimum_required(VERSION 3.16)
project(myprogram C)
set(SOURCES
    src/main.c
    src/tokenizer.c
    src/asm_generate.c
    src/parser.c
)

# Dodanie plików nagłówkowych (opcjonalne, tylko dla przejrzystości)
set(HEADERS
    tokenizer.h
    asm_generate.h
    parser.h
)
add_executable(${PROJECT_NAME} ${SOURCES})