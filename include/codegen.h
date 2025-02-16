#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

typedef struct TAC {
    char op[32];
    char arg1[32];
    char arg2[32];
    char result[32];
    struct TAC *prev;
    struct TAC *next;
} TAC;

TAC* generate_code(ASTNode *node);
void print_tac(TAC *code);

#endif