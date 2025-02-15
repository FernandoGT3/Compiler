#ifndef SYMTAB_H
#define SYMTAB_H

typedef enum { INT_TYPE, VOID_TYPE, ERROR_TYPE } TypeKind;

typedef struct Symbol {
    char *name;
    TypeKind type;
    int is_array;
    char *scope; // Nome da função ou "global"
    int line;    // Linha da declaração
    struct Symbol *next;
} Symbol;

typedef struct Scope {
    struct Scope *parent;
    Symbol *symbols;
} Scope;

// Funções da tabela de símbolos
void init_symbol_table();
void enter_scope();
void exit_scope();
Symbol* lookup_symbol(const char *name, const char *scope);
Symbol* lookup_current_scope(const char *name);
void insert_symbol(const char *name, TypeKind type, int is_array, const char *scope, int line);
void print_symbol_table();

// Escopo atual
extern Scope *current_scope;

#endif