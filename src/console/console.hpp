#pragma once
#include <string>
#include <stdexcept>

namespace console
{
  struct ConsoleParseError : public std::runtime_error
  {
    explicit ConsoleParseError(const std::string &message) : std::runtime_error(message) {};
  };

  struct CompilerOptions
  {
    std::string source_file;
    std::string output_file;
  };

  CompilerOptions parse_args(int argc, char **argv);
}