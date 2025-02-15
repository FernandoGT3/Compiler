CC = gcc
FLEX = flex
BISON = bison

all: compiler

compiler: lex.yy.c parser.tab.c ast.c symtab.c semant.c codegen.c main.c
    $(CC) -o $@ $^

lex.yy.c: lexer.l
    $(FLEX) $<

parser.tab.c: parser.y
    $(BISON) -d $<

clean:
    rm -f lex.yy.c parser.tab.* compiler *.output