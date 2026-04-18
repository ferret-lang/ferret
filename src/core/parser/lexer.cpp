#include "lexer.hpp"
#include "token.hpp"
#include <cctype>
#include <cstdio>
#include <unordered_map>

namespace parser {

std::unordered_map<std::string, TokenType> keywords = {
    {"return", TokenType::Return}};

bool Lexer::is_eof() const { return position_ >= source_code_.length(); }
char Lexer::peek() const { return source_code_[position_]; };
char Lexer::advance() { return source_code_[position_++]; }

void Lexer::skip_whitespaces() {
  while (std::isspace(peek()) && peek() != '\n')
    advance();
}

Token Lexer::parse_identifier() {
  std::size_t begin = position_;
  advance();
  while (std::isalnum(peek()))
    advance();
  std::size_t length = position_ - begin;

  std::string lexeme = source_code_.substr(begin, length);
  TokenType token_type =
      keywords.count(lexeme) == 0 ? TokenType::Identifier : keywords.at(lexeme);
  return Token(lexeme, token_type);
};

Token Lexer::parse_number_literal() {
  std::size_t begin = position_;
  advance();
  bool floating_point = false;
  while (std::isalnum(peek()) || peek() == '.') {
    if (peek() == '.') {
      if (floating_point) {
        throw LexerParseError(
            LexerErrorType::InvalidFloatLiteral,
            "A number cannot contain multiple decimal points.");
      }
      floating_point = true;
    }
    advance();
  }
  std::size_t length = position_ - begin;

  std::string lexeme = source_code_.substr(begin, length);
  auto token_type =
      floating_point ? TokenType::FloatLiteral : TokenType::IntegerLiteral;
  return Token(lexeme, token_type);
};

TokenType Lexer::peek_punctuation_type() const {
  switch (peek()) {
  case '{':
    return TokenType::LBrace;
  case '}':
    return TokenType::RBrace;
  case '(':
    return TokenType::LBracket;
  case ')':
    return TokenType::RBracket;
  case ';':
    return TokenType::SemiColon;
  case ',':
    return TokenType::Comma;
  default:
    std::string current_character_s = std::string(1, peek());
    std::string error_message =
        "The compiler is unable to recognize '" + current_character_s + "'";
    throw LexerParseError(LexerErrorType::UnrecognizableCharacter,
                          error_message);
  }
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens = {};

  while (!is_eof()) {
    skip_whitespaces();
    char current_character = peek();

    if (std::isalpha(current_character)) {
      tokens.emplace_back(parse_identifier());
      continue;
    }

    if (std::isalnum(current_character)) {
      tokens.emplace_back(parse_number_literal());
      continue;
    }

    if (current_character == '\n') {
      advance();
      continue;
    }

    TokenType token_type = peek_punctuation_type();
    std::string lexeme = std::string(1, current_character);
    tokens.emplace_back(lexeme, token_type);

    advance();
  }

  return tokens;
};
} // namespace parser
