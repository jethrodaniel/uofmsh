#ifndef PARSER_H
#define PARSER_H

#include "scanner.hpp"

#include <optional>

namespace uofmsh {

/**
 * A error specifies a message and where the error occured
 */
class Error {
  std::string msg;  // The error message
  int line, column; // The line and column where the error occured

public:
  /**
   * @param  msg     The error message
   * @param  line    The line where the error occured
   * @param  column  The column where the error occured
   * @return         A new error instance
   */
  explicit Error(std::string msg, int line, int column)
    : msg(msg), line(line), column(column) { }

  /**
   * @return  The error message
   */
  std::string getMsg() {
    return msg;
  }
};

/**
 * An abstract class used to add common AST node functionality.
 */
class ASTNode {
std::optional<Error> error; // The error, if it exists

public:
  // @return  Whether the error has a value
  bool isValid() {
    return !error.has_value();
  }

  // @return  The AST node's error, if it exists
  Error getError() {
    return error.value();
  }
};

/**
 * Represents a redirection
 */
class Redirection : public ASTNode {
  Token redirectionOp, filename; // The tokens that a redirection consists of

public:
  // @return  The redirection operator token
  Token getRedirectionOp() {
    return redirectionOp;
  }

  // @return  The filename token
  Token getFilename() {
    return filename;
  }

  /**
   * @param  redirectOp  The redirection operator token
   * @param  filename    The filename token
   * @return             A new redirection instance
   */
  explicit Redirection(Token redirectionOp, Token filename)
    : redirectionOp(redirectionOp), filename(filename) { }

  /**
   * @param  other  A redirection instance to compare to this instance
   * @return        Whether this redirection is the same, member-wise, as other
   */
  bool operator==(const Redirection &other) {
    return redirectionOp == other.redirectionOp &&
           filename      == other.filename;
  }

  /**
   * @param  r1  A redirection to compare against r2
   * @param  r2  A redirection to compare against r1
   * @return     Whether the redirections are the same, member-wise
   */
  friend bool operator==(const Redirection &r1, const Redirection &r2) {
    return r1.redirectionOp == r2.redirectionOp &&
           r1.filename      == r2.filename;
  }

  /**
   * Allows a redirection instance to be printed using <<
   *
   * @param  output  The output stream to write to
   * @param  r       The redirection instance to write out
   */
  friend std::ostream &operator<<(std::ostream &output, const Redirection &r ) {
    output << "    Redirection [\n"
           << "      redirectionOp: [" << r.redirectionOp << "],\n"
           << "      filename: [" << r.filename << "]\n"
           << "    ]";
    return output;
  }

};

// Represents a command
class Command : public ASTNode {
  const std::vector<Redirection> prefix; // The prefix redirections
  const std::vector<Token> elements;     // The elements of the command
  const std::vector<Redirection> suffix; // The suffix redirections

public:
  /**
   * @return  The prefix redirections
   */
  const std::vector<Redirection> getPrefix() {
    return prefix;
  }

  /**
   * @return  The suffix redirections
   */
  const std::vector<Redirection> getSuffix() {
    return suffix;
  }

  /**
   * @return  The command elements
   */
  const std::vector<Token> getElements() {
    return elements;
  }

  /**
   * @param  prefix    The prefix redirections
   * @param  elements  The command elements
   * @param  suffix    The suffix redirections
   * @return           A new command instance
   */
  explicit Command(std::vector<Redirection> prefix,
                   std::vector<Token> elements,
                   std::vector<Redirection> suffix)
    : prefix(prefix), elements(elements), suffix(suffix) { }

  /**
   * @param  other  A command instance to compare to this instance
   * @return        Whether this command is the same, member-wise, as other
   */
  bool operator==(const Command &other) {
    return prefix == other.prefix &&
           elements == other.elements &&
           suffix == other.suffix;
  }

  /**
   * @param  c1  A command to compare against c2
   * @param  c2  A command to compare against c1
   * @return     Whether the commands are the same, member-wise
   */
  friend bool operator==(const Command &c1, const Command &c2) {
    return c1.prefix   == c2.prefix &&
           c1.elements == c2.elements &&
           c1.suffix   == c2.suffix;
  }

  /**
   * Allows a command instance to be printed using <<
   *
   * @param  output  The output stream to write to
   * @param  c       The command instance to write out
   */
  friend std::ostream &operator<<(std::ostream &output, const Command &c ) {
    output << "  Command: [\n"
           << "    prefix: [";

    for (const auto &p : c.prefix)
      output << "\n    " << p << "\n";

    output << "    ],\n" // prefix
           << "    elements: [";

    for (const auto &e : c.elements)
      output << "\n    " << e << "\n";

    output << "    ]\n" // elements
           << "    suffix: [";

    for (const auto &s : c.suffix)
      output << "\n    " << s << "\n";

    output << "    ]\n" // suffix
           << "  ]"; // command
    return output;
  }

};

// Represents a pipeline
class Pipeline : public ASTNode {
  std::vector<Command> commands; // The commands to pipe together, in order

public:
  /**
   * @return  The commands
   */
  std::vector<Command> getCommands() {
    return commands;
  }

  /**
   * @param  commands  The commands to pipe together
   * @return           A new pipeline instance
   */
  explicit Pipeline(std::vector<Command> commands) : commands(commands) { }

