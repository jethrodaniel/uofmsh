#ifndef PARSER_H
#define PARSER_H

#include "scanner.hpp"

#include <optional>

namespace uofmsh {

class Error {
  std::string msg;
  int line, column;

public:
  Error(std::string msg, int line, int column)
    : msg(msg), line(line), column(column) { }

  std::string getMsg() {
    return msg;
  }
};

class ASTNode {
std::optional<Error> error;

public:
  bool isValid() {
    return error.has_value();
  }

  Error getError() {
    return error.value();
  }

  //ASTNode();
};

class Redirection : public ASTNode {
  Token redirectionOp, filename;
public:
  Token getRedirectionOp() {
    return redirectionOp;
  }
  Token getFilename() {
    return filename;
  }
  Redirection(Token redirectionOp, Token filename)
    : redirectionOp(redirectionOp), filename(filename) { }

  bool operator==(const Redirection &other) {
    return redirectionOp == other.redirectionOp &&
           filename      == other.filename;
  }

  friend bool operator==(const Redirection &r1, const Redirection r2) {
    return r1.redirectionOp == r2.redirectionOp &&
           r1.filename      == r2.filename;
  }

  // Allows a redirection to be printed using <<
  friend std::ostream &operator<<(std::ostream &output, const Redirection &r ) {
    output << "    Redirection [\n"
           << "      redirectionOp: [" << r.redirectionOp << "],\n"
           << "      filename: [" << r.filename << "]\n"
           << "    ]";
    return output;
  }

};

class Command : public ASTNode {
  const std::vector<Redirection> prefix;
  const std::vector<Token> elements;
  const std::vector<Redirection> suffix;
public:
  const std::vector<Redirection> getPrefix() {
    return prefix;
  }
  const std::vector<Redirection> getSuffix() {
    return suffix;
  }
  const std::vector<Token> getElements() {
    return elements;
  }
  Command(std::vector<Redirection> prefix,
          std::vector<Token> elements,
          std::vector<Redirection> suffix)
    : prefix(prefix), elements(elements), suffix(suffix) { }

  bool operator==(const Command &other) {
    return prefix == other.prefix &&
           elements == other.elements &&
           suffix == other.suffix;
  }

  friend bool operator==(const Command &c1, const Command c2) {
    return c1.prefix   == c2.prefix &&
           c1.elements == c2.elements &&
           c1.suffix   == c2.suffix;
  }

  // Allows a command to be printed using <<
  friend std::ostream &operator<<(std::ostream &output, const Command &c ) {
    output << "Command [\n"
           << "  prefix: [";

    for (const auto &p : c.prefix)
      output << "\n" << p << "\n";

    output << "  ],\n" // prefix
           << "  elements: [";

    for (const auto &e : c.elements)
      output << "\n    " << e << "\n";

    output << "  ]\n" // elements
           << "  suffix: [";

    for (const auto &s : c.suffix)
      output << "\n" << s;

    output << "  ]\n" // suffix
           << "]"; // command
    return output;
  }

};

class Pipeline : public ASTNode {
  std::vector<Command> commands;
public:
  std::vector<Command> getCommands() {
    return commands;
  }
  Pipeline(std::vector<Command> commands) : commands(commands) { }

  bool operator==(const Pipeline &other) {
    return commands == other.commands;
  }

  friend bool operator==(const Pipeline &p1, const Pipeline p2) {
    return p1.commands == p2.commands;
  }

};

class Program : public ASTNode {
  std::vector<Pipeline> pipelines;
public:
  std::vector<Pipeline> getPipelines() {
    return pipelines;
  }
  Program(std::vector<Pipeline> pipelines) : pipelines(pipelines) { };

  bool operator==(const Program &other) {
    return pipelines == other.pipelines;
  }

