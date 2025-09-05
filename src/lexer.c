#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/lexer.h"

static bool is_alpha(char c) {
  return isalpha(c) || c == '_';
}

static bool is_digit(char c) {
  return isdigit(c);
}

static char lexer_peek(Lexer *lexer) {
  return lexer->pos < lexer->length ? lexer->source[lexer->pos] : '\0';
}

static char lexer_advance(Lexer *lexer) {
  char c = lexer_peek(lexer);
  if (c == '\0') return c;
  lexer->pos++;
  if (c == '\n') {
    lexer->line++;
    lexer->column = 1;
  } else {
    lexer->column++;
  }
  return c;
}

static Token make_token(Lexer *lexer, TokenKind kind, const char *start, size_t length) {
  Token token = {
    .kind = kind,
    .line = lexer->line,
    .column = lexer->column,
    .lexeme = (char *)malloc(length + 1),
  };

  memcpy(token.lexeme, start, length);
  token.lexeme[length] = '\0';

  return token;
}

Lexer *lexer_new(const char *source) {
  Lexer *lexer = malloc(sizeof(Lexer));
  lexer->source = source;
  lexer->length = strlen(source);
  lexer->pos = 0;
  lexer->line = 1;
  lexer->column = 1;
  return lexer;
}

void lexer_free(Lexer *lexer) {
  free(lexer);
}

void token_free(Token token) {
  free(token.lexeme);
}

Token lexer_next_token(Lexer *lexer) {
  // Skip whitespace
  while (isspace(lexer_peek(lexer))) {
    lexer_advance(lexer);
  }

  size_t start = lexer->pos;
  char c = lexer_advance(lexer);

  // End of source
  if (c == '\0') {
    return make_token(lexer, TOKEN_EOF, "", 0);
  }

  // Skip comments (# ... end of line)
  if (c == '#') {
    while (lexer_peek(lexer) != '\n' && lexer_peek(lexer) != '\0') {
      lexer_advance(lexer);
    }
    return lexer_next_token(lexer);
  }

  // Handle @keywords
  if (c == '@') {
    size_t kw_start = lexer->pos;
    while (isalpha(lexer_peek(lexer))) lexer_advance(lexer);

    size_t length = lexer->pos - kw_start;
    char *kw = strndup(lexer->source + kw_start, length);

    TokenKind kind = TOKEN_ERROR;
    if      (strcmp(kw, "fn")     == 0) kind = TOKEN_FN;
    else if (strcmp(kw, "type")   == 0) kind = TOKEN_TYPE;
    else if (strcmp(kw, "match")  == 0) kind = TOKEN_MATCH;
    else if (strcmp(kw, "when")   == 0) kind = TOKEN_WHEN;
    else if (strcmp(kw, "return") == 0) kind = TOKEN_RETURN;
    else if (strcmp(kw, "use")    == 0) kind = TOKEN_USE;

    free(kw);
    return make_token(lexer, kind, lexer->source + start, lexer->pos - start);
  }

  // Identifiers
  if (is_alpha(c)) {
    while (is_alpha(lexer_peek(lexer)) || is_digit(lexer_peek(lexer))) {
      lexer_advance(lexer);
    }
    return make_token(lexer, TOKEN_IDENTIFIER, lexer->source + start, lexer->pos - start);
  }

  // Numbers
  if (is_digit(c)) {
    while (is_digit(lexer_peek(lexer))) lexer_advance(lexer);
    return make_token(lexer, TOKEN_INT_LITERAL, lexer->source + start, lexer->pos - start);
  }

  // Strings
  if (c == '"') {
    size_t str_start = lexer->pos;
    while (lexer_peek(lexer) != '"' && lexer_peek(lexer) != '\0') lexer_advance(lexer);
    if (lexer_peek(lexer) == '"') lexer_advance(lexer);
    return make_token(lexer, TOKEN_STRING_LITERAL, lexer->source + str_start, lexer->pos - str_start - 1);
  }

  // Operators and symbols
  if (c == '-' && lexer_peek(lexer) == '>') {
    lexer_advance(lexer);
    return make_token(lexer, TOKEN_ARROW, "->", 2);
  }
  if (c == '|' && lexer_peek(lexer) == '>') {
    lexer_advance(lexer);
    return make_token(lexer, TOKEN_PIPE, "|>", 2);
  }

  switch (c) {
    case '=': return make_token(lexer, TOKEN_EQUALS, "=", 1);
    case ':': return make_token(lexer, TOKEN_COLON, ":", 1);
    case '.': return make_token(lexer, TOKEN_DOT, ".", 1);
    case '(': return make_token(lexer, TOKEN_LPAREN, "(", 1);
    case ')': return make_token(lexer, TOKEN_RPAREN, ")", 1);
    case '{': return make_token(lexer, TOKEN_LBRACE, "{", 1);
    case '}': return make_token(lexer, TOKEN_RBRACE, "}", 1);
    case ',': return make_token(lexer, TOKEN_COMMA, ",", 1);
    case ';': return make_token(lexer, TOKEN_SEMICOLON, ";", 1);
    case '/': return make_token(lexer, TOKEN_SLASH, "/", 1);       
    case '&': return make_token(lexer, TOKEN_SELF, "&", 1);        
    case '?': return make_token(lexer, TOKEN_OPTIONAL, "?", 1);    
  }

  // Unknown character
  return make_token(lexer, TOKEN_ERROR, lexer->source + start, lexer->pos - start);
}


const char *token_kind_to_string(TokenKind kind) {
  switch (kind) {
    case TOKEN_IDENTIFIER:      return "IDENTIFIER";
    case TOKEN_INT_LITERAL:     return "INT_LITERAL";
    case TOKEN_STRING_LITERAL:  return "STRING_LITERAL";
    case TOKEN_FN:              return "@FN";
    case TOKEN_TYPE:            return "@TYPE";
    case TOKEN_MATCH:           return "@MATCH";
    case TOKEN_WHEN:            return "@WHEN";
    case TOKEN_RETURN:          return "@RETURN";
    case TOKEN_USE:             return "@USE";
    case TOKEN_ARROW:           return "->";
    case TOKEN_PIPE:            return "|>";
    case TOKEN_EQUALS:          return "=";
    case TOKEN_COLON:           return ":";
    case TOKEN_DOT:             return ".";
    case TOKEN_LPAREN:          return "(";
    case TOKEN_RPAREN:          return ")";
    case TOKEN_LBRACE:          return "{";
    case TOKEN_RBRACE:          return "}";
    case TOKEN_COMMA:           return ",";
    case TOKEN_SEMICOLON:       return ";";
    case TOKEN_SELF:            return "&";
    case TOKEN_OPTIONAL:        return "?";
    case TOKEN_SLASH:           return "/";
    case TOKEN_ERROR:           return "ERROR";
    case TOKEN_EOF:             return "EOF";
    default:                    return "UNKNOWN";
  }
}
