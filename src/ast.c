#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static const char* node_type_names[] = {
    "Program", "VarDecl", "FunDecl", "Param", "CompoundStmt",
    "ExprStmt", "IfStmt", "WhileStmt", "ReturnStmt", "Assign",
    "BinOp", "Var", "ArrayAccess", "FunCall", "Num", "Type"
};

static const char* var_type_names[] = {
    "int", "void"
};

static const char* op_names[] = {
    "+", "-", "*", "/", "<", "<=", ">", ">=", "==", "!="
};

ASTNode* ast_new_node(NodeType type, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->line = line;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_program(ASTNode *declarations) {
    ASTNode *node = ast_new_node(NODE_PROGRAM, 0);
    node->program.declarations = declarations;
    return node;
}

ASTNode* ast_new_var_decl(VarType type, char *name, ASTNode *array_size) {
    ASTNode *node = ast_new_node(NODE_VAR_DECL, line_num);
    node->var_decl.var_type = type;
    node->var_decl.var_name = strdup(name);
    node->var_decl.array_size = array_size;
    return node;
}

ASTNode* ast_new_fun_decl(VarType return_type, char *name, ASTNode *params, ASTNode *body) {
    ASTNode *node = ast_new_node(NODE_FUN_DECL, line_num);
    node->fun_decl.return_type = return_type;
    node->fun_decl.fun_name = strdup(name);
    node->fun_decl.params = params;
    node->fun_decl.body = body;
    return node;
}

ASTNode* ast_new_param(VarType type, char *name, int is_array) {
    ASTNode *node = ast_new_node(NODE_PARAM, line_num);
    node->param.param_type = type;
    node->param.param_name = strdup(name);
    node->param.is_array = is_array;
    return node;
}

ASTNode* ast_new_compound_stmt(ASTNode *local_decls, ASTNode *stmt_list) {
    ASTNode *node = ast_new_node(NODE_COMPOUND_STMT, line_num);
    node->compound_stmt.stmt_list = stmt_list;
    return node;
}

ASTNode* ast_new_expr_stmt(ASTNode *expr) {
    ASTNode *node = ast_new_node(NODE_EXPR_STMT, line_num);
    node->expr = expr;
    return node;
}

ASTNode* ast_new_if_stmt(ASTNode *cond, ASTNode *then_stmt, ASTNode *else_stmt) {
    ASTNode *node = ast_new_node(NODE_IF_STMT, line_num);
    node->if_stmt.cond = cond;
    node->if_stmt.then_stmt = then_stmt;
    node->if_stmt.else_stmt = else_stmt;
    return node;
}

ASTNode* ast_new_while_stmt(ASTNode *cond, ASTNode *stmt) {
    ASTNode *node = ast_new_node(NODE_WHILE_STMT, line_num);
    node->while_stmt.cond = cond;
    node->while_stmt.stmt = stmt;
    return node;
}

ASTNode* ast_new_return_stmt(ASTNode *expr) {
    ASTNode *node = ast_new_node(NODE_RETURN_STMT, line_num);
    node->return_stmt.expr = expr;
    return node;
}

ASTNode* ast_new_assign(ASTNode *lhs, ASTNode *rhs) {
    ASTNode *node = ast_new_node(NODE_ASSIGN, line_num);
    node->assign.left = lhs;
    node->assign.right = rhs;
    return node;
}

ASTNode* ast_new_binop(int op, ASTNode *left, ASTNode *right) {
    ASTNode *node = ast_new_node(NODE_BINOP, line_num);
    node->binop.op = op;
    node->binop.left = left;
    node->binop.right = right;
    return node;
}

ASTNode* ast_new_variable(char *name) {
    ASTNode *node = ast_new_node(NODE_VAR, line_num);
    node->variable.var_name = strdup(name);
    return node;
}

ASTNode* ast_new_array_access(char *name, ASTNode *index) {
    ASTNode *node = ast_new_node(NODE_ARRAY_ACCESS, line_num);
    node->array_access.array_name = strdup(name);
    node->array_access.index = index;
    return node;
}

ASTNode* ast_new_fun_call(char *name, ASTNode *args) {
    ASTNode *node = ast_new_node(NODE_FUN_CALL, line_num);
    node->fun_call.fun_name = strdup(name);
    node->fun_call.args = args;
    return node;
}

ASTNode* ast_new_num(int value) {
    ASTNode *node = ast_new_node(NODE_NUM, line_num);
    node->num_value = value;
    return node;
}

ASTNode* ast_new_type(VarType type) {
    ASTNode *node = ast_new_node(NODE_TYPE, line_num);
    node->var_type = type;
    return node;
}

ASTNode* ast_append(ASTNode *list, ASTNode *node) {
    if (!list) return node;
    
    ASTNode *current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
    return list;
}

void ast_print(ASTNode *node, int level) {
    if (!node) return;
    
    for (int i = 0; i < level; i++) printf("  ");
    
    printf("[%s] Line: %d", node_type_names[node->type], node->line);
    
    switch (node->type) {
        case NODE_VAR_DECL:
            printf(" - Type: %s, Name: %s", 
                   var_type_names[node->var_decl.var_type],
                   node->var_decl.var_name);
            if (node->var_decl.array_size) {
                printf(", Array Size: ");
                ast_print(node->var_decl.array_size, 0);
            }
            break;
            
        case NODE_FUN_DECL:
            printf(" - Return: %s, Name: %s",
                   var_type_names[node->fun_decl.return_type],
                   node->fun_decl.fun_name);
            break;
            
        case NODE_BINOP:
            printf(" - Op: %s", op_names[node->binop.op]);
            break;
            
        case NODE_VAR:
            printf(" - Name: %s", node->variable.var_name);
            break;
            
        case NODE_NUM:
            printf(" - Value: %d", node->num_value);
            break;
            
        default:
            break;
    }
    
    printf("\n");
    
    // Recursão para elementos filhos
    switch (node->type) {
        case NODE_PROGRAM:
            ast_print(node->program.declarations, level + 1);
            break;
            
        case NODE_FUN_DECL:
            ast_print(node->fun_decl.params, level + 1);
            ast_print(node->fun_decl.body, level + 1);
            break;
            
        case NODE_COMPOUND_STMT:
            ast_print(node->compound_stmt.stmt_list, level + 1);
            break;
            
        case NODE_IF_STMT:
            ast_print(node->if_stmt.cond, level + 1);
            ast_print(node->if_stmt.then_stmt, level + 1);
            ast_print(node->if_stmt.else_stmt, level + 1);
            break;
            
        case NODE_BINOP:
            ast_print(node->binop.left, level + 1);
            ast_print(node->binop.right, level + 1);
            break;
            
        default:
            ast_print(node->next, level);
            break;
    }
}