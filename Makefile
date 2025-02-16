# Configurações do compilador
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -g -Wall -Isrc/ -Iinclude/
SRC_DIR = src/
BUILD_DIR = build/

# Nome do executável
TARGET = compiler

# Arquivos fonte
SRC_C = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_C)) \
      $(BUILD_DIR)parser.tab.o \
      $(BUILD_DIR)lex.yy.o

# Regra padrão
all: $(BUILD_DIR) $(BUILD_DIR)parser.tab.h $(BUILD_DIR)lex.yy.c $(TARGET)

# Cria diretório de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Geração do executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

# Geração do parser (Bison)
$(BUILD_DIR)parser.tab.c $(BUILD_DIR)parser.tab.h: $(SRC_DIR)parser.y | $(BUILD_DIR)
	$(BISON) -d -t -v -o $(BUILD_DIR)parser.tab.c $<

# Geração do lexer (Flex)
$(BUILD_DIR)lex.yy.c: $(SRC_DIR)lexer.l $(BUILD_DIR)parser.tab.h | $(BUILD_DIR)
	$(FLEX) -o $@ $<

# Regra para arquivos objeto gerados a partir do build/
$(BUILD_DIR)%.o: $(BUILD_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Regra para arquivos fonte normais (dependendo do parser)
$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(BUILD_DIR)parser.tab.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Dependências especiais
$(BUILD_DIR)parser.tab.o: $(BUILD_DIR)parser.tab.c
$(BUILD_DIR)lex.yy.o: $(BUILD_DIR)lex.yy.c

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Teste
test: $(TARGET)
	./$(TARGET) ./tests/input/compare.c-

.PHONY: all clean test
