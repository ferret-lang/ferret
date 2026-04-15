#include "core/console/console.hpp"
#include "core/fs/fs.hpp"
#include "core/parser/lexer.hpp"
#include "core/parser/token.hpp"
#include <memory>

int main(int argc, char **argv) {
  // Parsing the command-line arguments.
  auto options = console::parse_args(argc, argv);

  // Reading the contents of the source file.
  auto source_code = fs::read_file(options.source_file);

  // Tokenizing the soource code.
  auto lexer = parser::Lexer(source_code);
  auto tokens = lexer.tokenize();

  // Printing the token to the console.
  for (const auto &token : tokens) {
    token->print_me();
  }
  return 0;
}
