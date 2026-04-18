#pragma once
#include <stdexcept>
#include <string>

namespace console {
class ConsoleParseError : public std::runtime_error {
public:
  explicit ConsoleParseError(const std::string &message)
      : std::runtime_error(message) {}
};

struct CompilerOptions {
  std::string source_file;
  std::string output_file;
};

CompilerOptions parse_args(int argc, char **argv);
} // namespace console
