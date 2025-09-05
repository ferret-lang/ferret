#ifndef FERRET_LEXER_H
#define FERRET_LEXER_H

#include <stddef.h>

typedef enum {
  TOKEN_EOF,
  TOKEN_IDENTIFIER,
  TOKEN_INT_LITERAL,
  TOKEN_STRING_LITERAL,
  
  // Special words.
  TOKEN_FN,
  TOKEN_TYPE,
  TOKEN_MATCH,
  TOKEN_WHEN,
  TOKEN_RETURN,
  TOKEN_NIL, 
  TOKEN_VOID,
  TOKEN_USE,

  // Symbols
  TOKEN_ARROW,
  TOKEN_PIPE,
  TOKEN_EQUALS,
  TOKEN_COLON,
  TOKEN_DOT,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_COMMA,
  TOKEN_SEMICOLON,
  TOKEN_SELF,      
  TOKEN_OPTIONAL,  
  TOKEN_SLASH,     

  TOKEN_ERROR
} TokenKind;

typedef struct {
  int line;
  int column;
  char *lexeme;
  TokenKind kind;
} Token;

typedef struct {
  int line;
  int column;
  size_t pos;
  size_t length;
  const char *source;
} Lexer;

Lexer *lexer_new(const char *source);
Token lexer_next_token(Lexer *lexer);
const char *token_kind_to_string(TokenKind kind);

void lexer_free(Lexer *lexer);
void token_free(Token token);


#endif