  /**
   * @param  other  A pipeline instance to compare to this instance
   * @return        Whether this pipeline is the same, member-wise, as other
   */
  bool operator==(const Pipeline &other) {
    return commands == other.commands;
  }

  /**
   * @param  p1  A pipeline to compare against p2
   * @param  p2  A pipeline to compare against p1
   * @return     Whether the pipelines are the same, member-wise
   */
  friend bool operator==(const Pipeline &p1, const Pipeline &p2) {
    return p1.commands == p2.commands;
  }

  /**
   * Allows a pipeline instance to be printed using <<
   *
   * @param  output  The output stream to write to
   * @param  p       The pipeline instance to write out
   */
  friend std::ostream &operator<<(std::ostream &output, const Pipeline &p ) {
    output << "Pipeline: [\n";

    for (auto const &c : p.commands)
      output << "\n" << c << "\n";

    output << "\n]";

    return output;
  }
};

// Represents a program, the highest level of the AST
class Program : public ASTNode {
  std::vector<Pipeline> pipelines; // The pipelines, seperated by ;

public:
  /**
   * @return  The pipelines in this program
   */
  std::vector<Pipeline> getPipelines() {
    return pipelines;
  }

  /**
   * @param  pipelines  The pipelines to use
   * @return            A new program instance
   */
  explicit Program(std::vector<Pipeline> pipelines) : pipelines(pipelines) { };

  /**
   * @param  other  A program instance to compare to this instance
   * @return        Whether this program is the same, member-wise, as other
   */
  bool operator==(const Program &other) {
    return pipelines == other.pipelines;
  }

  /**
   * @param  p1  A program to compare against p2
   * @param  p2  A program to compare against p1
   * @return     Whether the programs are the same, member-wise
   */
  friend bool operator==(const Program &p1, const Program &p2) {
    return p1.pipelines == p2.pipelines;
  }


  /**
   * Allows a program instance to be printed using <<
   *
   * @param  output  The output stream to write to
   * @param  p       The program instance to write out
   */
  friend std::ostream &operator<<(std::ostream &output, const Program &p ) {
    output << "Program: [\n";

    for (auto const &p : p.pipelines)
      output << "\n" << p << "\n";

    output << "\n]";

    return output;
  }

};

/* A parser forms meaningful expressions from a series of tokens
 */
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

  /**
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
   * Checks the type of the current token against a list
   *
   * @param  types  A list of types to compare with
   * @return        Whether the current token is of a type in types
   */
  bool match(std::vector<Token::Type> types) {
    for (auto t : types)
      if (peek().getType() == t)
        return true;

    return false;
  }

  /**
   * Parses a redirection instance
   *
   * @return  A list of redirections
   */
  std::vector<Redirection> redirection() {
    std::vector<Redirection> redirections;

    // TODO: add IO_NUMBER support
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

  /**
   * Parses a command instance
   *
   * @return  A command
   */
  Command command() {
    std::vector<Redirection> prefix = redirection();

    std::vector<Token> elements;

    while (match({Token::Type::TOKEN})) {
      elements.push_back(advance());
    }

    std::vector<Redirection> suffix = redirection();

    return Command(prefix, elements, suffix);
  }

  /**
   * Parses a pipeline instance
   *
   * @return A pipeline
   */
  Pipeline pipeline() {
    std::vector<Command> commands;

    Command c = command();
    commands.push_back(c);

    while (match({Token::Type::PIPE})) {
      advance(); // skip a |

      if (match({Token::Type::TOKEN}))
        commands.push_back(command());
      else
        throw(Parser::Exception(Error("Expected a command after |", peek().getLine(), peek().getStart())));
    }

    return Pipeline(commands);
  }

public:
  /**
   * @param  source  The source input
   * @return         A new parser instance
   */
  explicit Parser(std::string source)
    : source(source), scanner(Scanner(source)) { }

  // An exception to throw in case of a parsing error
  class Exception : std::exception {
    Error error; // The parsing error

  public:
    /**
     * @return  A new parsing exception
     */
    explicit Exception(Error error) : error(error) { }

    Error getError() {
      return error;
    }
  };

  /**
   * Parse and run the input
   *
   * @return  A new program instance
   */
  Program parse() {
    std::vector<Pipeline> pipelines;

    try {

      tokens = scanner.scanTokens();
      Pipeline pipe = pipeline();

      // TODO: Use a base Shell::Exception class

      pipelines.push_back(pipe);

      while (match({Token::Type::SEMI, Token::Type::NEWLINE})) {
        advance(); // skip a ; or a \n

        while (match({Token::Type::SEMI, Token::Type::NEWLINE}))
          advance();  // Skip repeated ; or \n

        if (match({Token::Type::TOKEN}))
          pipelines.push_back(pipeline());
        else {
          std::cout << "<<: " << peek();
          throw(Parser::Exception(Error("Expected a pipeline after ;", peek().getLine(), peek().getStart())));
        }
      }

    } catch (const Scanner::Exception &e) {
      std::cout << e.msg;
      return Program({});
    } catch (Parser::Exception &e) {
      std::cout << e.getError().getMsg();
      return Program({});
    }

    return Program(pipelines);
  }
};

} // namespace uofmsh

#endif
