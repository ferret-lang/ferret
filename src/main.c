#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/lexer.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <source>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening source file!");
    return 1;
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *source = malloc(size + 1);
  fread(source, 1, size, file);
  source[size] = '\0';
  fclose(file);

  Lexer *lexer = lexer_new(source);
  while (true) {
    Token token = lexer_next_token(lexer);
    if (token.kind == TOKEN_EOF) {
      token_free(token);
      break;
    }

    printf("[%d] %-15s '%s'\n", token.line, token_kind_to_string(token.kind), token.lexeme);
    token_free(token);
  }
}