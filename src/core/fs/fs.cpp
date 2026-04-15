#include "fs.hpp"
#include <fstream>
#include <sstream>

namespace fs {
std::string read_file(const std::string &file_path) {
  std::ifstream file(file_path);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
};
} // namespace fs
