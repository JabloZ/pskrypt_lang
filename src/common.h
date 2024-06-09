// common.h

#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h> // Dla size_t

struct Token* tokens;
int cur_tok;
int node_count;
struct Var_adr{
    char *name[32];
    int asm_address;
};

typedef enum{
    null,
    _return,
    int_lit,
    semicolon,
    equ,
    add, 
    sub,
    number,
    _str

} tokenType;

struct Token{
    tokenType type;
    char name[32];
    char text[32];
}; 

typedef enum{
    null_node,
    return_node,
    int_node,
    var_node,
    binary_op_node
} nodeType;

typedef struct Node{
    nodeType type;
    union{
        
        int intValue;
        struct {
            char* varName[32]; //if segfault try hardcoding size
            struct Node* varValue;
        } varDecl;
        struct {
            struct Node* returnValue;
        } returnDecl;
    } data;
    struct Node* nextNode;
}Node;

#endif;