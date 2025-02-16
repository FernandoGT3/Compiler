#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h"
#include "../include/semant.h"
#include "../include/symtab.h"
#include "../include/codegen.h"
#include "../include/errors.h"
#include "../build/parser.tab.h"

extern FILE *yyin;
extern int yyparse();
extern ASTNode *root;

int main(int argc, char *argv[]) {
    // Verificação de argumentos
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    // Abrir arquivo de entrada
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    yyin = input_file;

    // Fase 1: Análise Sintática (Parser)
    printf("\n=== Iniciando Análise Sintática ===\n");
    yyparse();
    
    if (!root) {
        fprintf(stderr, "Erro: AST não foi gerada corretamente\n");
        fclose(input_file);
        return 1;
    }

    // Fase 2: Análise Semântica
    printf("\n=== Iniciando Análise Semântica ===\n");
    check_semantics(root);
    
    // Imprimir Tabela de Símbolos
    printf("\n=== Tabela de Símbolos ===\n");
    print_symbol_table();

    // Fase 3: Geração de Código Intermediário
    printf("\n=== Gerando Código Intermediário ===\n");
    TAC *code = generate_code(root);
    
    // Imprimir Árvore Sintática
    printf("\n=== Árvore Sintática Abstrata ===\n");
    ast_print(root, 0);

    // Imprimir Código de Três Endereços
    print_tac(code);

    // Liberar recursos
    fclose(input_file);
    ast_destroy(root);
    
    return 0;
}