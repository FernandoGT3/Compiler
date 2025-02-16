#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "types.h"

Scope *current_scope = NULL;

void init_symbol_table() {
    current_scope = (Scope*)malloc(sizeof(Scope));
    current_scope->parent = NULL;
    current_scope->symbols = NULL;
    
    // Insere funções built-in
    insert_symbol("input", INT_TYPE, 0, "global", 0);
    insert_symbol("output", VOID_TYPE, 0, "global", 0);
}

void enter_scope() {
    Scope *new_scope = (Scope*)malloc(sizeof(Scope));
    new_scope->parent = current_scope;
    new_scope->symbols = NULL;
    current_scope = new_scope;
}

void exit_scope() {
    if(current_scope->parent != NULL) {
        Scope *old = current_scope;
        current_scope = current_scope->parent;
        free(old);
    }
}

Symbol* lookup_symbol(const char *name, const char *scope) {
    Scope *scope_ptr = current_scope;
    while(scope_ptr != NULL) {
        Symbol *s = scope_ptr->symbols;
        while(s != NULL) {
            if(strcmp(s->name, name) == 0 && 
              (scope == NULL || strcmp(s->scope, scope) == 0)) {
                return s;
            }
            s = s->next;
        }
        scope_ptr = scope_ptr->parent;
    }
    return NULL;
}

void insert_symbol(const char *name, DataType type, int is_array, const char *scope, int line) {
    // Verifica se já existe no escopo atual
    Symbol *s = current_scope->symbols;
    while(s != NULL) {
        if(strcmp(s->name, name) == 0 && strcmp(s->scope, scope) == 0) {
            fprintf(stderr, "ERRO SEMÂNTICO: '%s' redeclarado LINHA: %d\n", name, line);
            exit(1);
        }
        s = s->next;
    }
    
    // Cria novo símbolo
    Symbol *new_sym = (Symbol*)malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->type = type;
    new_sym->is_array = is_array;
    new_sym->scope = scope ? strdup(scope) : "global";
    new_sym->line = line;
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
    int scope_level = 0;
    
    while(scope_ptr != NULL) {
        printf("\nEscopo Nível %d:\n", scope_level++);
        Symbol *s = scope_ptr->symbols;
        while(s != NULL) {
            printf("• Nome: %-15s Tipo: %-10s Array: %-3s Escopo: %-15s Linha: %d\n",
                   s->name,
                   s->type == INT_TYPE ? "int" : "void",
                   s->is_array ? "Sim" : "Não",
                   s->scope,
                   s->line);
            s = s->next;
        }
        scope_ptr = scope_ptr->parent;
    }
}