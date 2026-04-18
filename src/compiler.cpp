#include "core/console/console.hpp"
#include "core/fs/fs.hpp"
#include "core/parser/lexer.hpp"
#include "core/parser/parser.hpp"

int main(int argc, char **argv) {
  auto options = console::parse_args(argc, argv);
  auto source_code = fs::read_file(options.source_file);

  auto lexer = parser::Lexer(source_code);
  auto tokens = lexer.tokenize();

  auto parser = parser::Parser(tokens);
  auto program = parser.generate_program();
  parser.print_program(program.get());

  return 0;
}
