#include <iostream>
#include <fstream>
#include <sstream>
#include "base/Parser.cpp"

int main() {
  // Reading the source file from the system.
  const std::ifstream file("./samples/main.fl");

  // Asserting whether the file is opened.
  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    // Generating the AST.
    auto ast =
      std::make_shared<Parser>(contents)->generateTranslationUnit();

    // Printing the AST.
    Parser::print(ast);
  } else {
    std::cerr << "Unable to not open the specified file!" << std::endl;
  }

  // Terminating the program with the 'SUCCESS' exit code.
  return 0;
}
