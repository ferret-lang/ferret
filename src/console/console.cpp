#include "console.hpp"
#include <functional>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace console
{
  class ConsoleParser
  {
  public:
    using OptionCallback = std::function<void(const std::string &)>;

    void add_option(const std::string &option, OptionCallback callback)
    {
      options_[option] = std::move(callback);
    }

    std::vector<std::string> parse_args(int argc, char **argv)
    {
      std::vector<std::string> positional_args;

      for (int i = 1; i < argc; ++i)
      {
        std::string arg = argv[i];

        if (auto eq = arg.find('='); arg.rfind("--", 0) == 0 && eq != std::string::npos)
        {
          std::string key = arg.substr(2, eq - 2);
          std::string value = arg.substr(eq + 1);
          auto it = options_.find(key);
          if (it == options_.end())
            throw new ConsoleParseError("Unknown option: " + key);
          it->second(value);
          continue;
        }

        positional_args.push_back(arg);
      }

      return positional_args;
    }

  private:
    std::unordered_map<std::string, OptionCallback> options_;
  };

  CompilerOptions parse_args(int argc, char **argv)
  {
    CompilerOptions options;
    ConsoleParser parser;

    parser.add_option(
        "outfile",
        [&](const std::string &value)
        { options.output_file = value; });
    auto positional_args = parser.parse_args(argc, argv);

    if (positional_args.empty())
      throw new ConsoleParseError("No source file provided!");
    else if (positional_args.size() > 1)
      throw new ConsoleParseError("Too many arguments provided!");

    options.source_file = positional_args[0];
    if (options.output_file.empty())
      options.output_file = options.source_file + ".out";

    return options;
  }
}