#ifndef UOFMSH_H
#define UOFMSH_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
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

  static void report(int line, std::string where, std::string message);

  public:
    static void error(int line, std::string message);
    static int main(int argc, char **argv);
    static bool hadError;

    enum class TokenType {
      // Single-character tokens
      LEFT_PAREN,    // (
      RIGHT_PAREN,   // )
      LEFT_BRACE,    // {
      RIGHT_BRACE,   // }
      PIPE,          // |
      SEMI,          // ;
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

class Token {
  const Shell::TokenType type;
  const std::string lexeme;
  const int line;

public:
  Token(Shell::TokenType type, std::string lexeme, const int line)
  : type(type), lexeme(lexeme), line(line) { }

  std::string toString() {
    // return std::to_string(this->type) + " " + std::to_string(this->lexeme);
    return this->lexeme;
  }

};

class Scanner {
  const std::string source;
  std::vector<Token> tokens;

  unsigned int start   = 0,
               current = 0,
               line    = 1;

  bool isAtEnd() {
    return current >= source.size();
  }

  char advance() {
    current++;
    return source[current - 1];
  }

  void addToken(Shell::TokenType type) {
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type, text, line));
  }

  void scanToken() {
    char c = advance();
    switch (c) {
      case '(': addToken(Shell::TokenType::LEFT_PAREN); break;
      case ')': addToken(Shell::TokenType::RIGHT_PAREN); break;
      case '{': addToken(Shell::TokenType::LEFT_BRACE); break;
      case '}': addToken(Shell::TokenType::RIGHT_BRACE); break;
      case '|': addToken(Shell::TokenType::PIPE); break;
      case ';': addToken(Shell::TokenType::SEMI); break;
      case '#': addToken(Shell::TokenType::POUND); break;
      default:
        Shell::error(line, "Unexpected character"); break;
    }
  }

public:
  Scanner(std::string source) : source(source) { }

  std::vector<Token> scanTokens() {
    while (!isAtEnd()) {
      // at the beginning of the next lexeme
      start = current;
      scanToken();
    }

    tokens.push_back(Token(Shell::TokenType::END, "", line));
    return tokens;
  }
};

} // namespace uofmsh

#endif
