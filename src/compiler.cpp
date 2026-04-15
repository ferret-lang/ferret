#include "core/console/console.hpp"
#include "core/fs/fs.hpp"
#include <iostream>

int main(int argc, char **argv) {
  // Parsing the command-line arguments.
  auto options = console::parse_args(argc, argv);

  // Reading the contents of the source file.
  auto source_code = fs::read_file(options.source_file);
  std::cout << source_code << std::endl;
  return 0;
}
