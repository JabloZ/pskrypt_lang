// common.h

#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h> // Dla size_t

struct Node* program;
struct Token* tokens;
int recent_loop;
int cur_tok;
int iter_loop_num;
int loop_name;
int node_count;
char variables[1000];
char variables_d[100][32]; // i should malloc that nstead of taking so much memory
char var_decl[1000];
char changed_var[32];
bool can_change;
struct Var_adr{
    char *name[32];
    int asm_address;
};
int loopstack[20]; //could do something like linked list but its fine for now, no premature optimazation 

typedef enum{
    null,
    _return,
    int_lit,
    semicolon,
    equ,
    add, 
    sub,
    mult,
    _div,
    number,
    _str,
    keyword_tok

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
    binary_op_node,
    semi_node,
    while_node,
    end_loop_node
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
        struct {
            struct Node* left;
            struct Node* right;
            char* op[32]; //mozliwy segfault
        } binaryOp;
        struct{
            int loopNum;
            struct Node* first;
            struct Node* second;
            char* instruction[32];
        } whileDecl;
        struct{
            int loopNum;
        } endLoopDecl;
    } data;
    struct Node* nextNode;
}Node;

#endif