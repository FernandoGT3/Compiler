%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symtab.h"
#include "errors.h"

extern int line_num;
extern int yylex();
extern FILE *yyin;
void yyerror(const char *s);

// Variável global para a raiz da AST
ASTNode *root = NULL;

%}

%union {
    int num;
    char *string;
    ASTNode *node;
}

%expect 1 // Conflito esperado (dangling else)

// Tokens
%token <string> ID
%token <num> NUM

%token ELSE IF INT RETURN VOID WHILE
%token ADD SUB MUL DIV LE LT GE GT EQ NE
%token ATTR SEMI COMMA LBRACE RBRACE LBRACKET RBRACKET LPAREN RPAREN

// Precedência (da menor para a maior)
%right ATTR          // Atribuição (=)
%left EQ NE          // ==, !=
%left LT LE GT GE    // <, <=, >, >=
%left ADD SUB        // +, -
%left MUL DIV        // *, /
%right UMINUS        // Operador unário -

%type <node> program declaration_list declaration var_declaration
%type <node> type_specifier fun_declaration params param_list param
%type <node> compound_decl local_declarations statement_list statement
%type <node> expression_decl selection_decl iteration_decl return_decl
%type <node> expression var simple_expression relop additive_expression
%type <node> sum term mult factor activation args arg_list

%start program

%%

program:
    declaration_list {
        $$ = ast_new_program($1);
        root = $$;
    }
;

declaration_list:
    declaration_list declaration {
        $$ = ast_append_declaration($1, $2);
    }
|   declaration {
        $$ = ast_new_declaration_list($1);
    }
;

declaration:
    var_declaration {
        $$ = $1;
    }
|   fun_declaration {
        $$ = $1;
    }
;

var_declaration:
    type_specifier ID SEMI {
        $$ = ast_new_var_decl($1, $2, NULL);
    }
|   type_specifier ID LBRACKET NUM RBRACKET SEMI {
        $$ = ast_new_var_decl($1, $2, ast_new_num($4));
    }
;

type_specifier:
    INT {
        $$ = ast_new_type(INT_TYPE);
    }
|   VOID {
        $$ = ast_new_type(VOID_TYPE);
    }
;

fun_declaration:
    type_specifier ID LPAREN params RPAREN compound_decl {
        $$ = ast_new_fun_decl($1, $2, $4, $6);
    }
;

params:
    param_list {
        $$ = $1;
    }
|   VOID {
        $$ = ast_new_param_list(NULL);
    }
;

param_list:
    param_list COMMA param {
        $$ = ast_append_param($1, $3);
    }
|   param {
        $$ = ast_new_param_list($1);
    }
;

param:
    type_specifier ID {
        $$ = ast_new_param($1, $2, 0);
    }
|   type_specifier ID LBRACKET RBRACKET {
        $$ = ast_new_param($1, $2, 1);
    }
;

compound_decl:
    LBRACE local_declarations statement_list RBRACE {
        $$ = ast_new_compound_stmt($2, $3);
    }
;

local_declarations:
    local_declarations var_declaration {
        $$ = ast_append_local_decl($1, $2);
    }
|   /* empty */ {
        $$ = NULL;
    }
;

statement_list:
    statement_list statement {
        $$ = ast_append_stmt($1, $2);
    }
|   /* empty */ {
        $$ = NULL;
    }
;

statement:
    expression_decl {
        $$ = $1;
    }
|   compound_decl {
        $$ = $1;
    }
|   selection_decl {
        $$ = $1;
    }
|   iteration_decl {
        $$ = $1;
    }
|   return_decl {
        $$ = $1;
    }
;

expression_decl:
    expression SEMI {
        $$ = ast_new_expr_stmt($1);
    }
|   SEMI {
        $$ = ast_new_empty_stmt();
    }
;

selection_decl:
    IF LPAREN expression RPAREN statement {
        $$ = ast_new_if_stmt($3, $5, NULL);
    }
|   IF LPAREN expression RPAREN statement ELSE statement {
        $$ = ast_new_if_stmt($3, $5, $7);
    }
;

iteration_decl:
    WHILE LPAREN expression RPAREN statement {
        $$ = ast_new_while_stmt($3, $5);
    }
;

return_decl:
    RETURN SEMI {
        $$ = ast_new_return_stmt(NULL);
    }
|   RETURN expression SEMI {
        $$ = ast_new_return_stmt($2);
    }
;

expression:
    var ATTR expression {
        $$ = ast_new_assign($1, $3);
    }
|   simple_expression {
        $$ = $1;
    }
;

var:
    ID {
        $$ = ast_new_variable($1);
    }
|   ID LBRACKET expression RBRACKET {
        $$ = ast_new_array_access($1, $3);
    }
;

simple_expression:
    additive_expression relop additive_expression {
        $$ = ast_new_binop($2, $1, $3);
    }
|   additive_expression {
        $$ = $1;
    }
;

relop:
    LE { $$ = LE; }
|   LT { $$ = LT; }
|   GT { $$ = GT; }
|   GE { $$ = GE; }
|   EQ { $$ = EQ; }
|   NE { $$ = NE; }
;

additive_expression:
    additive_expression sum term {
        $$ = ast_new_binop($2, $1, $3);
    }
|   term {
        $$ = $1;
    }
;

sum:
    ADD { $$ = ADD; }
|   SUB { $$ = SUB; }
;

term:
    term mult factor {
        $$ = ast_new_binop($2, $1, $3);
    }
|   factor {
        $$ = $1;
    }
;

mult:
    MUL { $$ = MUL; }
|   DIV { $$ = DIV; }
;

factor:
    LPAREN expression RPAREN {
        $$ = $2;
    }
|   var {
        $$ = $1;
    }
|   activation {
        $$ = $1;
    }
|   NUM {
        $$ = ast_new_num($1);
    }
;

activation:
    ID LPAREN args RPAREN {
        $$ = ast_new_fun_call($1, $3);
    }
;

args:
    arg_list {
        $$ = $1;
    }
|   /* empty */ {
        $$ = NULL;
    }
;

arg_list:
    arg_list COMMA expression {
        $$ = ast_append_arg($1, $3);
    }
|   expression {
        $$ = ast_new_arg_list($1);
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "ERRO SINTÁTICO: %s LINHA: %d\n", s, line_num);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    yyparse();
    
    // Imprime a AST após parsing bem-sucedido
    ast_print(root, 0);
    
    fclose(yyin);
    return 0;
}