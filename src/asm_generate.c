#include "asm_generate.h"
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