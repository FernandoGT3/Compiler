#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"

static int temp_counter = 0;
static int label_counter = 0;

// Funções auxiliares
static char* new_temp() {
    char *temp = malloc(32);
    sprintf(temp, "t%d", temp_counter++);
    return temp;
}

static char* new_label() {
    char *label = malloc(32);
    sprintf(label, "L%d", label_counter++);
    return label;
}

static TAC* tac_append(TAC *code1, TAC *code2) {
    if(!code1) return code2;
    
    TAC *last = code1;
    while(last->next) last = last->next;
    last->next = code2;
    if(code2) code2->prev = last;
    return code1;
}

// Geração de código para diferentes construções
static TAC* gen_expression(ASTNode *expr);
static TAC* gen_assignment(ASTNode *assign);
static TAC* gen_binop(ASTNode *binop);
static TAC* gen_if(ASTNode *if_stmt);
static TAC* gen_while(ASTNode *while_stmt);
static TAC* gen_function_call(ASTNode *call);

TAC* generate_code(ASTNode *node) {
    if(!node) return NULL;
    
    switch(node->type) {
        case NODE_PROGRAM:
            return generate_code(node->program.declarations);
            
        case NODE_FUN_DECL: {
            TAC *code = NULL;
            
            // Prologo da função
            TAC *prolog = malloc(sizeof(TAC));
            sprintf(prolog->op, "FUNC");
            sprintf(prolog->result, "%s", node->fun_decl.fun_name);
            code = tac_append(code, prolog);
            
            // Gerar código para o corpo
            code = tac_append(code, generate_code(node->fun_decl.body));
            
            // Epilogo
            TAC *epilog = malloc(sizeof(TAC));
            sprintf(epilog->op, "ENDFUNC");
            code = tac_append(code, epilog);
            
            return code;
        }
        
        case NODE_ASSIGN:
            return gen_assignment(node);
            
        case NODE_BINOP:
            return gen_binop(node);
            
        case NODE_IF_STMT:
            return gen_if(node);
            
        case NODE_WHILE_STMT:
            return gen_while(node);
            
        case NODE_FUN_CALL:
            return gen_function_call(node);
            
        case NODE_RETURN_STMT: {
            TAC *code = NULL;
            if(node->return_stmt.return_expr) {
                TAC *expr_code = gen_expression(node->return_stmt.return_expr);
                code = tac_append(code, expr_code);
                
                TAC *ret = malloc(sizeof(TAC));
                sprintf(ret->op, "RETURN");
                strcpy(ret->arg1, expr_code->result);
                code = tac_append(code, ret);
            } else {
                TAC *ret = malloc(sizeof(TAC));
                sprintf(ret->op, "RETURN");
                code = tac_append(code, ret);
            }
            return code;
        }
        
        // Outros nós (lista de declarações, etc.)
        default:
            if(node->next) return tac_append(generate_code(node), generate_code(node->next));
            return generate_code(node);
    }
}

static TAC* gen_expression(ASTNode *expr) {
    if(!expr) return NULL;
    
    switch(expr->type) {
        case NODE_NUM: {
            TAC *t = malloc(sizeof(TAC));
            char *temp = new_temp();
            sprintf(t->op, "=");
            sprintf(t->arg1, "%d", expr->num.value);
            strcpy(t->result, temp);
            return t;
        }
        
        case NODE_VAR: {
            TAC *t = malloc(sizeof(TAC));
            char *temp = new_temp();
            sprintf(t->op, "=");
            strcpy(t->arg1, expr->var.var_name);
            strcpy(t->result, temp);
            return t;
        }
        
        case NODE_BINOP:
            return gen_binop(expr);
            
        case NODE_FUN_CALL:
            return gen_function_call(expr);
            
        default:
            return NULL;
    }
}

static TAC* gen_assignment(ASTNode *assign) {
    TAC *code = gen_expression(assign->assign.rhs);
    
    TAC *assign_tac = malloc(sizeof(TAC));
    sprintf(assign_tac->op, "=");
    strcpy(assign_tac->arg1, code ? code->result : "");
    strcpy(assign_tac->result, assign->assign.lhs->var.var_name);
    
    return tac_append(code, assign_tac);
}

static TAC* gen_binop(ASTNode *binop) {
    TAC *left = gen_expression(binop->binop.left);
    TAC *right = gen_expression(binop->binop.right);
    
    TAC *code = tac_append(left, right);
    
    TAC *op_tac = malloc(sizeof(TAC));
    char *temp = new_temp();
    
    switch(binop->binop.op) {
        case OP_ADD: strcpy(op_tac->op, "+"); break;
        case OP_SUB: strcpy(op_tac->op, "-"); break;
        case OP_MUL: strcpy(op_tac->op, "*"); break;
        case OP_DIV: strcpy(op_tac->op, "/"); break;
        
        // Operadores relacionais
        case OP_LT: strcpy(op_tac->op, "<"); break;
        case OP_LE: strcpy(op_tac->op, "<="); break;
        case OP_GT: strcpy(op_tac->op, ">"); break;
        case OP_GE: strcpy(op_tac->op, ">="); break;
        case OP_EQ: strcpy(op_tac->op, "=="); break;
        case OP_NE: strcpy(op_tac->op, "!="); break;

        // Operadores lógicos
        case OP_AND: strcpy(op_tac->op, "&&"); break;
        case OP_OR: strcpy(op_tac->op, "||"); break;

        default:
            fprintf(stderr, "ERRO: Operador binário desconhecido\n");
            exit(1);
    }
    
    strcpy(op_tac->arg1, left->result);
    strcpy(op_tac->arg2, right->result);
    strcpy(op_tac->result, temp);
    
    return tac_append(code, op_tac);
}

