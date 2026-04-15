#pragma once
#include "token.hpp"
#include <memory>
#include <string>
#include <vector>

namespace parser {

class Lexer {
public:
  std::string source_code;
  Lexer(const std::string &source_code) : source_code(source_code) {};
  std::vector<std::unique_ptr<Token>> tokenize();
};
} // namespace parser
