#ifndef SEMANT_H
#define SEMANT_H

#include "types.h"
#include "ast.h"
#include "symtab.h"

void semantic_error(const char *id, int line);
void check_semantics(ASTNode *root);
DataType check_expression(ASTNode *expr, const char *current_function);
void check_function_decl(ASTNode *fun_decl);

#endif