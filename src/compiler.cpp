#include "console/console.hpp"
#include <iostream>

int main(int argc, char **argv) {
  auto options = console::parse_args(argc, argv);
  std::cout << "Source file: " << options.source_file << "\n";
  std::cout << "Output file: " << options.output_file << "\n";
  return 0;
}
