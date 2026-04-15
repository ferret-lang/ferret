#include "lexer.hpp"
#include <memory>

namespace parser {
std::vector<std::unique_ptr<Token>> Lexer::tokenize() {
  std::vector<std::unique_ptr<Token>> tokens = {};
  tokens.emplace_back(std::make_unique<Token>("int", TokenType::StringLiteral));
  tokens.emplace_back(
      std::make_unique<Token>("main", TokenType::StringLiteral));
  return tokens;
};
} // namespace parser
