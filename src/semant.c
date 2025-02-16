#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/semant.h"
#include "../include/types.h"

static const char *current_function = NULL;

void semantic_error(const char *id, int line) {
    fprintf(stderr, "ERRO SEMÂNTICO: '%s' LINHA: %d\n", id, line);
    exit(1);
}

DataType check_expression(ASTNode *expr, const char *current_function) {
    if(!expr) return ERROR_TYPE;
    
    switch(expr->type) {
        case NODE_NUM:
            // expr->data_type = INT_TYPE;
            return INT_TYPE;
            
        case NODE_VAR: {
            Symbol *s = lookup_symbol(expr->var.var_name, current_function);
            if(!s) s = lookup_symbol(expr->var.var_name, "global");
            
            if(!s) {
                semantic_error(expr->var.var_name, expr->line);
            }
            // expr->data_type = s->type;
            return s->type;
        }
        
        case NODE_ARRAY_ACCESS: {
            Symbol *s = lookup_symbol(expr->array_access.array_name, current_function);
            if(!s) s = lookup_symbol(expr->array_access.array_name, "global");
            
            // Verifica se é array
            if(!s || !s->is_array) {
                fprintf(stderr, "ERRO SEMÂNTICO: '%s' não é array LINHA: %d\n",
                       expr->array_access.array_name, expr->line);
                exit(1);
            }
            
            // Verifica índice
            DataType index_type = check_expression(expr->array_access.index, current_function);
            if(index_type != INT_TYPE) {
                fprintf(stderr, "ERRO DE TIPO: Índice de array não inteiro LINHA: %d\n",
                       expr->line);
                exit(1);
            }
            
            // expr->data_type = s->type;
            return s->type;
        }
        
        case NODE_ASSIGN: {
            DataType lhs = check_expression(expr->assign.lhs, current_function);
            DataType rhs = check_expression(expr->assign.rhs, current_function);
            
            if(lhs != rhs) {
                fprintf(stderr, "ERRO DE TIPO: Atribuição inválida (esperado %d, recebido %d) LINHA: %d\n",
                       lhs, rhs, expr->line);
                exit(1);
            }
            // expr->data_type = lhs;
            return lhs;
        }
        
        case NODE_BINOP: {
            DataType left = check_expression(expr->binop.left, current_function);
            DataType right = check_expression(expr->binop.right, current_function);
            
            // Operações aritméticas
            if(expr->binop.op >= OP_ADD && expr->binop.op <= OP_DIV) {
                if(left != INT_TYPE || right != INT_TYPE) {
                    fprintf(stderr, "ERRO DE TIPO: Operação aritmética com tipos não inteiros LINHA: %d\n",
                           expr->line);
                    exit(1);
                }
                // expr->data_type = INT_TYPE;
                return INT_TYPE;
            }
            // Operações relacionais
            else if(expr->binop.op >= OP_LE && expr->binop.op <= OP_NE) {
                if(left != right) {
                    fprintf(stderr, "ERRO DE TIPO: Comparação entre tipos diferentes LINHA: %d\n",
                           expr->line);
                    exit(1);
                }
                // expr->data_type = INT_TYPE;
                return INT_TYPE; // Resultado booleano como inteiro
            }
            // break;
        }
        
        case NODE_FUN_CALL: {
            Symbol *fun = lookup_symbol(expr->fun_call.fun_name, "global");
            if(!fun) {
                semantic_error(expr->fun_call.fun_name, expr->line);
            }
            
            // Verifica parâmetros
            ASTNode *args = expr->fun_call.args;
            ASTNode *params = fun->fun_node->fun_decl.params; // Supondo que params estão armazenados no símbolo
            int arg_count = 0;
            
            while(args && params) {
                DataType arg_type = check_expression(args, current_function);
                if(arg_type != params->param.param_type) {
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
                       expr->fun_call.fun_name, expr->line);
                exit(1);
            }

            // expr->data_type = fun->type;
            
            return fun->type;
        }
        
        case NODE_IF_STMT: {
            DataType cond_type = check_expression(expr->if_stmt.condition, current_function);
            if(cond_type != INT_TYPE) {
                fprintf(stderr, "ERRO DE TIPO: Condição deve ser inteira LINHA: %d\n",
                       expr->line);
                exit(1);
            }
            check_expression(expr->if_stmt.then_stmt, current_function);
            if(expr->if_stmt.else_stmt) {
                check_expression(expr->if_stmt.else_stmt, current_function);
            }
            return VOID_TYPE;
        }
        
        case NODE_WHILE_STMT: {
            DataType cond_type = check_expression(expr->while_stmt.condition, current_function);
            if(cond_type != INT_TYPE) {
                fprintf(stderr, "ERRO DE TIPO: Condição deve ser inteira LINHA: %d\n", expr->line);
                exit(1);
            }
            check_expression(expr->while_stmt.body, current_function);
            return VOID_TYPE;
        }
        
        case NODE_RETURN_STMT: {
            if(expr->return_stmt.return_expr) {
                DataType return_type = check_expression(expr->return_stmt.return_expr, current_function);
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
    current_function = fun_decl->fun_decl.fun_name;
    enter_scope();
    
    // Insere parâmetros na tabela
    ASTNode *param = fun_decl->fun_decl.params;
    while(param != NULL && param->type == NODE_PARAM) {
        insert_symbol(
            param->param.param_name,
            param->param.param_type,
            param->param.is_array,
            current_function,
            param->line
        );
        param = param->next;
    }
    
    // check_expression(fun_decl->fun_decl.body, current_function);
    
    // Verifica corpo da função
    if(fun_decl->fun_decl.body && fun_decl->fun_decl.body->type == NODE_COMPOUND_STMT) {
        ASTNode *stmt = fun_decl->fun_decl.body->compound_stmt.statements;
        while(stmt) {
            check_expression(stmt, current_function);
            stmt = stmt->next;
        }
    }
    exit_scope();
    current_function = NULL;
}

void check_semantics(ASTNode *root) {
    init_symbol_table();
    ASTNode *decl = root->program.declarations;
    
    // Primeira passada: Insere Declarações Globais
    while(decl != NULL) {
        if(decl->type == NODE_FUN_DECL) {
            // Insere função com escopo GLOBAL
            insert_symbol(decl->fun_decl.fun_name, 
                        decl->fun_decl.return_type, 
                        0,  // Não é array
                        "global", 
                        decl->line);
            
            // Atualiza símbolo com referência à declaração da função
            Symbol *s = lookup_symbol(decl->fun_decl.fun_name, "global");
            if(s) {
                s->fun_node = decl;
            }
        }
        decl = decl->next;
    }
    
    // Segunda passada: Verificação das Funções
    decl = root->program.declarations;
    while(decl != NULL) {
        if(decl->type == NODE_FUN_DECL) {
            check_function_decl(decl);
        }
        decl = decl->next;
    }
    
    // Verificação EXPLÍCITA da main no escopo global
    Symbol *main_sym = lookup_symbol("main", "global");
    if(!main_sym) {
        fprintf(stderr, "ERRO SEMÂNTICO: Função 'main' não declarada\n");
        exit(1);
    }
    if(main_sym->type != INT_TYPE) {
        fprintf(stderr, "ERRO SEMÂNTICO: Função 'main' deve retornar int\n");
        exit(1);
    }
}