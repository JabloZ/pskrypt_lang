#include "parser.h"

struct Token* currentToken(){
    return &tokens[cur_tok];   
};
struct Token* nextToken(){
    cur_tok++;
    return &tokens[cur_tok];
};
struct Node* createNodeEndLoop(){
        struct Token* token=currentToken();
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        //memset(node, 0, sizeof(struct Node));
        node->type=end_loop_node;
        recent_loop--;
        node->data.endLoopDecl.loopNum=recent_loop;
        
        node->nextNode=NULL;
        return node;
}
struct Node* createNodeEndIf(){
        struct Token* token=currentToken();
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        //memset(node, 0, sizeof(struct Node));
        node->type=end_if_node;
        recent_if--;
        node->data.endIfDecl.ifNum=recent_if;
        
        node->nextNode=NULL;
        return node;
}
struct Node* createNodeReturn(struct Node* returnVal){
        struct Token* token=currentToken();
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        //memset(node, 0, sizeof(struct Node));
        node->type=return_node;
        
        node->data.returnDecl.returnValue=returnVal;
        
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
struct Node* createWhileLoop(struct Node* first_n, struct Node* second_n, char* name_ins){
   
    struct Token* token=currentToken();
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    memset(node, 0, sizeof(struct Node));
    node->data.whileDecl.loopNum=recent_loop;
    node->type=while_node;
    node->data.whileDecl.first=first_n;
    node->data.whileDecl.second=second_n;
    recent_loop++;
    strcpy(node->data.whileDecl.instruction,name_ins);
    node->nextNode=NULL;
    
    return node;
}
struct Node* createNodeIf(struct Node* first_n, struct Node* second_n, char* name_ins){
    
    struct Token* token=currentToken();
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    memset(node, 0, sizeof(struct Node));
    node->data.ifDecl.ifNum=recent_if;
    node->type=if_node;
    node->data.ifDecl.first=first_n;
    node->data.ifDecl.second=second_n;
    recent_if++;
    strcpy(node->data.ifDecl.instruction,name_ins);
    node->nextNode=NULL;
    return node;
}

struct Node* variable_exists(char* token_name){ // to replace with map

    int* returned_node=malloc(sizeof(int*));
    struct Node* node_checked=program;
    while(node_checked!=NULL){
        if (strcmp(node_checked->data.varDecl.varName,token_name)==0){
            
            return node_checked;
        }
        node_checked=node_checked->nextNode;

    }
    
    return returned_node;
}

struct Node* numberStatement(){
        struct Token* token=currentToken();
        
        if (token->type==number){
            return createNodeInt(atoi(token->name));
        }
        if (token->type==_str){

            struct Node* res;
            res=variable_exists(token->name); //tu segfault narazie
        
            if (res!=NULL){
                return res;
            }
        }
        exit(EXIT_FAILURE);    
    };
struct Node* variableStatement(){
        struct Token* token=nextToken();
        char name[32]="";
        strcpy(name,token->name);
        struct Node* node_int=createNodeInt(0);
        return createNodeVariable(name, node_int);
        
    };

struct Node* binaryOperation(){
        struct Token* token=currentToken();
        char op[32]="";
        struct Node* left=numberStatement();
        if (left->type==int_node || left->type==var_node){
            token=nextToken();  
            if (token->type==add || token->type==equ || token->type==sub || token->type==mult || token->type==_div){
                strcpy(op,token->name);
                token=nextToken();
               
                struct Node* right=numberStatement();
                
                if (right->type==int_node || right->type==var_node){
                    
                    return createNodeBinOp(op,left,right);
                }
                
            }

        }
            struct Node* node=malloc(sizeof(struct Node));
            node->type=null_node;
            node->nextNode=NULL;
            return node;
}
struct Node* whileLoopStatement(){
    printf("\nwtf?");
    struct Token* token=nextToken();
    struct Node* num_or_var=numberStatement();

        if (num_or_var->type==int_node || num_or_var->type==var_node){
             printf("\nwtf?");
            token=nextToken();
            if (strcmp(token->name,"greater")==0 || strcmp(token->name,"greater_equal")==0 || strcmp(token->name,"lesser")==0 || strcmp(token->name,"lesser_equal")==0 || strcmp(token->name,"equal")==0 || strcmp(token->name,"not_equal")==0){
                char ins_name[32];
                strcpy(ins_name,token->name);
                token=nextToken();
                struct Node* num_or_var_second=numberStatement();
                if (num_or_var->type==int_node || num_or_var->type==var_node){
                    return createWhileLoop(num_or_var, num_or_var_second, ins_name);
                }

            }
        }
    
}
struct Node* ifStatement(){
    struct Token* token=nextToken();
    struct Node* num_or_var=numberStatement();
    
        if (num_or_var->type==int_node || num_or_var->type==var_node){
            token=nextToken();
            if (strcmp(token->name,"greater")==0 || strcmp(token->name,"greater_equal")==0 || strcmp(token->name,"lesser")==0 || strcmp(token->name,"lesser_equal")==0 || strcmp(token->name,"equal")==0 || strcmp(token->name,"not_equal")==0){
                char ins_name[32];
                strcpy(ins_name,token->name);
                token=nextToken();
                struct Node* num_or_var_second=numberStatement();
                if (num_or_var->type==int_node || num_or_var->type==var_node){
                    return createNodeIf(num_or_var, num_or_var_second, ins_name);
                }

            }
        }
    
}
struct Node* node_semi(){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->type=semi_node;
    node->nextNode=NULL;
    node->data.intValue==0;
    return node;
}
struct Node* returnStatement(){
        struct Token* token=nextToken();
        struct Node* value = numberStatement();
        return createNodeReturn(value);
    };

struct Node* parseKeywords(){
        struct Token* token=currentToken();
        if (strcmp(token->name,"if")==0){
            return ifStatement();
        }
        if (strcmp(token->name,"end_if")==0){
            return createNodeEndIf();
        }
        if (strcmp(token->name,"end_loop")==0){
            return createNodeEndLoop();
        }
        if (strcmp(token->name,"while")==0){
            return whileLoopStatement();
        }
        if (strcmp(token->name,";")==0){
            return node_semi();
        }
        if (strcmp(token->name,"return")==0){
            return returnStatement();
        }
        if (strcmp(token->name,"var")==0){
            return variableStatement();
        }
        if (token->type==number){
            return createNodeInt(atoi(token->name));}
        if (strcmp(token->name,"+")==0 || strcmp(token->name,"=")==0 || strcmp(token->name,"-")==0  ||  strcmp(token->name,"*")==0 ||  strcmp(token->name,"/")==0){
            cur_tok--;
            return binaryOperation();
        }
        
        {
            struct Node* node=malloc(sizeof(struct Node));
            node->type=null_node;
            node->nextNode=NULL;
            return node;
        }

    };

void resetNode(struct Node* node) {
    if (node != NULL) {
        
        memset(&node->data, 0, sizeof(node->data));
        
    }
}
 
struct Node* parser(struct Token *tokens){
   
    struct Token* token=currentToken();
    recent_loop=0;
    recent_if=0;
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


/*
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
            printf("\n int: %d",node->data.intValue);
            break;
    }
    if (node->nextNode!=NULL){
    print_all(node->nextNode);}

}*/