  friend bool operator==(const Program &p1, const Program p2) {
    return p1.pipelines == p2.pipelines;
  }

};

/* A parser forms meaningful expressions from a series of tokens
 *
 * Our simple shell grammar is defined below, starting with the 'program' rule
 *
 * program -> list
 *            list separator
 *
 * separator -> separator_op linebreak
 *              newline_list
 *
 * separator_op -> '&'
 *                 ';'
 *
 * linebreak -> ε
 *              newline_list
 *
 * newline_list -> '\n'
 *                 newline_list '\n'
 *
 * list -> and_or
 *         list separator_op and_or
 *
 * and_or -> pipeline
 *           and_or '&&' linebreak pipeline
 *           and_or '||' linebreak pipeline
 *
 * pipeline -> command
 *             pipeline '|' linebreak command
 *
 * command -> cmd_prefix cmd_word cmd_suffix
 *            cmd_prefix cmd_word
 *            cmd_prefix
 *            cmd_name cmd_suffix
 *            cmd_name
 *
 * cmd_name -> WORD
 *
 * cmd_word -> WORD
 *
 * cmd_prefix -> io_redirect
 *               cmd_prefix io_redirect
 *
 * cmd_suffix -> io_redirect
 *               cmd_suffix io_redirect
 *
 * io_redirect -> io_file
 *                IO_NUMBER io_file
 *
 * io_file -> '<' filename
 *            DREDIRECT_LEFT filename
 *            '>' filename
 *            DREDIRECT_RIGHT filename
 *
 * filename -> WORD    // Perform any redirection
 */
class Parser {
  const std::string source;  // The source text to process
  Scanner scanner;           // The scanner to get tokens from
  std::vector<Token> tokens; // A list of tokens
  int current = 0;           // The current token's index

  const std::vector<Token::Type> REDIRECTION_OPS = {
    Token::Type::REDIRECT_LEFT,
    Token::Type::REDIRECT_RIGHT
  };

  /**
   * @param  n  The number of tokens to look ahead
   * @return    The current token
   */
  Token peek() {
    return tokens[current];
  }

  /**
   * @return  The previous token
   */
  Token previous() {
    return tokens[current - 1];
  }

  /**
   * @return Whether or not the parser is the end of input
   */
  bool isAtEnd() {
    return peek().getType() == Token::Type::END;
  }

  /**
   * Moves the parser to the next token
   *
   * @return The previous Token
   */
  Token advance() {
    if (!isAtEnd()) current++;
    return previous();
  }

  /**
   * Moves the parser to the previous token
   *
   * @return The last visted Token
   */
  Token backup() {
    if (current > 0)
      return tokens[current--];
    else
      return peek();
  }

   /**
   * Checks the type of tokens[n + current] type against a list
   *
   * @param  types  A list of types to compare with
   * @param  n      The number of tokens to look ahead
   * @return        Whether the tokens[n+current] is of a type in types
   */
  bool match(std::vector<Token::Type> types) {
    for (auto t : types)
      if (peek().getType() == t)
        return true;

    return false;
  }

  std::vector<Redirection> redirection() {
    std::vector<Redirection> redirections;

    while (match(REDIRECTION_OPS)) {
      auto redirect = advance();

      if (match({Token::Type::TOKEN})) {
        auto filename = advance();
        redirections.push_back(Redirection(redirect, filename));
      } else
        throw(Parser::Exception(Error("Expected a filename", redirect.getLine(), redirect.getStart())));
    }

    return redirections;
  }

  Command command() {
    std::vector<Redirection> prefix = redirection();

    std::vector<Token> elements;

    while (match({Token::Type::TOKEN})) {
      elements.push_back(advance());
    }

    return Command(prefix, elements, {});
  }

  Pipeline pipeline() {
    Command c = command();

    Pipeline p(std::vector<Command>{c});
    return p;
  }

public:
  /**
   * @return  A new parser instance, initialized with input
   */
  Parser(std::string source)
    : source(source), scanner(Scanner(source)) { }

  // An exception to throw in case of a parsing error
  class Exception : std::exception {
    Error error;
  public:
    Exception(Error error) : error(error) { }
  };

  // Parse and run the input
  Program parse() {
    try {
      tokens = scanner.scanTokens();
    } catch (const Scanner::Exception e) {
      throw;
    }

    Pipeline pipe = pipeline();

    // if (!pipe.isValid())
    //   throw(Parser::Exception(pipe.getError()));

    return Program({pipe});
  }
};

} // namespace uofmsh

#endif
