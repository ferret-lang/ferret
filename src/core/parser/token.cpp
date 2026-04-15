#include "token.hpp"
#include <iostream>

namespace parser {
TokenType Token::get_type() { return type_; };
std::string Token::get_lexeme() { return lexeme_; };

std::string Token::get_type_as_string() {
  switch (type_) {
  case TokenType::IntegerLiteral:
    return "IntegerLiteral";
  case TokenType::FloatLiteral:
    return "FloatLiteral";
  case TokenType::BooleanLiteral:
    return "BooleanLiteral";
  case TokenType::StringLiteral:
    return "StringLiteral";
  default:
    return "Unknown Token";
  }
};

void Token::print_me() {
  std::cout << get_type_as_string() << "(" << get_lexeme() << ")" << "\n";
};
} // namespace parser
