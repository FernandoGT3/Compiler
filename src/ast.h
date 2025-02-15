#ifndef AST_H
#define AST_H

typedef enum {
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
    NODE_TYPE
} NodeType;

typedef enum {
    INT_TYPE,
    VOID_TYPE
} VarType;

typedef struct ASTNode {
    NodeType type;
    int line;
    
    union {
        // Program
        struct {
            struct ASTNode *declarations;
        } program;
        
        // Variable declaration
        struct {
            VarType var_type;
            char *var_name;
            struct ASTNode *array_size;
        } var_decl;
        
        // Function declaration
        struct {
            VarType return_type;
            char *fun_name;
            struct ASTNode *params;
            struct ASTNode *body;
        } fun_decl;
        
        // Parameter
        struct {
            VarType param_type;
            char *param_name;
            int is_array;
        } param;
        
        // Statements
        struct {
            struct ASTNode *stmt_list;
        } compound_stmt;
        
        // Expressions
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            int op;
        } binop;
        
        struct {
            char *var_name;
        } variable;
        
        struct {
            struct ASTNode *expr;
        } return_stmt;
        
        struct {
            struct ASTNode *cond;
            struct ASTNode *then_stmt;
            struct ASTNode *else_stmt;
        } if_stmt;
        
        struct {
            struct ASTNode *cond;
            struct ASTNode *stmt;
        } while_stmt;
        
        struct {
            char *fun_name;
            struct ASTNode *args;
        } fun_call;
        
        int num_value;
    };
    
    struct ASTNode *next;
} ASTNode;

// Funções de construção da AST
ASTNode* ast_new_program(ASTNode *declarations);
ASTNode* ast_new_var_decl(VarType type, char *name, ASTNode *array_size);
ASTNode* ast_new_fun_decl(VarType return_type, char *name, ASTNode *params, ASTNode *body);
ASTNode* ast_new_param(VarType type, char *name, int is_array);
ASTNode* ast_new_compound_stmt(ASTNode *local_decls, ASTNode *stmt_list);
ASTNode* ast_new_expr_stmt(ASTNode *expr);
ASTNode* ast_new_if_stmt(ASTNode *cond, ASTNode *then_stmt, ASTNode *else_stmt);
ASTNode* ast_new_while_stmt(ASTNode *cond, ASTNode *stmt);
ASTNode* ast_new_return_stmt(ASTNode *expr);
ASTNode* ast_new_assign(ASTNode *lhs, ASTNode *rhs);
ASTNode* ast_new_binop(int op, ASTNode *left, ASTNode *right);
ASTNode* ast_new_variable(char *name);
ASTNode* ast_new_array_access(char *name, ASTNode *index);
ASTNode* ast_new_fun_call(char *name, ASTNode *args);
ASTNode* ast_new_num(int value);
ASTNode* ast_new_type(VarType type);

// Funções auxiliares
void ast_print(ASTNode *node, int level);
ASTNode* ast_append(ASTNode *list, ASTNode *node);

#endif