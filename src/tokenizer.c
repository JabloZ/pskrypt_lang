#include "tokenizer.h"
bool is_keyword(char *name){

}
struct Token *tokenize(char* buf, size_t buf_size){
    cur_tok=0;
    bool wait_for_value=false;
    int waiting_for=-1;
    struct Token *tokens=malloc(100*sizeof(struct Token));
    int token_i=0;
    char digit_buf[32]="";
    int digit_buf_i=0;
    char kw_buf[32]="";
    int kw_buf_i=0;
    char keywords[10][15]={"if","while","greater","greater_equal","lesser","lesser_equal","equal","end_loop","end_if","not_equal"};
    for (int i=0; i<buf_size; i++){
       
        while (isalpha(buf[i]) || buf[i]=='_'){
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
        if (strcmp(kw_buf,"var")==0 && buf[i]==' '){
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
            //for (int i=0; i<sizeof())
            for (int i=0; i<(sizeof(keywords)/sizeof(keywords[0])); i++){
                if (strcmp(kw_buf,keywords[i])){
                        tokens[token_i].type=keyword_tok;
                        strcpy(tokens[token_i].name,kw_buf);
                }
            }
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
        if (buf[i]=='*'){
                tokens[token_i].type=mult;
                tokens[token_i].name[0]=buf[i];
                token_i++;
        }
        if (buf[i]=='/'){
                tokens[token_i].type=_div;
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
