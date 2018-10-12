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
  //  @return  the previous character
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

  // Constructs an alphnumeric token
  void alphaNumeric(bool startsWithNum = false) {
    bool onlyNumbers = startsWithNum;

    while (std::isalnum(peek()) || peek() == '-' || peek() == '_' || peek() == '/') {
      if (!std::isdigit(peek()))
        onlyNumbers = false;

      advance();
    }

    if (onlyNumbers && (peek() == '<' || peek() == '>')) {
      addToken(Token::Type::IO_NUMBER);
      start = current;

      if (peek() == '<') {
        advance(); // Skip a <
        if (peek() == '<') {
          advance(); // Skip the next <
          addToken(Token::Type::DREDIRECT_LEFT);
        } else
          addToken(Token::Type::REDIRECT_LEFT);
      } else {
        advance(); // Skip a >
        if (peek() == '>') {
          advance(); // Skip the next >
          addToken(Token::Type::DREDIRECT_RIGHT);
        } else
          addToken(Token::Type::REDIRECT_RIGHT);
      }
    } else
      addToken(Token::Type::TOKEN);
  }

  // Constructs a single-quoted string
  void singleQuotedStr() {
    while (peek() != '\'' && !isAtEnd())
      advance();

    if (isAtEnd())
      throw Error("Missing single quote.", line, start);
    else {
      start++;   // To skip the leading '
      addToken(Token::Type::SINGLE_QUOTED_STR);
      advance(); // Skip the trailing '
    }
  }

  // Constructs a double-quoted string
  void doubleQuotedStr() {
    while (peek() != '"' && !isAtEnd())
      advance();

    if (isAtEnd())
      throw Error("Missing double quote.", line, start);
    else {
      start++;   // To skip the leading "
      addToken(Token::Type::DOUBLE_QUOTED_STR);
      advance(); // Skip the trailing "
    }
  }

  // Constructs a backtick-quoted string
  void backtickStr() {
    while (peek() != '`' && !isAtEnd())
      advance();

    if (isAtEnd())
      throw Error("Missing backtick.", line, start);
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
        if (std::isalnum(c) || (c == '-' && peek() != ' ') || c == '/') {
          if (std::isdigit(c))
            alphaNumeric(true);
          else
            alphaNumeric();
        } else if (c == '-' && peek() == ' ')
          addToken(Token::Type::HYPHEN);
        else {
          auto error = std::string("Unexpected character '") + c + "'.";
          throw Error(error, line, start);
        }
    }
  }

public:
  //  @param  source  The input text to scan
  //  @return         A new scanner instance
  explicit Scanner(std::string &source) : source(source) { }

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

};

} // namespace uofmsh

#endif
