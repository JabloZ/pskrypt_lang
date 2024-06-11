#include "parser.h"

struct Token* currentToken(){
    return &tokens[cur_tok];   
};
struct Token* nextToken(){
    cur_tok++;
    return &tokens[cur_tok];
};

struct Node* createNodeReturn(struct Node* returnVal){
        struct Token* token=currentToken();
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        memset(node, 0, sizeof(struct Node));
        node->type=return_node;
        node->data.returnDecl.returnValue=returnVal->data.intValue;
        node->nextNode=NULL;
        return node;
    };
struct Node* createNodeInt(int val){
    
        struct Token* token=currentToken();
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        
        memset(node, 0, sizeof(struct Node));
        node->type=int_node;
        node->data.intValue=val;

        node->nextNode=NULL;
        return node;
    };
struct Node* createNodeVariable(char* var_name, struct Node* varVal){
        struct Token* token=currentToken();
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        memset(node, 0, sizeof(struct Node));
        node->type=var_node;
        strcpy(node->data.varDecl.varName,var_name);
        
        node->data.varDecl.varValue=varVal->data.intValue;
        node->nextNode=NULL;
        return node;
    }
struct Node* createNodeBinOp(char* op,struct Node* left_n,struct Node* right_n){
    struct Token* token=currentToken();
    
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
     memset(node, 0, sizeof(struct Node));
    node->type=binary_op_node;
    node->data.binaryOp.left=left_n;
    node->data.binaryOp.right=right_n;
    strcpy(node->data.binaryOp.op,op);
    node->nextNode=NULL;
    
    return node;
       
}


int* variable_exists(char* token_name){
    //int* arr=malloc(sizeof(int)*2);
    int* arr=malloc(8);
    arr[0]=-1;
    arr[1]=-1;
    struct Node* node_checked=program;
    while(node_checked!=NULL){
        if (strcmp(node_checked->data.varDecl.varName,token_name)==0){
            arr[0]=1;
            arr[1]=node_checked->data.varDecl.varValue;
            return arr;
        }
        node_checked=node_checked->nextNode;

    }
    
    return arr;
}

struct Node* numberStatement(){
        struct Token* token=currentToken();
        
        if (token->type==number){
            return createNodeInt(atoi(token->name));
        }
        if (token->type==_str){
            int* res;
            res=variable_exists(token->name);

            if (res[0]!=-1){
                return createNodeInt(res[1]);
            }
        }
        exit(EXIT_FAILURE);    
    };
struct Node* variableStatement(){
        struct Token* token=nextToken();
        char name[32]="";
        strcpy(name,token->name);
        if (token->type!=_str){
            exit(EXIT_FAILURE);
        }
        token=nextToken();
        if (token->type==equ){
            token=nextToken();
            struct Node* value=numberStatement();
            return createNodeVariable(name, value);
        }
        
    };

struct Node* binaryOperation(){
        struct Token* token=currentToken();
        char op[32]="";
        
        struct Node* left=numberStatement();
        if (left->type==int_node){
            token=nextToken();
           
            if (token->type==add){
                strcpy(op,token->name);
             
                token=nextToken();
                struct Node* right=numberStatement();
                if (right->type==int_node){
                    return createNodeBinOp(op,left,right);
                }
                
            }

        }
            struct Node* node=malloc(sizeof(struct Node));
            node->type=null_node;
            node->nextNode=NULL;
            return node;
        
        
}

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
        if (strcmp(token->name,"+")==0){
            cur_tok--;
            return binaryOperation();
        }
        
        {
            struct Token* token=currentToken();
            struct Node* node=malloc(sizeof(struct Node));
            node->type=null_node;
            node->nextNode=NULL;
            return node;
        }

    };

void resetNode(struct Node* node) {
    if (node != NULL) {
        
        memset(&node->data, 0, sizeof(node->data));
        printf("RESET: %d",node->type);
    }
}
 
struct Node* parser(struct Token *tokens){
   
    struct Token* token=currentToken();

    struct Node* current=NULL;
    node_count=0;
    while (token->type!=0){
        
        struct Node* kw=parseKeywords();
        
        if (kw){
            node_count++;
            if (program==NULL){
                program=kw;
                current=kw;
            }
            else{
                current->nextNode=kw;
                current=kw;
             
            }
        }
           //resetNode(current);
        token=nextToken();

    }
    printf("node_count: %d",node_count);
    return program;
}



void print_all(struct Node* node){
    printf("\n NODE_TYPE: %d",node->type);
    switch(node->type){
        
        case return_node:
            printf("\nRETURN |%d|",node->data.returnDecl.returnValue);
            break;
        case var_node:
            printf("\nVAR |%s|%d|ttt",node->data.varDecl.varName,node->data.varDecl.varValue);
            break;
        case binary_op_node:
            
            //printf("\nl: %d r: %d op:%s ",node->data.binaryOp.left->data.intValue, node->data.binaryOp.right->data.intValue, node->data.binaryOp.op);
            printf("\nW PRINTALL: l: %d r: %d op: %s",node->data.binaryOp.left->data.intValue, node->data.binaryOp.right->data.intValue, node->data.binaryOp.op);
            break;
        case int_node:
            printf("\n int");
            break;
    }
    if (node->nextNode!=NULL){
    print_all(node->nextNode);}

}