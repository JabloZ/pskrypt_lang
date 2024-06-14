#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
extern int errno;
#include "common.h"
#include "tokenizer.h"
#include "asm_generate.h"
#include "parser.h"

struct Token* tokenize(char* buf, size_t buf_size);
void generate_assembly(struct Node* programNode);
struct Node* parser(struct Token *tokens);

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
    buf[strlen(buf)]='\0';
    size_t tokens_length = 0;
    tokens=tokenize(buf, strlen(buf));
    
    struct Node* program=parser(tokens);
    while (tokens[tokens_length].name[0] != '\0') {
        tokens_length++;
    }
    
    generate_assembly(program); 
    
    //system("cat output.asm");
    system("nasm -f elf64 output.asm -o output.o");
    system("ld output.o -o output");
   
    return 0;


}