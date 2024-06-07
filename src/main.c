#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
extern int errno;
struct Token * tokens;
int cur_tok=0;
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

struct Var_adr{
    char *name[32];
    int asm_address;
};


void generate_assembly(struct Token *tokens,int size_tok){
    struct Var_adr *adrs=malloc(sizeof(struct Var_adr)*size_tok);
    int adr_i=0;
    FILE *fptr;
    for (int j=0; j<size_tok; j++){
        printf("%d",j);
    }
    int m_stack_size=0;
    fptr=fopen("output.asm","w");
    fprintf(fptr,"global _main\n");
    fprintf(fptr,"_main:\n");
    fprintf(fptr,"\tpush rbp\n");
    fprintf(fptr,"\tmov rbp, rsp\n");
    printf("%d",size_tok);
    for (int i=0; i<=size_tok; i++){
        if (tokens[i].type==_return){
            fprintf(fptr,"\tmov rax, 60\n");
            fprintf(fptr,"\tmov rdi, %d\n",atoi(tokens[i].text));
            fprintf(fptr,"\tsyscall");
        }
    printf("%d",int_lit);
        if (tokens[i].type==int_lit){
            m_stack_size+=4;
            strcpy(adrs[adr_i].name,tokens[i].name);
            adrs[adr_i].asm_address=m_stack_size;
            fprintf(fptr,"\tmov	DWORD PTR -%d[rbp], %s\n",m_stack_size,(tokens[i].text));
            adr_i++;
        }
    }
    printf("|%p|%d|",adrs[0].name,adrs[0].asm_address);
    fprintf(fptr,"\t");
}





struct NodeExpr{
    struct Token int_lit;
};
struct NodeReturn {
    struct NodeExpr *expr; 
};

typedef enum{
    return_node,
    int_node,
    var_node
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
        printf(" %s str",token->name);
        if (strcmp(token->name,"return")==0){
            return returnStatement();
        }
        if (strcmp(token->name,"int")==0){
            return variableStatement();
        }

        {
            struct Token* token=currentToken();
        
            printf("\nNIEUZYWANE TOKENY: %s}",token->name);
            struct Node* node=malloc(sizeof(struct Node));
            node->type=int_node;
            node->data.intValue=10;
            node->nextNode=NULL;
            return node;
        }

    };


struct Node* parser(struct Token *tokens){
    
    struct Token* token=currentToken();
    struct Node* program=NULL;
    struct Node* current=NULL;
    
    while (token->type!=0){
        
        struct Node* kw=parseKeywords();
        if (kw){
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
    
    //for (int k=0; k<30; k++){
    //printf("|%d|-|%s|-|%s|\n",tokens[k].type, tokens[k].name, tokens[k].text);
//}

    return program;
}
void print_all(struct Node* node){
    
    switch(node->type){
        case return_node:
            printf("\n RETURN |%d|",node->data.returnDecl.returnValue);
        case var_node:
            printf("\nVAR |%s|%d|",node->data.varDecl.varName,node->data.varDecl.varValue);
    }
    if (node->nextNode!=NULL){
    print_all(node->nextNode);}

}
//oosbna funkcje do parsowania jezyka
struct Token *tokenize(char* buf, size_t buf_size){
    printf("%d|",sizeof(Node));
    bool wait_for_value=false;
    int waiting_for=-1;
    struct Token *tokens=malloc(100*sizeof(struct Token));
    int token_i=0;
    char digit_buf[32]="";
    int digit_buf_i=0;
    char kw_buf[32]="";
    int kw_buf_i=0;
    
    for (int i=0; i<buf_size; i++){
       
        while (isalpha(buf[i])){
            kw_buf[kw_buf_i]=buf[i];
            kw_buf_i++;
            i++;
        }
        kw_buf[kw_buf_i]='\0';
        while (isdigit(buf[i])){
            digit_buf[digit_buf_i]=buf[i];
            digit_buf_i++;
            i++;
        }
       
        if (strcmp(digit_buf,"")!=0){
            tokens[token_i].type=number;
            strcpy(tokens[token_i].name,digit_buf);
            memset(kw_buf,0,strlen(kw_buf));
            memset(digit_buf,0,strlen(digit_buf));
            token_i++;
        }
        if (strcmp(kw_buf,"int")==0 && buf[i]==' '){
            tokens[token_i].type=int_lit;
            strcpy(tokens[token_i].name,kw_buf);
            memset(kw_buf,0,strlen(kw_buf));
            memset(digit_buf,0,strlen(digit_buf));
            token_i++;
        }
        if (strcmp(kw_buf,"return")==0 && buf[i]==' '){
            
            tokens[token_i].type=_return;
            strcpy(tokens[token_i].name,kw_buf);
            memset(kw_buf,0,strlen(kw_buf));
            memset(digit_buf,0,strlen(digit_buf));
            token_i++;
        }
        if (strcmp(kw_buf,"")!=0){
            tokens[token_i].type=_str;
            strcpy(tokens[token_i].name,kw_buf);
            memset(kw_buf,0,strlen(kw_buf));
            memset(digit_buf,0,strlen(digit_buf));
            token_i++;
        }
        if (buf[i]==';'){   
            tokens[token_i].type=semicolon;
            tokens[token_i].name[0]=buf[i];
            token_i++;
            
        }
         if (buf[i]=='='){
                tokens[token_i].type=equ;
                tokens[token_i].name[0]=buf[i];
                token_i++;
        }
        if (buf[i]=='+'){
                tokens[token_i].type=add;
                tokens[token_i].name[0]=buf[i];
                token_i++;
        }
        if (buf[i]=='-'){
                tokens[token_i].type=sub;
                tokens[token_i].name[0]=buf[i];
                token_i++;
        }
      
        digit_buf_i=0;
        memset(digit_buf,0,strlen(digit_buf));
        kw_buf_i=0;
        memset(kw_buf,0,strlen(kw_buf));
        
    }
    for (int k=0; k<30; k++){
        if (tokens[k].type==int_lit && tokens[k].text==""){
            strcpy(tokens[k].text,"0");}
        printf("|%d|-|%s|-|%s|\n",tokens[k].type, tokens[k].name, tokens[k].text);
    }
   
    return tokens;
}




int main(int argc, char* argv[]){  
    
    tokens=malloc(100*sizeof(struct Token));
  
    int st_n=0;
    if (argc!=2){
        perror("No input file to read \n");
        return 0;
    }
    FILE *fptr;
    fptr=fopen(argv[1],"rb");
    size_t buf_size=20;
    char *buf=malloc(buf_size);
    if (fptr==NULL){
        return 0;
    }
    
    int c;
    while((c=fgetc(fptr))!=EOF){
        char ch=(char) c;
        strcat(buf,&ch);
        if (strlen(buf)==buf_size){
            buf_size=buf_size*2;
            buf=realloc(buf, buf_size);
        }
    }
    fclose(fptr);
    
   /*struct Token tokens[]={
        {int_lit,"b","132"},
        {int_lit,"c","132"},
        {_return,NULL,"123"}
   };*/
    buf[strlen(buf)]='\0';
    size_t tokens_length = 0;
    tokens=tokenize(buf, strlen(buf));
    printf("nie");
    struct Node* program=parser(tokens);
    print_all(program);
    while (tokens[tokens_length].name[0] != '\0') {
        tokens_length++;}
    
 
    
    //generate_assembly(tokens,tokens_length); //causes segfault for buffer for some reason ALE CHYBA DLATEGO ZE TOKENS PUSTE JEST
    return 0;


}