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
};

class Command : public ASTNode {
  std::vector<Redirection> prefix;
  std::vector<Token> elements;
  std::vector<Redirection> suffix;
public:
  std::vector<Redirection> getPrefix() {
    return prefix;
  }
  std::vector<Redirection> getSuffix() {
    return suffix;
  }
  std::vector<Token> getElements() {
    return elements;
  }
  Command(std::vector<Redirection> prefix,
          std::vector<Token> elements,
          std::vector<Redirection> suffix)
    : prefix(prefix), elements(elements), suffix(suffix) { }
};

class Pipeline : public ASTNode {
  std::vector<Command> commands;
public:
  std::vector<Command> getCommands() {
    return commands;
  }
  Pipeline(std::vector<Command> commands) : commands(commands) { }
};

class Program : public ASTNode {
  std::vector<Pipeline> pipelines;
public:
  std::vector<Pipeline> getPipelines() {
    return pipelines;
  }
  Program(std::vector<Pipeline> pipelines) : pipelines(pipelines) { };
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

  /**
   * @return  The current token
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
   * Checks the current token's type against a list
   *
   * @param  types  A list of types to compare with
   * @return  Whether the current token is of a type in types
   */
  bool match(std::vector<Token::Type> types) {
    for (auto t : types)
      if (peek().getType() == t)
        return true;

    return false;
  }

  // Redirection redirection() {
  //   return redirection();
  // }

  // Command command() {
  //   return Command();
  // }

  // Pipeline pipeline() {
  //   Command c = command();
  //   return Pipeline();
  // }

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

  // // Parse and run the input
  // Program parse() {
  //   try {
  //     tokens = scanner.scanTokens();
  //   } catch (const Scanner::Exception e) {
  //     throw;
  //   }

  //   Pipeline pipe = pipeline();

  //   if (!pipe.isValid())
  //     throw(Parser::Exception(pipe.getError()));

  //   return Program({pipe});
  // }
};

} // namespace uofmsh

#endif
