%{
#include <stdio.h>
#include "../build/parser.tab.h" // Arquivo gerado pelo Bison
#include "../include/errors.h"

int line_num = 1;        // Contador de linhas para erros
%}

%x COMMENT

LETRA   [a-zA-Z]
DIGITO  [0-9]
ID      {LETRA}({LETRA}|{DIGITO})*
NUM     {DIGITO}+
ESPACO  [ \t\r]

%%

"else"         { return ELSE; }
"if"           { return IF; }
"int"          { return INT; }
"return"       { return RETURN; }
"void"         { return VOID; }
"while"        { return WHILE; }

"+"            { return ADD; }
"-"            { return SUB; }
"*"            { return MUL; }
"/"            { return DIV; }
"<="           { return LE; }
"<"            { return LT; }
">="           { return GE; }
">"            { return GT; }
"=="           { return EQ; }
"!="           { return NE; }
"="            { return ATTR; }
";"            { return SEMI; }
","            { return COMMA; }
"{"            { return LBRACE; }
"}"            { return RBRACE; }
"["            { return LBRACKET; }
"]"            { return RBRACKET; }
"("            { return LPAREN; }
")"            { return RPAREN; }

{ID}           { yylval.string = strdup(yytext); return ID; }
{NUM}          { yylval.num = atoi(yytext); return NUM; }

"/*"           { BEGIN(COMMENT); }
<COMMENT>"*/"  { BEGIN(INITIAL); }
<COMMENT>\n    { line_num++; }
<COMMENT>.     { /* Ignora conteúdo do comentário */ }
<COMMENT><<EOF>> { 
    fprintf(stderr, "ERRO LÉXICO: Comentário não fechado LINHA: %d\n", line_num);
    exit(1);
}

\n             { line_num++; }
{ESPACO}+      { /* Ignora espaços em branco */ }

.              { 
    fprintf(stderr, "ERRO LÉXICO: '%s' LINHA: %d\n", yytext, line_num);
    exit(1);
}

%%

int yywrap() {
    return 1;
}

/* Função auxiliar para exibir tokens (para depuração) */
void print_token(int token) {
    const char *token_names[] = {
        "ID", "NUM", "ELSE", "IF", "INT", "RETURN", "VOID", "WHILE",
        "ADD", "SUB", "MUL", "DIV", "LE", "LT", "GE", "GT", "EQ", "NE",
        "ATTR", "SEMI", "COMMA", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
        "LPAREN", "RPAREN"
    };
    
    if(token >= 256 && token < 256 + sizeof(token_names)/sizeof(char*)) {
        printf("TOKEN: %s\n", token_names[token-256]);
    } else {
        printf("TOKEN DESCONHECIDO: %d\n", token);
    }
}