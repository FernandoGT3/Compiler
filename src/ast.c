#include "../include/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Protótipos de funções auxiliares locais
static void print_indent(int level);
static void print_binop_operator(int op);

// =============================================
// Funções de Criação de Nós
// =============================================

ASTNode* ast_new_program(ASTNode *declarations) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->line = 0;
    node->program.declarations = declarations;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_var_decl(DataType type, char *name, ASTNode *array_size) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR_DECL;
    node->line = 0;
    node->var_decl.var_type = type;
    node->var_decl.var_name = strdup(name);
    node->var_decl.array_size = array_size;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_fun_decl(DataType return_type, char *name, ASTNode *params, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FUN_DECL;
    node->line = 0;
    node->fun_decl.return_type = return_type;
    node->fun_decl.fun_name = name ? strdup(name) : NULL;
    node->fun_decl.params = params;
    node->fun_decl.body = body;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_param(DataType type, char *name, int is_array) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->line = 0;
    node->param.param_type = type;
    node->param.param_name = strdup(name);
    node->param.is_array = is_array;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_compound_stmt(ASTNode *local_decls, ASTNode *statements) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_COMPOUND_STMT;
    node->line = 0;
    node->compound_stmt.local_decls = local_decls;
    node->compound_stmt.statements = statements;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_expr_stmt(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_STMT;
    node->line = 0;
    node->expr_stmt.expr = expr;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_if_stmt(ASTNode *condition, ASTNode *then_stmt, ASTNode *else_stmt) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_IF_STMT;
    node->line = 0;
    node->if_stmt.condition = condition;
    node->if_stmt.then_stmt = then_stmt;
    node->if_stmt.else_stmt = else_stmt;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_while_stmt(ASTNode *condition, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_WHILE_STMT;
    node->line = 0;
    node->while_stmt.condition = condition;
    node->while_stmt.body = body;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_return_stmt(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN_STMT;
    node->line = 0;
    node->return_stmt.return_expr = expr;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_assign(ASTNode *lhs, ASTNode *rhs) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->line = 0;
    node->assign.lhs = lhs;
    node->assign.rhs = rhs;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_binop(int op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->line = 0;
    node->binop.op = op;
    node->binop.left = left;
    node->binop.right = right;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_variable(char *name) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->line = 0;
    node->var.var_name = strdup(name);
    node->next = NULL;
    return node;
}

ASTNode* ast_new_array_access(char *name, ASTNode *index) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->line = 0;
    node->array_access.array_name = strdup(name);
    node->array_access.index = index;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_fun_call(char *name, ASTNode *args) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FUN_CALL;
    node->line = 0;
    node->fun_call.fun_name = strdup(name);
    node->fun_call.args = args;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_num(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->line = 0;
    node->num.value = value;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_type(DataType type) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_TYPE;
    node->line = 0;
    node->var_decl.var_type = type;
    node->next = NULL;
    return node;
}

ASTNode* ast_new_empty_stmt() {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_EMPTY;
    node->line = 0;
    node->next = NULL;
    return node;
}

// =============================================
// Funções Utilitárias
// =============================================

void ast_print(ASTNode *node, int indent) {
    if (!node) return;

    print_indent(indent);
    
    switch (node->type) {
        case NODE_PROGRAM:
            printf("Program\n");
            ast_print(node->program.declarations, indent + 1);
            break;
            
        case NODE_VAR_DECL: {
            char *type = (node->var_decl.var_type == INT_TYPE) ? "int" : "void";
            printf("VarDecl(%s %s", type, node->var_decl.var_name);
            if (node->var_decl.array_size) {
                printf("[");
                ast_print(node->var_decl.array_size, 0);
                printf("]");
            }
            printf(")\n");
            break;
        }
        
        case NODE_FUN_DECL: {
            char *type = (node->fun_decl.return_type == INT_TYPE) ? "int" : "void";
            printf("FunDecl(%s %s)\n", type, node->fun_decl.fun_name);
            ast_print(node->fun_decl.params, indent + 1);
            ast_print(node->fun_decl.body, indent + 1);
            break;
        }
        
        case NODE_PARAM: {
            char *type = (node->param.param_type == INT_TYPE) ? "int" : "void";
            printf("Param(%s %s%s)\n", type, node->param.param_name, 
                   node->param.is_array ? "[]" : "");
            break;
        }
        
        case NODE_COMPOUND_STMT:
            printf("CompoundStmt\n");
            ast_print(node->compound_stmt.local_decls, indent + 1);
            ast_print(node->compound_stmt.statements, indent + 1);
            break;
            
        case NODE_EXPR_STMT:
            printf("ExprStmt\n");
            ast_print(node->expr_stmt.expr, indent + 1);
            break;
            
        case NODE_IF_STMT:
            printf("IfStmt\n");
            print_indent(indent + 1); printf("Condition:\n");
            ast_print(node->if_stmt.condition, indent + 2);
            print_indent(indent + 1); printf("Then:\n");
            ast_print(node->if_stmt.then_stmt, indent + 2);
            if (node->if_stmt.else_stmt) {
                print_indent(indent + 1); printf("Else:\n");
                ast_print(node->if_stmt.else_stmt, indent + 2);
            }
            break;
            
        case NODE_WHILE_STMT:
            printf("WhileStmt\n");
            print_indent(indent + 1); printf("Condition:\n");
            ast_print(node->while_stmt.condition, indent + 2);
            print_indent(indent + 1); printf("Body:\n");
            ast_print(node->while_stmt.body, indent + 2);
            break;
            
        case NODE_RETURN_STMT:
            printf("ReturnStmt\n");
            ast_print(node->return_stmt.return_expr, indent + 1);
            break;
            
        case NODE_ASSIGN:
            printf("Assign\n");
            ast_print(node->assign.lhs, indent + 1);
            ast_print(node->assign.rhs, indent + 1);
            break;
            
        case NODE_BINOP:
            printf("BinOp(");
            print_binop_operator(node->binop.op);
            printf(")\n");
            ast_print(node->binop.left, indent + 1);
            ast_print(node->binop.right, indent + 1);
            break;
            
        case NODE_VAR:
            printf("Var(%s)\n", node->var.var_name);
            break;
            
        case NODE_ARRAY_ACCESS:
            printf("ArrayAccess(%s)\n", node->array_access.array_name);
            ast_print(node->array_access.index, indent + 1);
            break;
            
        case NODE_FUN_CALL:
            printf("FunCall(%s)\n", node->fun_call.fun_name);
            ast_print(node->fun_call.args, indent + 1);
            break;
            
        case NODE_NUM:
            printf("Num(%d)\n", node->num.value);
            break;

        case NODE_TYPE:
            printf("Type(%s)\n", node->var_decl.var_type == INT_TYPE ? "int" : "void");
            break;

        case NODE_DECL_LIST:
            printf("DeclarationList\n");
            ast_print(node->next, indent);
            break;

        case NODE_PARAM_LIST:
            printf("ParamList\n");
            ast_print(node->next, indent + 1);
            break;

        case NODE_ARG_LIST:
            printf("ArgList\n");
            ast_print(node->next, indent + 1);
            break;

        case NODE_EMPTY:
            printf("EmptyStmt\n");
            break;
            
        default:
            printf("UnknownNode\n");
    }

    // Processa nós seguintes na lista
    ast_print(node->next, indent);
}

void ast_destroy(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_VAR_DECL:
            free(node->var_decl.var_name);
            ast_destroy(node->var_decl.array_size);
            break;
            
        case NODE_FUN_DECL:
            free(node->fun_decl.fun_name);
            ast_destroy(node->fun_decl.params);
            ast_destroy(node->fun_decl.body);
            break;
            
        case NODE_PARAM:
            free(node->param.param_name);
            break;
            
        case NODE_VAR:
            free(node->var.var_name);
            break;
            
        case NODE_ARRAY_ACCESS:
            free(node->array_access.array_name);
            ast_destroy(node->array_access.index);
            break;
            
        case NODE_FUN_CALL:
            free(node->fun_call.fun_name);
            ast_destroy(node->fun_call.args);
            break;
            
        case NODE_ASSIGN:
            ast_destroy(node->assign.lhs);
            ast_destroy(node->assign.rhs);
            break;
            
        case NODE_BINOP:
            ast_destroy(node->binop.left);
            ast_destroy(node->binop.right);
            break;
            
        case NODE_IF_STMT:
            ast_destroy(node->if_stmt.condition);
            ast_destroy(node->if_stmt.then_stmt);
            ast_destroy(node->if_stmt.else_stmt);
            break;
            
        case NODE_WHILE_STMT:
            ast_destroy(node->while_stmt.condition);
            ast_destroy(node->while_stmt.body);
            break;
            
        case NODE_RETURN_STMT:
            ast_destroy(node->return_stmt.return_expr);
            break;
            
        case NODE_COMPOUND_STMT:
            ast_destroy(node->compound_stmt.local_decls);
            ast_destroy(node->compound_stmt.statements);
            break;
            
        case NODE_EXPR_STMT:
            ast_destroy(node->expr_stmt.expr);
            break;
            
        default:
            break;
    }

    ast_destroy(node->next);
    free(node);
}

// =============================================
// Funções de Manipulação de Listas
// =============================================

ASTNode* ast_new_declaration_list(ASTNode *declaration) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_DECL_LIST;
    node->program.declarations = declaration;
    node->next = NULL;
    return node;
}

ASTNode* ast_append_declaration(ASTNode *list, ASTNode *decl) {
    if (!list) return decl;
    
    ASTNode *current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = decl;
    return list;
}

ASTNode* ast_new_param_list(ASTNode *first_param) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM_LIST;
    node->fun_decl.params = first_param;
    node->next = NULL;
    return node;
}

ASTNode* ast_append_param(ASTNode *list, ASTNode *param) {
    return ast_append_declaration(list, param);
}

ASTNode* ast_append_local_decl(ASTNode *list, ASTNode *decl) {
    return ast_append_declaration(list, decl);
}

ASTNode* ast_append_stmt(ASTNode *list, ASTNode *stmt) {
    return ast_append_declaration(list, stmt);
}

ASTNode* ast_new_arg_list(ASTNode *first_arg) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ARG_LIST;
    node->fun_call.args = first_arg;
    node->next = NULL;
    return node;
}

ASTNode* ast_append_arg(ASTNode *list, ASTNode *arg) {
    return ast_append_declaration(list, arg);
}
// =============================================
// Funções Auxiliares Locais
// =============================================

static void print_indent(int level) {
    for (int i = 0; i < level; i++) printf("  ");
}

static void print_binop_operator(int op) {
    switch (op) {
        case OP_ADD: printf("+"); break;
        case OP_SUB: printf("-"); break;
        case OP_MUL: printf("*"); break;
        case OP_DIV: printf("/"); break;
        case OP_LT:  printf("<"); break;
        case OP_LE:  printf("<="); break;
        case OP_GT:  printf(">"); break;
        case OP_GE:  printf(">="); break;
        case OP_EQ:  printf("=="); break;
        case OP_NE:  printf("!="); break;
        case OP_AND: printf("&&"); break;
        case OP_OR:  printf("||"); break;
        default:     printf("?");
    }
}