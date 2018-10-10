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

#include "token.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

namespace uofmsh {

// Represents a shell's data and methods
class Shell {
  std::string prompt;  // The shell's prompt

  // Runs commands from a file
  static void runFile(std::string fileName);

  // Runs the shell interactively
  static void runPrompt();

  // Runs commands
  static void run(std::string source);

  // Outputs a message about a particular line
  static void report(int line, int column, std::string message);

public:
  // Outputs an error message about a particular line
  static void error(int line, int column, std::string message);

  // Outputs an error message from the parser
  static void error(Error e);

  // The entry point for our shell
  static int main(int argc, char **argv);

  static bool hadError;  // Whether the last command typed had an error

};

} // namespace uofmsh

#endif
