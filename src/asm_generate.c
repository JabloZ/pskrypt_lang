#include "asm_generate.h"
bool asm_variable_exists(char *name);

int free_on_loopstack(){
    for (int i=0;i<20;i++){
        if (loopstack[i]==0){
            loopstack[i]=1;
            return i;
        }
    }
}

int free_on_ifstack(){
    for (int i=0;i<20;i++){
        if (ifstack[i]==0){
            ifstack[i]=1;
            return i;
        }
    }
}
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
                fprintf(fptr_var,"\t%s dq %d\n",current_node->data.varDecl.varName, current_node->data.varDecl.varValue);
            }
            bool res=asm_variable_exists(current_node->data.varDecl.varName);
            if (res==false){
                sprintf(var_decl,"\t%s dq %d\n",current_node->data.varDecl.varName, current_node->data.varDecl.varValue);
                strcat(variables,var_decl);
            }
        }
        if (current_node->type==end_loop_node){
            fprintf(fptr,"\tjmp .loop%d\n",current_node->data.endLoopDecl.loopNum);
            fprintf(fptr,".end%d:\n",current_node->data.endLoopDecl.loopNum);
        }
        if (current_node->type==while_node){
            printf("\n blad jakis");
            fflush(stdout);
            int loop_i=free_on_loopstack();
            int i=current_node->data.whileDecl.loopNum;
            printf("\n blad jakis");
            fflush(stdout);
            
            fprintf(fptr,"\tjmp .loop%d\n",i);
            fprintf(fptr,"\tmov rax, 0\n");
            int to_pass=current_node->data.whileDecl.loopNum;
            printf("\nto_pass;%d",to_pass);
            fprintf(fptr,".loop%d:\n",to_pass);
            if (current_node->data.whileDecl.first->type==var_node){
                fprintf(fptr,"\tmov rax, [%s]\n",current_node->data.whileDecl.first->data.varDecl.varName);
            }
            else{ 
                fprintf(fptr,"\tmov rax, %d\n",current_node->data.whileDecl.first->data.intValue);
            }
            if (current_node->data.whileDecl.second->type==var_node){
                fprintf(fptr,"\tcmp rax, [%s]\n",current_node->data.whileDecl.second->data.varDecl.varName);
            }
            else{
                 fprintf(fptr,"\tcmp rax, %d\n",current_node->data.whileDecl.second->data.intValue);
            }
            if (strcmp(current_node->data.whileDecl.instruction,"greater")==0){
            fprintf(fptr,"\tjl .end%d\n",loop_i);}
            if (strcmp(current_node->data.whileDecl.instruction,"lesser")==0){
            fprintf(fptr,"\tjg .end%d\n",loop_i);}
            if (strcmp(current_node->data.whileDecl.instruction,"greater_equal")==0){
            fprintf(fptr,"\tjle .end%d\n",loop_i);}
            if (strcmp(current_node->data.whileDecl.instruction,"lesser_equal")==0){
            fprintf(fptr,"\tjge .end%d\n",loop_i);}
            if (strcmp(current_node->data.whileDecl.instruction,"equal")==0){
            fprintf(fptr,"\tjne .end%d\n",loop_i);}
             if (strcmp(current_node->data.whileDecl.instruction,"not_equal")==0){
            fprintf(fptr,"\tje .end%d\n",loop_i);}
            
            
        }


        if (current_node->type==end_if_node){
            
            fprintf(fptr,".end_if%d:\n",current_node->data.endIfDecl.ifNum);
        }
        if (current_node->type==if_node){
            int if_i=free_on_ifstack();
            int i=current_node->data.ifDecl.ifNum;
           
            
            //fprintf(fptr,"\tjmp .loop%d\n",i);
            
           
            int to_pass=current_node->data.ifDecl.ifNum;
            
            if (current_node->data.ifDecl.first->type==var_node){
                fprintf(fptr,"\tmov rax, [%s]\n",current_node->data.ifDecl.first->data.varDecl.varName);
            }
            else{ 
                fprintf(fptr,"\tmov rax, %d\n",current_node->data.ifDecl.first->data.intValue);
            }
            if (current_node->data.ifDecl.second->type==var_node){
                fprintf(fptr,"\tcmp rax, [%s]\n",current_node->data.ifDecl.second->data.varDecl.varName);
            }
            else{
                 fprintf(fptr,"\tcmp rax, %d\n",current_node->data.ifDecl.second->data.intValue);
            }
            if (strcmp(current_node->data.ifDecl.instruction,"greater")==0){
            fprintf(fptr,"\tjl .end_if%d\n",if_i);}
            if (strcmp(current_node->data.ifDecl.instruction,"lesser")==0){
            fprintf(fptr,"\tjg .end_if%d\n",if_i);}
            if (strcmp(current_node->data.ifDecl.instruction,"greater_equal")==0){
            fprintf(fptr,"\tjle .end_if%d\n",if_i);}
            if (strcmp(current_node->data.ifDecl.instruction,"lesser_equal")==0){
            fprintf(fptr,"\tjge .end_if%d\n",if_i);}
            if (strcmp(current_node->data.ifDecl.instruction,"equal")==0){
            fprintf(fptr,"\tjne .end_if%d\n",if_i);}
             if (strcmp(current_node->data.ifDecl.instruction,"not_equal")==0){
            fprintf(fptr,"\tje .end_if%d\n",if_i);}
            
            
        }
        
        if (current_node->type==return_node){
            fprintf(fptr,"\tmov rax, 60\n");
            if (current_node->data.returnDecl.returnValue->type==var_node){
                fprintf(fptr,"\tmov rdi, [%s]\n",current_node->data.returnDecl.returnValue->data.varDecl.varName);
            }
            else if(current_node->data.returnDecl.returnValue->type==int_node){
                fprintf(fptr,"\tmov rdi, %d\n",current_node->data.returnDecl.returnValue->data.intValue);
            }
            
            fprintf(fptr,"\tsyscall\n");
        }
        if (current_node->type==int_node){
            fprintf(fptr,"\tmov rax, %d\n",current_node->data.intValue); 
        }
        if (current_node->type==var_node){
            fprintf(fptr,"\tmov rax, [%s]\n",current_node->data.varDecl.varName);
        }
         if (current_node->type == binary_op_node) {
            if (strcmp(current_node->data.binaryOp.op, "=") == 0) {
                generate_assembly_recursive(current_node->data.binaryOp.right, fptr, fptr_var);
                fprintf(fptr, "\tmov [%s], rax\n", current_node->data.binaryOp.left->data.varDecl.varName);
            } 
            else {
                if (current_node->data.binaryOp.left == NULL || current_node->data.binaryOp.right == NULL) {
                    exit(EXIT_FAILURE);
                }
                   
                    fprintf(fptr, "\tpush rax\n");
                     
                if (strcmp(current_node->data.binaryOp.op, "+") == 0) {
                    generate_assembly_recursive(current_node->data.binaryOp.right, fptr, fptr_var);                    
                    fprintf(fptr, "\tpop rbx\n");
                    fprintf(fptr, "\tadd rax, rbx\n");
                    fprintf(fptr, "\tmov [%s], rax\n",changed_var);
                }
                 if (strcmp(current_node->data.binaryOp.op, "-") == 0) {   
                     fprintf(fptr, "\tpop rbx\n");
                    generate_assembly_recursive(current_node->data.binaryOp.right, fptr, fptr_var); 
                    fprintf(fptr, "\tsub rbx, rax\n"); // DLA 24-7 TO PRZECHOWA -17+8 (247)
                    fprintf(fptr, "\tmov [%s], rbx\n",changed_var); //
                    fprintf(fptr, "\tmov rax, rbx\n",changed_var);
                }
                 if (strcmp(current_node->data.binaryOp.op, "*") == 0) {
                    
                    generate_assembly_recursive(current_node->data.binaryOp.right, fptr, fptr_var);    
                    fprintf(fptr, "\tpop rbx\n");
                    fprintf(fptr, "\tmul rbx\n");
                    fprintf(fptr, "\tmov [%s], rax\n",changed_var);
                }
                if (strcmp(current_node->data.binaryOp.op, "/") == 0) {
                    
                    generate_assembly_recursive(current_node->data.binaryOp.right, fptr, fptr_var); 
                    fprintf(fptr, "\tpush rax\n");
                    fprintf(fptr, "\tpop rbx\n");
                    generate_assembly_recursive(current_node->data.binaryOp.left, fptr, fptr_var);         
                    fprintf(fptr, "\txor rdx, rdx\n");
                    fprintf(fptr, "\tdiv rbx\n");
                    fprintf(fptr, "\tmov [%s], rax\n",changed_var);
             
                }
            }
        }
        
        
        struct Node *next_node = current_node->nextNode;
        current_node->nextNode = NULL;
        current_node = next_node;
        
    }
    
}
bool asm_variable_exists(char *name){
    for (int i=0; i<100; i++){
        printf(" %d ",i);
        if(strcmp(name,variables_d[i])==0){
            return true;
        }
        if (strcmp(variables_d[i],"")==0){
            strcpy(variables_d[i],name);
            return false;
        }
    }
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
    for (int i=0; i<20; i++){
        loopstack[i]=0;
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