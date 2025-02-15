#include <stdio.h>
#include <stdlib.h>
#include "lexer.l"
#include "parser.tab.h"
#include "symtab.h"
#include "semant.h"
#include "codegen.h"
#include "ast.h"
#include "errors.h"

// Variáveis globais
extern int line_num;
extern FILE *yyin;
extern ASTNode *root;

// Protótipos
void print_ast(ASTNode *node);
void free_ast(ASTNode *node);
void free_symbol_table();

int main(int argc, char *argv[]) {
    // Verificação de argumentos
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada.c->\n", argv[0]);
        return 1;
    }

    // Abrir arquivo de entrada
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }

    // Inicialização
    init_symbol_table();
    
    // Fase 1: Análise Léxica e Sintática
    printf("\n=== Iniciando Análise Léxica/Sintática ===\n");
    yyparse();
    
    // Fase 2: Análise Semântica
    printf("\n=== Iniciando Análise Semântica ===\n");
    check_semantics(root);
    
    // Fase 3: Geração de Código
    printf("\n=== Iniciando Geração de Código ===\n");
    TAC *tac_code = generate_code(root);
    
    // Saídas obrigatórias
    printf("\n=== Resultados da Compilação ===\n");
    
    // 1. Tabela de Símbolos
    print_symbol_table();
    
    // 2. Árvore Sintática
    printf("\n=== Árvore Sintática Abstrata (AST) ===\n");
    ast_print(root, 0);
    
    // 3. Código Intermediário
    print_tac(tac_code);
    
    // Liberação de recursos
    fclose(yyin);
    free_ast(root);
    free_symbol_table();
    
    printf("\nCompilação concluída com sucesso!\n");
    return 0;
}

// Implementação de funções auxiliares
void print_ast(ASTNode *node) {
    // Função já implementada em ast.c
    ast_print(node, 0);
}

void free_ast(ASTNode *node) {
    // Função recursiva para liberar memória da AST
    if (!node) return;
    
    switch(node->type) {
        case NODE_VAR:
            free(node->var_name);
            break;
            
        case NODE_FUN_DECL:
            free(node->fun_name);
            free_ast(node->fun_params);
            free_ast(node->fun_body);
            break;
            
        // Adicionar casos para outros tipos de nós
        
        default:
            if (node->next) free_ast(node->next);
            break;
    }
    free(node);
}

void free_ast(ASTNode *node) {
    if (!node) return;

    switch(node->type) {
        case NODE_VAR:
            free(node->var_name);
            break;

        case NODE_NUM:
            // Números não têm alocação dinâmica
            break;

        case NODE_ASSIGN:
            free_ast(node->assign_lhs);
            free_ast(node->assign_rhs);
            break;

        case NODE_BINOP:
            free_ast(node->binop_left);
            free_ast(node->binop_right);
            break;

        case NODE_FUN_DECL:
            free(node->fun_name);
            free_ast(node->fun_params);
            free_ast(node->fun_body);
            break;

        case NODE_FUN_CALL:
            free(node->fun_call_name);
            free_ast(node->fun_call_args);
            break;

        case NODE_IF:
            free_ast(node->cond_expr);
            free_ast(node->then_stmt);
            free_ast(node->else_stmt);
            break;

        case NODE_WHILE:
            free_ast(node->cond_expr);
            free_ast(node->loop_body);
            break;

        case NODE_RETURN:
            free_ast(node->return_expr);
            break;

        case NODE_COMPOUND_STMT:
            free_ast(node->compound_local_decls);
            free_ast(node->compound_stmt_list);
            break;

        case NODE_ARRAY_ACCESS:
            free(node->array_name);
            free_ast(node->array_index);
            break;

        case NODE_PARAM:
            free(node->param_name);
            break;

        case NODE_TYPE:
            // Tipo não tem alocação dinâmica
            break;

        case NODE_PROGRAM:
            free_ast(node->program_decls);
            break;

        case NODE_DECL_LIST:
        case NODE_STMT_LIST:
        case NODE_PARAM_LIST:
        case NODE_ARG_LIST:
        case NODE_LOCAL_DECLS:
            // Listas: liberar o nó atual e o próximo
            free_ast(node->next);
            break;

        default:
            fprintf(stderr, "ERRO: Tipo de nó AST desconhecido ao liberar memória\n");
            break;
    }

    // Liberar o nó atual
    free(node);
}

void free_symbol_table() {
    // Função para liberar memória da tabela de símbolos
    Scope *scope = current_scope;
    while (scope) {
        Symbol *s = scope->symbols;
        while (s) {
            Symbol *temp = s;
            s = s->next;
            free(temp->name);
            free(temp->scope);
            free(temp);
        }
        Scope *old_scope = scope;
        scope = scope->parent;
        free(old_scope);
    }
}