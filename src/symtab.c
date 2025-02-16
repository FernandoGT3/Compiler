#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/symtab.h"
#include "../include/types.h"

Scope *current_scope = NULL;

void init_symbol_table() {
    current_scope = (Scope*)malloc(sizeof(Scope));
    current_scope->parent = NULL;
    current_scope->symbols = NULL;
    
    // Insere funções built-in
    insert_symbol("input", INT_TYPE, 0, "global", 0);
    insert_symbol("output", VOID_TYPE, 0, "global", 0);

    // Força o escopo global como raiz
    while(current_scope->parent != NULL) {
        current_scope = current_scope->parent;
    }
}

void enter_scope() {
    Scope *new_scope = (Scope*)malloc(sizeof(Scope));
    new_scope->parent = current_scope;
    new_scope->symbols = NULL;
    current_scope = new_scope;
}

void exit_scope() {
    if(current_scope->parent != NULL) {
        Scope *old_scope = current_scope;
        current_scope = current_scope->parent;
        
        // Libera símbolos do escopo
        Symbol *sym = old_scope->symbols;
        while(sym) {
            Symbol *next = sym->next;
            free(sym->name);
            free(sym->scope);
            free(sym);
            sym = next;
        }
        free(old_scope);
    }
}

Symbol* lookup_symbol(const char *name, const char *scope) {
    Scope *scope_ptr = current_scope;
    
    // Busca específica no escopo global quando solicitado
    if(scope && strcmp(scope, "global") == 0) {
        // Navega até o escopo global
        while(scope_ptr->parent != NULL) {
            scope_ptr = scope_ptr->parent;
        }
        
        // Busca apenas no escopo global
        Symbol *s = scope_ptr->symbols;
        while(s != NULL) {
            if(strcmp(s->name, name) == 0) return s;
            s = s->next;
        }
        return NULL;
    }
    
    // Busca normal em todos os escopos
    while(scope_ptr != NULL) {
        Symbol *s = scope_ptr->symbols;
        while(s != NULL) {
            if(strcmp(s->name, name) == 0) return s;
            s = s->next;
        }
        scope_ptr = scope_ptr->parent;
    }
    return NULL;
}

void insert_symbol(const char *name, DataType type, int is_array, const char *scope, int line) {
    // Verifica se já existe no escopo atual
    Symbol *existing = lookup_current_scope(name);
    if(existing != NULL) {
        fprintf(stderr, "ERRO SEMÂNTICO: '%s' redeclarado LINHA: %d\n", name, line);
        exit(1);
    }
    
    // Cria novo símbolo
    Symbol *new_sym = (Symbol*)malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->type = type;
    new_sym->is_array = is_array;
    new_sym->scope = scope ? strdup(scope) : "global";
    new_sym->line = line;
    new_sym->fun_node = NULL;
    new_sym->next = current_scope->symbols;

    current_scope->symbols = new_sym;
}

Symbol* lookup_current_scope(const char *name) {
    Symbol *s = current_scope->symbols;
    while(s != NULL) {
        if(strcmp(s->name, name) == 0) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}

void print_symbol_table() {
    printf("\n=== TABELA DE SÍMBOLOS ===\n");
    Scope *scope_ptr = current_scope;
    int level = 0;
    
    while(scope_ptr != NULL) {
        printf("\nEscopo Nível %d\n", level++);
        printf("-----------------\n");
        
        Symbol *sym = scope_ptr->symbols;
        while(sym != NULL) {
            printf("Nome: %-15s Tipo: %-10s Array: %-3s Escopo: %-15s Linha: %d\n",
                   sym->name,
                   sym->type == INT_TYPE ? "int" : "void",
                   sym->is_array ? "Sim" : "Não",
                   sym->scope,
                   sym->line);
                   
            if(sym->fun_node != NULL) {
                printf("  Parâmetros: ");
                ASTNode *params = sym->fun_node->fun_decl.params;
                while(params != NULL) {
                    printf("%s %s%s ",
                           params->param.param_type == INT_TYPE ? "int" : "void",
                           params->param.param_name,
                           params->param.is_array ? "[]" : "");
                    params = params->next;
                }
                printf("\n");
            }
            
            sym = sym->next;
        }
        scope_ptr = scope_ptr->parent;
    }
}