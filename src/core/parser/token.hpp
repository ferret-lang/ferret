#pragma once
#include <string>

namespace parser {

// This enum contains the list of supported tokens by the compiler.
enum class TokenType {
  // Literals
  IntegerLiteral,
  FloatLiteral,
  BooleanLiteral,
  StringLiteral
};

class Token {
public:
  Token(const std::string &lexeme, const TokenType type)
      : lexeme_(lexeme), type_(type) {};

  void print_me();
  TokenType get_type();
  std::string get_lexeme();
  std::string get_type_as_string();

private:
  std::string lexeme_;
  TokenType type_;
};

} // namespace parser
