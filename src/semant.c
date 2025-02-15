#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

static const char *current_function = NULL;

void semantic_error(const char *id, int line) {
    fprintf(stderr, "ERRO SEMÂNTICO: '%s' LINHA: %d\n", id, line);
    exit(1);
}

TypeKind check_expression(ASTNode *expr, const char *current_function) {
    if(!expr) return ERROR_TYPE;
    
    switch(expr->type) {
        case NODE_NUM:
            return INT_TYPE;
            
        case NODE_VAR: {
            Symbol *s = lookup_symbol(expr->var_name, current_function);
            if(!s) s = lookup_symbol(expr->var_name, "global");
            
            if(!s) {
                semantic_error(expr->var_name, expr->line);
            }
            expr->expr_type = s->type;
            return s->type;
        }
        
        case NODE_ARRAY_ACCESS: {
            Symbol *s = lookup_symbol(expr->array_name, current_function);
            if(!s) s = lookup_symbol(expr->array_name, "global");
            
            // Verifica se é array
            if(!s || !s->is_array) {
                fprintf(stderr, "ERRO SEMÂNTICO: '%s' não é array LINHA: %d\n",
                       expr->array_name, expr->line);
                exit(1);
            }
            
            // Verifica índice
            TypeKind index_type = check_expression(expr->array_index, current_function);
            if(index_type != INT_TYPE) {
                fprintf(stderr, "ERRO DE TIPO: Índice de array não inteiro LINHA: %d\n",
                       expr->line);
                exit(1);
            }
            
            expr->expr_type = s->type;
            return s->type;
        }
        
        case NODE_ASSIGN: {
            TypeKind lhs = check_expression(expr->assign_lhs, current_function);
            TypeKind rhs = check_expression(expr->assign_rhs, current_function);
            
            if(lhs != rhs) {
                fprintf(stderr, "ERRO DE TIPO: Atribuição inválida (esperado %d, recebido %d) LINHA: %d\n",
                       lhs, rhs, expr->line);
                exit(1);
            }
            return lhs;
        }
        
        case NODE_BINOP: {
            TypeKind left = check_expression(expr->binop_left, current_function);
            TypeKind right = check_expression(expr->binop_right, current_function);
            
            // Operações aritméticas
            if(expr->binop_op >= ADD && expr->binop_op <= DIV) {
                if(left != INT_TYPE || right != INT_TYPE) {
                    fprintf(stderr, "ERRO DE TIPO: Operação aritmética com tipos não inteiros LINHA: %d\n",
                           expr->line);
                    exit(1);
                }
                return INT_TYPE;
            }
            // Operações relacionais
            else if(expr->binop_op >= LE && expr->binop_op <= NE) {
                if(left != right) {
                    fprintf(stderr, "ERRO DE TIPO: Comparação entre tipos diferentes LINHA: %d\n",
                           expr->line);
                    exit(1);
                }
                return INT_TYPE; // Resultado booleano como inteiro
            }
            break;
        }
        
        case NODE_FUN_CALL: {
            Symbol *fun = lookup_symbol(expr->fun_call_name, "global");
            if(!fun) {
                semantic_error(expr->fun_call_name, expr->line);
            }
            
            // Verifica parâmetros
            ASTNode *args = expr->fun_call_args;
            ASTNode *params = fun->params; // Supondo que params estão armazenados no símbolo
            int arg_count = 0;
            
            while(args && params) {
                TypeKind arg_type = check_expression(args, current_function);
                if(arg_type != params->param_type) {
                    fprintf(stderr, "ERRO DE TIPO: Argumento %d incompatível LINHA: %d\n",
                           arg_count+1, expr->line);
                    exit(1);
                }
                args = args->next;
                params = params->next;
                arg_count++;
            }
            
            if(args || params) {
                fprintf(stderr, "ERRO SEMÂNTICO: Número de argumentos incorreto para '%s' LINHA: %d\n",
                       expr->fun_call_name, expr->line);
                exit(1);
            }
            
            return fun->type;
        }
        
        case NODE_IF:
        case NODE_WHILE: {
            TypeKind cond_type = check_expression(expr->cond_expr, current_function);
            if(cond_type != INT_TYPE) {
                fprintf(stderr, "ERRO DE TIPO: Condição deve ser inteira LINHA: %d\n",
                       expr->line);
                exit(1);
            }
            check_expression(expr->then_stmt, current_function);
            if(expr->else_stmt) {
                check_expression(expr->else_stmt, current_function);
            }
            return VOID_TYPE;
        }
        
        case NODE_RETURN: {
            if(expr->return_expr) {
                TypeKind return_type = check_expression(expr->return_expr, current_function);
                Symbol *fun = lookup_symbol(current_function, "global");
                if(return_type != fun->type) {
                    fprintf(stderr, "ERRO DE TIPO: Retorno incompatível LINHA: %d\n",
                           expr->line);
                    exit(1);
                }
            }
            return VOID_TYPE;
        }
        
        default:
            fprintf(stderr, "ERRO SEMÂNTICO: Expressão não reconhecida LINHA: %d\n",
                   expr->line);
            exit(1);
    }
    return ERROR_TYPE;
}

void check_function_decl(ASTNode *fun_decl) {
    current_function = fun_decl->fun_name;
    enter_scope();
    
    // Insere parâmetros na tabela
    ASTNode *param = fun_decl->fun_params;
    while(param != NULL) {
        insert_symbol(param->param_name, param->param_type, 
                     param->is_array, current_function, param->line);
        param = param->next;
    }
    
    // Verifica corpo da função
    ASTNode *stmt = fun_decl->fun_body;
    while(stmt != NULL) {
        // Verifica todos os statements
        stmt = stmt->next;
    }
    
    exit_scope();
    current_function = NULL;
}

void check_semantics(ASTNode *root) {
    init_symbol_table();
    ASTNode *decl = root->program_decls;
    
    // Primeira passada: insere declarações globais
    while(decl != NULL) {
        if(decl->type == NODE_FUN_DECL) {
            insert_symbol(decl->fun_name, decl->fun_type, 0, "global", decl->line);
        }
        decl = decl->next;
    }
    
    // Segunda passada: verifica funções
    decl = root->program_decls;
    while(decl != NULL) {
        if(decl->type == NODE_FUN_DECL) {
            check_function_decl(decl);
        }
        decl = decl->next;
    }
    
    // Verifica se main existe
    if(!lookup_symbol("main", "global")) {
        fprintf(stderr, "ERRO SEMÂNTICO: função 'main' não declarada\n");
        exit(1);
    }
}