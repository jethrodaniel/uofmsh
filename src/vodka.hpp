#ifndef UOFMSH_H
#define UOFMSH_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <ios>
#include <cctype>
#include <ostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <sstream>
#include <optional>

#include "error.hpp"
#include "token.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

namespace vodka {

// Represents a shell's data and methods
class Shell {
  std::string prompt;  // The shell's prompt

  // Runs commands from a file
  void runFile(std::string fileName);

  // Runs the shell interactively
  void runPrompt();

  // Runs commands
  void run(std::string source);

  // Runs the AST generated from input
  Interpreter interpreter;

public:
  // Outputs an error message
  void error(Error e);

  // The entry point for our shell
  int main(int argc, char **argv);

  bool hadError = false;  // Whether the last command typed had an error

};

} // namespace vodka

#endif