static TAC* gen_if(ASTNode *if_stmt) {
    char *else_label = new_label();
    char *end_label = new_label();
    
    TAC *cond_code = gen_expression(if_stmt->if_stmt.condition);
    TAC *code = cond_code;
    
    // Ifz (condição) goto ELSE
    TAC *branch = malloc(sizeof(TAC));
    sprintf(branch->op, "IFZ");
    strcpy(branch->arg1, cond_code->result);
    strcpy(branch->result, else_label);
    code = tac_append(code, branch);
    
    // Código THEN
    TAC *then_code = generate_code(if_stmt->if_stmt.then_stmt);
    code = tac_append(code, then_code);
    
    // Goto END
    TAC *jump_end = malloc(sizeof(TAC));
    sprintf(jump_end->op, "GOTO");
    strcpy(jump_end->result, end_label);
    code = tac_append(code, jump_end);
    
    // Label ELSE
    TAC *else_lbl = malloc(sizeof(TAC));
    sprintf(else_lbl->op, "LABEL");
    strcpy(else_lbl->result, else_label);
    code = tac_append(code, else_lbl);
    
    // Código ELSE (se existir)
    if(if_stmt->if_stmt.else_stmt) {
        TAC *else_code = generate_code(if_stmt->if_stmt.else_stmt);
        code = tac_append(code, else_code);
    }
    
    // Label END
    TAC *end_lbl = malloc(sizeof(TAC));
    sprintf(end_lbl->op, "LABEL");
    strcpy(end_lbl->result, end_label);
    code = tac_append(code, end_lbl);
    
    return code;
}

static TAC* gen_while(ASTNode *while_stmt) {
    char *loop_label = new_label();
    char *end_label = new_label();
    
    TAC *code = NULL;
    
    // Label LOOP
    TAC *loop_lbl = malloc(sizeof(TAC));
    sprintf(loop_lbl->op, "LABEL");
    strcpy(loop_lbl->result, loop_label);
    code = tac_append(code, loop_lbl);
    
    // Condição
    TAC *cond_code = gen_expression(while_stmt->while_stmt.condition);
    code = tac_append(code, cond_code);
    
    // Ifz (condição) goto END
    TAC *branch = malloc(sizeof(TAC));
    sprintf(branch->op, "IFZ");
    strcpy(branch->arg1, cond_code->result);
    strcpy(branch->result, end_label);
    code = tac_append(code, branch);
    
    // Corpo do loop
    TAC *body_code = generate_code(while_stmt->while_stmt.body);
    code = tac_append(code, body_code);
    
    // Goto LOOP
    TAC *jump_loop = malloc(sizeof(TAC));
    sprintf(jump_loop->op, "GOTO");
    strcpy(jump_loop->result, loop_label);
    code = tac_append(code, jump_loop);
    
    // Label END
    TAC *end_lbl = malloc(sizeof(TAC));
    sprintf(end_lbl->op, "LABEL");
    strcpy(end_lbl->result, end_label);
    code = tac_append(code, end_lbl);
    
    return code;
}

static TAC* gen_function_call(ASTNode *call) {
    TAC *code = NULL;
    ASTNode *arg = call->fun_call.args;
    int arg_count = 0;
    
    // Gerar código para argumentos
    while(arg) {
        TAC *arg_code = gen_expression(arg);
        code = tac_append(code, arg_code);
        
        // Passar argumento
        TAC *param = malloc(sizeof(TAC));
        sprintf(param->op, "PARAM");
        strcpy(param->arg1, arg_code->result);
        code = tac_append(code, param);
        
        arg = arg->next;
        arg_count++;
    }
    
    // Chamada da função
    TAC *call_tac = malloc(sizeof(TAC));
    sprintf(call_tac->op, "CALL");
    strcpy(call_tac->arg1, call->fun_call.fun_name);
    sprintf(call_tac->arg2, "%d", arg_count);

    Symbol *fun_sym = lookup_symbol(call->fun_call.fun_name, "global");
    if(fun_sym && fun_sym->type != VOID_TYPE) {
        char *temp = new_temp();
        strcpy(call_tac->result, temp);
    }
    
    code = tac_append(code, call_tac);
    
    return code;
}

void print_tac(TAC *code) {
    printf("\n=== CÓDIGO INTERMEDIÁRIO (TAC) ===\n");
    TAC *current = code;
    while(current) {
        if(strcmp(current->op, "LABEL") == 0) {
            printf("%s:\n", current->result);
        }
        else if(strcmp(current->op, "FUNC") == 0) {
            printf("\nFUNCTION %s:\n", current->result);
        }
        else if(strcmp(current->op, "ENDFUNC") == 0) {
            printf("END %s\n", current->result);
        }
        else {
            printf("%-8s", current->op);
            if(current->arg1[0]) printf(" %-8s", current->arg1);
            if(current->arg2[0]) printf(" %-8s", current->arg2);
            if(current->result[0]) printf(" -> %-8s", current->result);
            printf("\n");
        }
        current = current->next;
    }
}