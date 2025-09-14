#include <iostream>
#include "base/lexer.cpp"
#include <fstream>
#include <sstream>

int main() {
  // Reading the source file from the system.
  const std::ifstream file("../samples/main.fl");

  // Asserting whether the file is opened.
  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    // Initializing the lexer.
    const auto lexer = std::make_shared<Lexer>(contents);
    // Tokenizing the source code.
    const auto tokens = lexer->tokenize();

    // Printing token's lexeme property.
    for (const auto& token : tokens) {
      std::cout << token->getLexeme() << std::endl;
    }
  } else {
    std::cerr << "Unable to not open the specified file!" << std::endl;
  }

  // Terminating the program with the 'SUCCESS' exit code.
  return 0;
}