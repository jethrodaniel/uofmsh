#ifndef PARSER_H
#define PARSER_H

#include <sstream>
#include <optional>

#include "error.hpp"
#include "scanner.hpp"
#include "ast.hpp"

namespace vodka {

// A parser forms meaningful expressions from a series of tokens
class Parser {
  const std::string source;  // The source text to process
  Scanner scanner;           // The scanner to get tokens from
  std::vector<Token> tokens; // A list of tokens
  int current = 0;           // The current token's index

  // A list of redirection operators
  const std::vector<Token::Type> REDIRECTION_OPS = {
    Token::Type::REDIRECT_LEFT,
    Token::Type::DREDIRECT_LEFT,
    Token::Type::REDIRECT_RIGHT,
    Token::Type::DREDIRECT_RIGHT
  };

  // @return    The current token
  Token peek() {
    return tokens[current];
  }

  // @return  The previous token
  Token previous() {
    return tokens[current - 1];
  }

  // @return Whether or not the parser is the end of input
  bool isAtEnd() {
    return peek().getType() == Token::Type::END;
  }

  // Moves the parser to the next token
  //
  // @return The previous Token
  Token advance() {
    if (!isAtEnd()) current++;
    return previous();
  }

  // Checks the type of the current token against a list
  //
  // @param  types  A list of types to compare with
  // @return        Whether the current token is of a type in types
  bool match(std::vector<Token::Type> types) {
    for (auto t : types)
      if (peek().getType() == t)
        return true;

    return false;
  }

  // Parses an io number
  //
  // @return  An optional io number
  std::optional<Token> ioNumber() {
    if (match({Token::Type::IO_NUMBER}))
      return std::optional<Token>(advance());
    else
      return std::nullopt;
  }

  // Parses a redirection instance
  //
  // @return  A list of redirections
  std::vector<Redirection> redirection() {
    std::vector<Redirection> redirections;

    auto ioNum = ioNumber();

    while (match(REDIRECTION_OPS)) {
      auto redirect = advance();

      if (match({Token::Type::TOKEN})) {
        auto filename = advance();
        if (ioNum)
          redirections.push_back(Redirection(ioNum.value(), redirect, filename));
        else
          redirections.push_back(Redirection(redirect, filename));
      } else
        throw(Error("Expected a filename", redirect.getLine(), redirect.getStart()));
    }

    return redirections;
  }

  // Parses a command instance
  //
  // @return  A command
  Command command() {
    std::vector<Redirection> prefix = redirection();

    std::vector<Token> elements;

    while (match({Token::Type::TOKEN}))
      elements.push_back(advance());

    std::vector<Redirection> suffix = redirection();


    if (prefix.size() == 0 && elements.size() == 0 && suffix.size() == 0)
      throw(Error("Expected a command", peek().getLine(), peek().getStart()));
    else
      return Command(prefix, elements, suffix);
  }

  // Parses a pipeline instance
  //
  // @return A pipeline
  Pipeline pipeline() {
    std::vector<Command> commands;

    Command c = command();
    commands.push_back(c);

    while (match({Token::Type::PIPE})) {
      advance(); // skip a |

      if (match({Token::Type::TOKEN}))
        commands.push_back(command());
      else
        throw(Error("Expected a command after |", peek().getLine(), peek().getStart()));
    }

    if (commands.size() == 0)
      throw(Error("Expected a command", peek().getLine(), peek().getStart()));
    else
      return Pipeline(commands);
  }

public:

  // @param  source  The source input
  // @return         A new parser instance
  explicit Parser(std::string source)
    : source(source), scanner(Scanner(source)) { }

  // Parse and run the input
  //
  // @return  A new program instance
  Program parse(bool throwError = false) {
    std::vector<Pipeline> pipelines;

    try {

      tokens = scanner.scanTokens();
      Pipeline pipe = pipeline();

      pipelines.push_back(pipe);

      while (match({Token::Type::SEMI, Token::Type::NEWLINE})) {
        advance(); // skip a ; or a \n

        while (match({Token::Type::SEMI, Token::Type::NEWLINE}))
          advance();  // Skip repeated ; or \n

        if (match({Token::Type::TOKEN}))
          pipelines.push_back(pipeline());
      }

    } catch (const Error &e) {
      if (throwError)
        throw;
      else
        return Program({});
    }

    return Program(pipelines);
  }
};

} // namespace vodka

#endif
