#ifndef UOFMSH_H
#define UOFMSH_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "helpers.hpp"

namespace uofmsh {

// Represents a shell's data and methods
class Shell {
  std::string prompt;
  std::vector<std::string> commands;


  static void runFile(std::string fileName);
  static void runPrompt();
  static void run(std::string source);

  static void error(int line, std::string message);
  static void report(int line, std::string where, std::string message);

  public:
    static int main(int argc, char **argv);
    static bool hadError;

    enum class TokenType {
      // Single-character tokens
      LEFT_PAREN,    // (
      RIGHT_PAREN,   // )
      LEFT_BRACE,    // {
      RIGHT_BRACE,   // }
      PIPE,          // |
      SEMICOLON,     // ;
      POUND,         // #

      // One or two character tokens
      REDIRECT_LEFT,   // <
      DREDIRECT_LEFT,  // >
      REDIRECT_RIGHT,  // >>
      DREDIRECT_RIGHT, // <<
      BANG,            // !
      AND_IF,          // &&
      OR_IF,           // ||
      DSEMI,           // ;;
      LESS_AND,        // >&
      GREATAND,        // <&
      LESSGREAT,       // <>
      DLESSDASH,       // <<-
      CLOBBER,         // >|

      // Literals
      WORD, ASSIGNMENT_WORD, NAME, NEWLINE, IO_NUMBER,

      // Keywords
      IF, THEN, ELSE, ELIF, FI, DO, DONE,
      CASE, ESAC, WHILE, UNTIL, FOR, IN,

      END // EOF
    };
};


} // namespace uofmsh

#endif
