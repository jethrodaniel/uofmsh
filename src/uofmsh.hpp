#ifndef UOFMSH_H
#define UOFMSH_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <ostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "helpers.hpp"

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

  // The entry point for our shell
  static int main(int argc, char **argv);

  static bool hadError;  // Whether the last command typed had an error

  enum class TokenType {
    LEFT_PAREN,    // (
    RIGHT_PAREN,   // )
    LEFT_BRACE,    // {
    RIGHT_BRACE,   // }
    PIPE,          // |
    SEMI,          // ;
    POUND,         // #
    COLON,         // :
    HYPHEN,        // -

    REDIRECT_LEFT,   // <
    DREDIRECT_LEFT,  // >
    REDIRECT_RIGHT,  // >>
    DREDIRECT_RIGHT, // <<
    BANGBANG,        // !!
    BANG,            // !
    AND,             // &
    AND_IF,          // &&
    OR_IF,           // ||

    // A generic token, which could be any of the below tokens,
    // depending on the context
    TOKEN,

    WORD,
    ASSIGNMENT_WORD,
    NAME,
    NEWLINE,
    IO_NUMBER,

    END // EOF
  };
};

// A token represents the building blocks of the grammar
class Token {
  const Shell::TokenType type;
  const std::string lexeme;    // The characters that form this token
  const int line,              // The line number of this token
            start,             // The column number of the start of this token
            end;               // The column number of the end of this token

public:
  // @return  A new Token instance
  Token(Shell::TokenType type, std::string lexeme,
        const int line, const int start, const int end)
  : type(type), lexeme(lexeme), line(line), start(start), end(end) { }

  // Allows a token to be printed using <<
  friend std::ostream &operator<<(std::ostream &output, const Token &t ) {
    output << "Type: " << (int)t.type << " ["
           << t.line << "," << t.start << " - " << std::setw(3) << t.end
           << "]: '" << t.lexeme << "'";
    return output;
  }

  Shell::TokenType getType() {
    return type;
  }

  std::string getLexeme() {
    return lexeme;
  }

};

// A scanner/lexer reads the input and splits it into tokens
class Scanner {
  const std::string source;  // The source text to process
  std::vector<Token> tokens; // A list of the current tokens

  unsigned int start   = 0,  // The start of the current token
               current = 0,  // The index of the current token
               line    = 1;  // The line number of the current token

  // @return  Whether or not the scanner is at the end of input
  bool isAtEnd() {
    return current >= source.size();
  }

  // Moves the scanner to the next character
  // @return  the current character
  char advance() {
    current++;
    return source[current - 1];
  }

  // Adds a token to the list of tokens
  void addToken(Shell::TokenType type) {
    std::string lexeme = source.substr(start, current - start);
    tokens.push_back(Token(type, lexeme, line, start, current));
  }

  // Looks at the next character, without moving the scanner
  // @return  the next character
  char peek() {
    if (isAtEnd())
      return '\0';
    else
      return source[current];
  }

  void alphaNumeric() {
    while (std::isalnum(peek()) || peek() == '-')
      advance();

    addToken(Shell::TokenType::TOKEN);
  }

  // Read characters until the the next available token is formed
  void scanToken() {
    char c = advance();
    switch (c) {
      case '(': addToken(Shell::TokenType::LEFT_PAREN); break;
      case ')': addToken(Shell::TokenType::RIGHT_PAREN); break;
      case '{': addToken(Shell::TokenType::LEFT_BRACE); break;
      case '}': addToken(Shell::TokenType::RIGHT_BRACE); break;
      case ';': addToken(Shell::TokenType::SEMI); break;
      case ':': addToken(Shell::TokenType::COLON); break;
      case '<':
        if (peek() == '<') {
          advance();
          addToken(Shell::TokenType::DREDIRECT_LEFT);
        } else
          addToken(Shell::TokenType::REDIRECT_LEFT);

        break;
      case '>':
        if (peek() == '>') {
          advance();
          addToken(Shell::TokenType::DREDIRECT_RIGHT);
        } else
          addToken(Shell::TokenType::REDIRECT_RIGHT);

        break;
      case '!':
        if (peek() == '!') {
          advance();
          addToken(Shell::TokenType::BANGBANG);
        } else
          addToken(Shell::TokenType::BANG);

        break;
      case '&':
        if (peek() == '&') {
          advance();
          addToken(Shell::TokenType::AND_IF);
        } else
          addToken(Shell::TokenType::AND);

        break;
      case '|':
        if (peek() == '|') {
          advance();
          addToken(Shell::TokenType::OR_IF);
        } else
          addToken(Shell::TokenType::PIPE);

        break;
     case '#':
        // If a comment is started, ignore input until the end of the line
        while (peek() != '\n' && !isAtEnd()) advance();
        break;
      case ' ':  // Ignore whitespace
      case '\t':
      case '\r': break;
      case '\n':
        addToken(Shell::TokenType::NEWLINE);
        line++;
        break;
      default:
        if (std::isalnum(c) || (c == '-' && peek() != ' '))
          alphaNumeric();
        else if (c == '-' && peek() == ' ')
          addToken(Shell::TokenType::HYPHEN);
        else
          Shell::error(line, start, "Unexpected character");
    }
  }

public:
  // @return  A new scanner instance
  Scanner(std::string source) : source(source) { }

  // @return  A list of all tokens from the input
  std::vector<Token> scanTokens() {
    // Until the end of input is found, build tokens
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }

    tokens.push_back(Token(Shell::TokenType::END, "END", line, start, current));
    return tokens;
  }
};

} // namespace uofmsh

#endif
