#include "token.hpp"
#include <iostream>

namespace parser {
TokenType Token::get_type() const { return type_; };
std::string Token::get_lexeme() const { return lexeme_; };

std::string Token::get_type_as_string() const {
  switch (type_) {
  case TokenType::IntegerLiteral:
    return "IntegerLiteral";
  case TokenType::FloatLiteral:
    return "FloatLiteral";
  case TokenType::BooleanLiteral:
    return "BooleanLiteral";
  case TokenType::StringLiteral:
    return "StringLiteral";
  case TokenType::Identifier:
    return "Identifier";

  case TokenType::LBrace:
  case TokenType::RBrace:
  case TokenType::LBracket:
  case TokenType::RBracket:
  case TokenType::SemiColon:
  case TokenType::Comma:
    return "Punctuation";

  case TokenType::Return:
    return "Keyword";

  default:
    return "Unknown Token";
  }
};

void Token::print_me() const {
  std::cout << get_type_as_string() << "(" << get_lexeme() << ")" << "\n";
};
} // namespace parser
