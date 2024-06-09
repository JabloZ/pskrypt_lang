#include "asm_generate.h"
void generate_assembly(struct Node *programNode){
    struct Var_adr *adrs=malloc(sizeof(struct Var_adr)*node_count);
    int adr_i=0;
    FILE *fptr;
    FILE *fptr_var;
    FILE *fptr_out;
    int m_stack_size=0;
    char variables[1000]="section .data\n"; //do optymalizacji bazowane na ilosci zmiennych np
    struct Node* current_node=programNode;
    fptr=fopen("output.asm","w+");
    fptr_var=fopen("asm_vars.asm","w+");
    fprintf(fptr_var,"section .data\n");

    fprintf(fptr,"global _start\n");
    fprintf(fptr,"_start:\n");
    fprintf(fptr,"\tpush rbp\n");
    fprintf(fptr,"\tmov rbp, rsp\n");
    char var_decl[100];
    while(current_node!=NULL){
        if(current_node->type==var_node){
            sprintf(var_decl,"\t%s dd %d\n",current_node->data.varDecl.varName, current_node->data.varDecl.varValue);
            strcat(variables,var_decl);
            fprintf(fptr_var,"\t%s dd %d\n",current_node->data.varDecl.varName, current_node->data.varDecl.varValue);   
        }
        if (current_node->type==return_node){
        
            fprintf(fptr,"\tmov rax, 60\n");
            fprintf(fptr,"\tmov rdi, %d\n",(current_node->data.returnDecl.returnValue));
            fprintf(fptr,"\tsyscall\n");
        }
        current_node=current_node->nextNode;
    }
    fprintf(fptr, variables);
    /*
    for (int i=0; i<=node_count; i++){
        if (type==return_node){
            
        }
        if (tokens[i].type==int_lit){
            m_stack_size+=4;
            strcpy(adrs[adr_i].name,tokens[i].name);
            adrs[adr_i].asm_address=m_stack_size;
            fprintf(fptr,"\tmov	DWORD PTR -%d[rbp], %s\n",m_stack_size,(tokens[i].text));
            adr_i++;
        }
    }*/
    fprintf(fptr,"\t");
}