#include "parser.h"

struct Token* currentToken(){
    return &tokens[cur_tok];   
}
struct Token* nextToken(){
    cur_tok++;
    return &tokens[cur_tok];
}

struct Node* createNodeReturn(struct Node* returnVal){
        struct Token* token=currentToken();
        struct Node* node=malloc(sizeof(struct Node));
       
        node->type=return_node;
        node->data.returnDecl.returnValue=returnVal->data.intValue;
        node->nextNode=NULL;
        return node;
    };
struct Node* createNodeInt(int val){
        struct Token* token=currentToken();
        struct Node* node=malloc(sizeof(struct Node));
        node->type=int_node;
        node->data.intValue=val;
        node->nextNode=NULL;
        return node;
    };
struct Node* createNodeVariable(char* var_name, struct Node* varVal){
        struct Token* token=currentToken();
        struct Node* node=malloc(sizeof(struct Node));
        node->type=var_node;
        printf("%s token_name",var_name);
        strcpy(node->data.varDecl.varName,var_name);
        
        node->data.varDecl.varValue=varVal->data.intValue;
        node->nextNode=NULL;
        return node;
    }
struct Node* numberStatement(){
        struct Token* token=currentToken();
        if (token->type==number){
            return createNodeInt(atoi(token->name));
        }
    };
struct Node* variableStatement(){
        struct Token* token=nextToken();
        char name[32]="";
        strcpy(name,token->name);
        if (token->type!=_str){
            exit(EXIT_FAILURE);
        }
        printf("%s token_name",name);
        token=nextToken();
        if (token->type==equ){
            token=nextToken();
            struct Node* value=numberStatement();
            return createNodeVariable(name, value);
        }
        
    };

struct Node* returnStatement(){
        struct Token* token=nextToken();
        struct Node* value = numberStatement();
        return createNodeReturn(value);
    };

struct Node* parseKeywords(){
        struct Token* token=currentToken();
       
        if (strcmp(token->name,"return")==0){
            return returnStatement();
        }
        if (strcmp(token->name,"int")==0){
            return variableStatement();
        }
        else
        {
            struct Token* token=currentToken();
            struct Node* node=malloc(sizeof(struct Node));
            node->type=int_node;
            node->data.intValue=10;
            node->nextNode=NULL;
            return node;
        }

    };


struct Node* parser(struct Token *tokens){
    printf("totalnie peirwszy token: %d",cur_tok);
    struct Token* token=currentToken();

    struct Node* program=NULL;
    struct Node* current=NULL;
    node_count=0;
    while (token->type!=0){
        
        struct Node* kw=parseKeywords();
        printf("%d- to kw\n");
        if (kw){
            node_count++;
            if (program==NULL){
                program=kw;
                current=kw;
            }
            else{
                if (current!=NULL){
                current->nextNode=kw;
                current=kw;}
            }
        }
        token=nextToken();

    }
    printf("+%d",node_count);
    return program;
}



void print_all(struct Node* node){
    
    switch(node->type){
        case return_node:
            printf("\nRETURN |%d|",node->data.returnDecl.returnValue);
        case var_node:
            printf("\nVAR |%s|%d|ttt",node->data.varDecl.varName,node->data.varDecl.varValue);
    }
    if (node->nextNode!=NULL){
    print_all(node->nextNode);}

}