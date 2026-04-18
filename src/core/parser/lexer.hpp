#pragma once
#include "token.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace parser {
enum class LexerErrorType {
  InvalidFloatLiteral,
  UnrecognizableCharacter,
};

class LexerParseError : public std::runtime_error {
public:
  explicit LexerParseError(const LexerErrorType error_type,
                           const std::string message)
      : error_type_(error_type), std::runtime_error(message) {}

private:
  LexerErrorType error_type_;
};

class Lexer {
public:
  Lexer(const std::string &source_code)
      : source_code_(source_code), position_(0) {};
  std::vector<Token> tokenize();

private:
  std::string source_code_;
  std::size_t position_;

  bool is_eof();
  char peek();
  char advance();

  void skip_whitespaces();

  Token parse_identifier();
  Token parse_number_literal();

  TokenType peek_punctuation_type();
};
} // namespace parser
