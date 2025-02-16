#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

typedef enum {
    // Tipos de nós
    NODE_PROGRAM,
    NODE_VAR_DECL,
    NODE_FUN_DECL,
    NODE_PARAM,
    NODE_COMPOUND_STMT,
    NODE_EXPR_STMT,
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_RETURN_STMT,
    NODE_ASSIGN,
    NODE_BINOP,
    NODE_VAR,
    NODE_ARRAY_ACCESS,
    NODE_FUN_CALL,
    NODE_NUM,
    NODE_TYPE,
    NODE_DECL_LIST,
    NODE_PARAM_LIST,
    NODE_ARG_LIST,
    NODE_EMPTY
} NodeType;

typedef struct ASTNode ASTNode;

// Estrutura principal da AST
struct ASTNode {
    NodeType type;
    DataType data_type;  // Tipo de dado associado ao nó
    int line;  // Número da linha no código fonte
    
    // Campos específicos para cada tipo de nó
    union {
        // Programa (lista de declarações)
        struct {
            ASTNode *declarations;
        } program;
        
        // Declaração de variável
        struct {
            DataType var_type;
            char *var_name;
            ASTNode *array_size;  // NULL se não for array
        } var_decl;
        
        // Declaração de função
        struct {
            DataType return_type;
            char *fun_name;
            ASTNode *params;
            ASTNode *body;
        } fun_decl;
        
        // Parâmetro de função
        struct {
            DataType param_type;
            char *param_name;
            int is_array;
        } param;
        
        // Bloco de código composto
        struct {
            ASTNode *local_decls;
            ASTNode *statements;
        } compound_stmt;
        
        // Expressão
        struct {
            ASTNode *expr;
        } expr_stmt;
        
        // Comando if
        struct {
            ASTNode *condition;
            ASTNode *then_stmt;
            ASTNode *else_stmt;  // NULL se não houver else
        } if_stmt;
        
        // Comando while
        struct {
            ASTNode *condition;
            ASTNode *body;
        } while_stmt;
        
        // Comando return
        struct {
            ASTNode *return_expr;  // NULL se não houver expressão
        } return_stmt;
        
        // Atribuição
        struct {
            ASTNode *lhs;
            ASTNode *rhs;
        } assign;
        
        // Operação binária
        struct {
            int op;
            ASTNode *left;
            ASTNode *right;
        } binop;
        
        // Variável simples
        struct {
            char *var_name;
        } var;
        
        // Acesso a array
        struct {
            char *array_name;
            ASTNode *index;
        } array_access;
        
        // Chamada de função
        struct {
            char *fun_name;
            ASTNode *args;
        } fun_call;
        
        // Literal numérico
        struct {
            int value;
        } num;
    };
    
    ASTNode *next;  // Para listas (declarações, parâmetros, etc.)
};

// Operadores binários (deve corresponder aos tokens do Bison)
typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV,
    OP_LT, OP_LE, OP_GT, OP_GE, OP_EQ, OP_NE,
    OP_AND, OP_OR
} BinopOperator;

// Protótipos das funções de construção da AST
ASTNode* ast_new_program(ASTNode *declarations);
ASTNode* ast_new_var_decl(DataType type, char *name, ASTNode *array_size);
ASTNode* ast_new_fun_decl(DataType return_type, char *name, ASTNode *params, ASTNode *body);
ASTNode* ast_new_param(DataType type, char *name, int is_array);
ASTNode* ast_new_compound_stmt(ASTNode *local_decls, ASTNode *statements);
ASTNode* ast_new_expr_stmt(ASTNode *expr);
ASTNode* ast_new_if_stmt(ASTNode *condition, ASTNode *then_stmt, ASTNode *else_stmt);
ASTNode* ast_new_while_stmt(ASTNode *condition, ASTNode *body);
ASTNode* ast_new_return_stmt(ASTNode *expr);
ASTNode* ast_new_assign(ASTNode *lhs, ASTNode *rhs);
ASTNode* ast_new_binop(int op, ASTNode *left, ASTNode *right);
ASTNode* ast_new_variable(char *name);
ASTNode* ast_new_array_access(char *name, ASTNode *index);
ASTNode* ast_new_fun_call(char *name, ASTNode *args);
ASTNode* ast_new_num(int value);
ASTNode* ast_new_type(DataType type);
ASTNode* ast_new_empty();

// Funções utilitárias
void ast_print(ASTNode *node, int indent);
void ast_destroy(ASTNode *node);

// Funções para manipulação de listas
ASTNode* ast_append_declaration(ASTNode *list, ASTNode *decl);
ASTNode* ast_append_param(ASTNode *list, ASTNode *param);
ASTNode* ast_append_stmt(ASTNode *list, ASTNode *stmt);
ASTNode* ast_append_arg(ASTNode *list, ASTNode *arg);

ASTNode* ast_new_declaration_list(ASTNode *decl);
ASTNode* ast_new_param_list(ASTNode *param);
ASTNode* ast_append_local_decl(ASTNode *list, ASTNode *decl);
ASTNode* ast_new_empty_stmt();
ASTNode* ast_new_arg_list(ASTNode *arg);

#endif