#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
extern int errno;
typedef enum{
    _return,
    int_lit,
    semicolon,
    equ,
    add, 
    sub
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

typedef struct Node{
    tokenType type;
    union{
        struct {
            int intValue;
            struct Node* value;
        } varDecl;
        struct {
            struct Node* returnValue;
        } returnStmt;
    } data;
};
void parser(struct Token *tokens){
    int current_i=0; 
    struct Token token=tokens[current_i];
    for (int i=0; i<sizeof(tokens)/sizeof(tokens[0]);i++){
        printf("%d",tokens[i].type);
    }
    /*for (int k=0; k<20; k++){
    printf("|%d|-|%s|-|%s|\n",tokens[k].type, tokens[k].name, tokens[k].text);
    }*/
}
//oosbna funkcje do parsowania jezyka
struct Token *tokenize(char* buf, size_t buf_size){
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
        if (strcmp(kw_buf,"int")==0 && buf[i]==' '){
            tokens[token_i].type=int_lit;
            memset(kw_buf,0,strlen(kw_buf));
            memset(digit_buf,0,strlen(digit_buf));
            token_i++;
        }
        if (strcmp(kw_buf,"return")==0 && buf[i]==' '){
            tokens[token_i].type=_return;
            memset(kw_buf,0,strlen(kw_buf));
            memset(digit_buf,0,strlen(digit_buf));
            token_i++;
        }
     
        if (buf[i]==';'){   
            tokens[token_i].type=semicolon;
            token_i++;
            
        }
         if (buf[i]=='='){
                tokens[token_i].type=equ;
                token_i++;
        }
        if (buf[i]=='+'){
                tokens[token_i].type=add;
                token_i++;
        }
        if (buf[i]=='-'){
                tokens[token_i].type=sub;
                token_i++;
        }
      
        digit_buf_i=0;
        memset(digit_buf,0,strlen(digit_buf));
        kw_buf_i=0;
        memset(kw_buf,0,strlen(kw_buf));
        
    }
    for (int k=0; k<20; k++){
        if (tokens[k].type==int_lit && tokens[k].text==""){
            strcpy(tokens[k].text,"0");}
        printf("|%d|-|%s|-|%s|\n",tokens[k].type, tokens[k].name, tokens[k].text);
    }
   
    return tokens;
}




int main(int argc, char* argv[]){  

   
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
    struct Token *tokens=tokenize(buf, strlen(buf));
    parser(tokens);
    while (tokens[tokens_length].name[0] != '\0') {
        tokens_length++;}
    
 
    
    //generate_assembly(tokens,tokens_length); //causes segfault for buffer for some reason ALE CHYBA DLATEGO ZE TOKENS PUSTE JEST
    return 0;


}