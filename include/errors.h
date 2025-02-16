#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>

extern int line_num;  // Variável global definida no lexer.l/parser.y

// Macros para emitir erros e encerrar a compilação
#define LEXICAL_ERROR(lexema) \
    do { \
        fprintf(stderr, "ERRO LÉXICO: '%s' LINHA: %d\n", lexema, line_num); \
        exit(1); \
    } while(0)

#define SYNTAX_ERROR(token) \
    do { \
        fprintf(stderr, "ERRO SINTÁTICO: '%s' LINHA: %d\n", token, line_num); \
        exit(1); \
    } while(0)

#define SEMANTIC_ERROR(identificador) \
    do { \
        fprintf(stderr, "ERRO SEMÂNTICO: '%s' LINHA: %d\n", identificador, line_num); \
        exit(1); \
    } while(0)

#define SEMANTIC_MSG_ERROR(mensagem, identificador) \
    do { \
        fprintf(stderr, "ERRO SEMÂNTICO: %s '%s' LINHA: %d\n", mensagem, identificador, line_num); \
        exit(1); \
    } while(0)

#endif