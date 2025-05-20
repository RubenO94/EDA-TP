# Compilador e flags
CC = gcc
INCLUDE = -Iinclude -Iinclude/core -Iinclude/io -Iinclude/ui -Iinclude/utils
CFLAGS = -g -Wall $(INCLUDE)

# Diretórios
SRC_DIR = src
LIB_DIR = lib
BIN_DIR = bin

# Ficheiros principais
MAIN = $(SRC_DIR)/main.c
MAIN_OBJ = $(MAIN:.c=.o)
TARGET = $(BIN_DIR)/main

# Lib: todos os .c exceto o main
LIB_SRC = $(shell find $(SRC_DIR) -name "*.c" ! -name "main.c")
LIB_OBJ = $(LIB_SRC:.c=.o)

STATIC_LIB = $(LIB_DIR)/libed.a

# Flags de link
LD_FLAGS = -L$(LIB_DIR)
LD_LIBS = -led

# Regra principal
all: $(TARGET)

# Compilar o executável principal
$(TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(LD_FLAGS) $(LD_LIBS) -o $@

# Compilar a biblioteca
$(STATIC_LIB): $(LIB_OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

# Regra genérica para compilar qualquer .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(SRC_DIR)/**/*.o $(BIN_DIR) $(LIB_DIR)
