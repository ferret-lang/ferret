#pragma once
#include <string>

namespace parser {

enum class TokenType {
  IntegerLiteral,
  FloatLiteral,
  BooleanLiteral,
  StringLiteral,

  Identifier,
};

class Token {
public:
  Token(const std::string &lexeme, const TokenType type)
      : lexeme_(lexeme), type_(type) {};

  void print_me() const;
  TokenType get_type() const;
  std::string get_lexeme() const;
  std::string get_type_as_string() const;

private:
  std::string lexeme_;
  TokenType type_;
};

} // namespace parser
