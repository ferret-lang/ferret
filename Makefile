CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
SRC = src/main.c src/lexer.c
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
BIN = ferretc

.PHONY: all clean run

all: $(BIN)

# Link object files to create final binary
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

# Compile .c files into build/*.o
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if missing
build:
	mkdir -p build

clean:
	rm -rf build $(BIN)

run: $(BIN)
	./$(BIN) examples/main.fr
