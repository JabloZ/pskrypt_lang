#include "asm_generate.h"
bool asm_variable_exists(char *name);

void generate_assembly_recursive(struct Node *programNode, FILE *fptr, FILE *fptr_var){
   
   
    struct Node* current_node=programNode;
    
    
    while(current_node!=NULL){
       
        if (current_node->type==semi_node){
            can_change=true;
        }
        if(current_node->type==var_node){
            
            if(can_change==true){
                can_change=false;
                
                strcpy(changed_var,current_node->data.varDecl.varName);
                fprintf(fptr_var,"\t%s dd %d\n",current_node->data.varDecl.varName, current_node->data.varDecl.varValue);
            
                
                }
            bool res=asm_variable_exists(current_node->data.varDecl.varName);
            if (res==false){
                    sprintf(var_decl,"\t%s dd %d\n",current_node->data.varDecl.varName, current_node->data.varDecl.varValue);
                    strcat(variables,var_decl);
            }
            
        }
        if (current_node->type==return_node){
        
            fprintf(fptr,"\tmov rax, 60\n");
            fprintf(fptr,"\tmov rdi, [c]\n");
            fprintf(fptr,"\tsyscall\n");
        }
        if (current_node->type==int_node){
           
            fprintf(fptr,"\tmov rax, %d\n",current_node->data.intValue);
            
        }
        
        if (current_node->type==var_node){
            fprintf(fptr,"\tmov rax, [%s]\n",current_node->data.varDecl.varName);
        }
         if (current_node->type == binary_op_node) {
            printf("Binary operation with operator: %s\n", current_node->data.binaryOp.op); // Debugging info

            if (strcmp(current_node->data.binaryOp.op, "=") == 0) {
                
                
                generate_assembly_recursive(current_node->data.binaryOp.right, fptr, fptr_var);
                fprintf(fptr, "\tmov [%s], rax\n", current_node->data.binaryOp.left->data.varDecl.varName);
            } else {
                if (current_node->data.binaryOp.left == NULL || current_node->data.binaryOp.right == NULL) {
                    printf("Error: left or right operand is NULL\n");
                    exit(EXIT_FAILURE);
                }
                // Left operand evaluation
                 
                 fprintf(fptr, "\tpush rax\n");
                generate_assembly_recursive(current_node->data.binaryOp.left, fptr, fptr_var);
                
                printf("\n after this should be int");
                fprintf(fptr, "\tpop rbx\n");
                generate_assembly_recursive(current_node->data.binaryOp.right, fptr, fptr_var);
                
                // Right operand evaluation
               

                if (strcmp(current_node->data.binaryOp.op, "+") == 0) {
                    fprintf(fptr, "\tadd rax, rbx\n");
                    fprintf(fptr, "\tmov [%s], rax\n",changed_var);
                }
                 if (strcmp(current_node->data.binaryOp.op, "-") == 0) {
                    printf("\nat least once here");
                    fprintf(fptr, "\tsub rax, rbx\n");
                    fprintf(fptr, "\tmov [%s], rax\n",changed_var);
                }
                // Można dodać obsługę innych operatorów tutaj
                
            }
        }
        
        
        struct Node *next_node = current_node->nextNode;
        current_node->nextNode = NULL; // Avoid potential cyclic dependencies
        current_node = next_node;
        
    }
    
    
    
}
bool asm_variable_exists(char *name){
    for (int i=0; i<100; i++){
       
        if(strcmp(name,variables_d[i])==0){
            return true;
        }
        if (strcmp(variables_d[i],"")==0){
            //variables_d[i]=name;
            strcpy(variables_d[i],name);
            return false;
        }
    }
    //strcpy(variables_d[i],name);
    return false;
}
void generate_assembly(struct Node *programNode) {
    FILE *fptr;
    FILE *fptr_var;
    fptr = fopen("output.asm", "w+");
    fptr_var = fopen("asm_vars.asm", "w+");
    if (fptr == NULL || fptr_var == NULL) {
        printf("Error opening file!\n");
        exit(EXIT_FAILURE);
    }
    
    can_change=true;
    fprintf(fptr_var,"section .data\n");
    fprintf(fptr,"section .text\n");
    fprintf(fptr,"\tglobal _start\n");
    fprintf(fptr,"_start:\n");
    fprintf(fptr,"\tpush rbp\n");
    fprintf(fptr,"\tmov rbp, rsp\n");
    strcpy(variables,"section .data\n");
    generate_assembly_recursive(programNode,fptr, fptr_var);
    
    fprintf(fptr, variables);
    fclose(fptr);
    fclose(fptr_var);
}