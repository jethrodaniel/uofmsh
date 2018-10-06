#ifndef SCANNER_H
#define SCANNER_H

#include "token.hpp"
#include "scanner.hpp"
#include "uofmsh.hpp"

namespace uofmsh {

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
  // @return  the previous character
  char advance() {
    return source[current++];
  }

  // Adds a token to the list of tokens
  void addToken(Token::Type type) {
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

    addToken(Token::Type::TOKEN);
  }

  void singleQuotedStr() {
    while (peek() != '\'' && !isAtEnd())
      advance();

    if (isAtEnd())
      throw Exception(line, start, "Missing single quote.");
    else {
      start++;   // To skip the leading '
      addToken(Token::Type::SINGLE_QUOTED_STR);
      advance(); // Skip the trailing '
    }
  }

  void doubleQuotedStr() {
    while (peek() != '"' && !isAtEnd())
      advance();

    if (isAtEnd())
      throw Exception(line, start, "Missing double quote.");
    else {
      start++;   // To skip the leading "
      addToken(Token::Type::DOUBLE_QUOTED_STR);
      advance(); // Skip the trailing "
    }
  }

  void backtickStr() {
    while (peek() != '`' && !isAtEnd())
      advance();

    if (isAtEnd())
      throw Exception(line, start, "Missing backtick.");
    else {
      start++;   // To skip the leading "
      addToken(Token::Type::BACKTICK_STR);
      advance(); // Skip the trailing "
    }
  }

  // Read characters until the the next available token is formed
  void scanToken() {
    char c = advance();
    switch (c) {
      case '(': addToken(Token::Type::LEFT_PAREN); break;
      case ')': addToken(Token::Type::RIGHT_PAREN); break;
      case '{': addToken(Token::Type::LEFT_BRACE); break;
      case '}': addToken(Token::Type::RIGHT_BRACE); break;
      case ';': addToken(Token::Type::SEMI); break;
      case ':': addToken(Token::Type::COLON); break;
      case '\\': addToken(Token::Type::BACKSLASH); break;
      case '\'':
        singleQuotedStr();
        break;
      case '"':
        doubleQuotedStr();
        break;
      case '`':
        backtickStr();
        break;
      case '<':
        if (peek() == '<') {
          advance();
          addToken(Token::Type::DREDIRECT_LEFT);
        } else
          addToken(Token::Type::REDIRECT_LEFT);

        break;
      case '>':
        if (peek() == '>') {
          advance();
          addToken(Token::Type::DREDIRECT_RIGHT);
        } else
          addToken(Token::Type::REDIRECT_RIGHT);

        break;
      case '!':
        if (peek() == '!') {
          advance();
          addToken(Token::Type::BANGBANG);
        } else
          addToken(Token::Type::BANG);

        break;
      case '&':
        if (peek() == '&') {
          advance();
          addToken(Token::Type::AND_IF);
        } else
          addToken(Token::Type::AND);

        break;
      case '|':
        if (peek() == '|') {
          advance();
          addToken(Token::Type::OR_IF);
        } else
          addToken(Token::Type::PIPE);

        break;
     case '#':
        // If a comment is started, ignore input until the end of the line
        while (peek() != '\n' && !isAtEnd()) advance();
        break;
      case ' ':  // Ignore whitespace
      case '\t':
      case '\r': break;
      case '\n':
        addToken(Token::Type::NEWLINE);
        line++;
        break;
      default:
        if (std::isalnum(c) || (c == '-' && peek() != ' '))
          alphaNumeric();
        else if (c == '-' && peek() == ' ')
          addToken(Token::Type::HYPHEN);
        else
          throw Scanner::Exception(line, start, "Unexpected character");
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

    tokens.push_back(Token(Token::Type::END, "END", line, start, current));
    return tokens;
  }

  // An exception to throw in case of a scanning error
  class Exception : std::exception {
  public:
    const int line, start;
    std::string msg;
    Exception(const int line, const int start, std::string msg)
      : line(line), start(start), msg(msg) { }
  };
};

} // namespace uofmsh

#endif
