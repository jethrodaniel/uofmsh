// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"
#include "../src/parser.hpp"


SCENARIO("Using == with Redirections") {
  GIVEN("Two Redirections with the same members") {
    uofmsh::Redirection r1(
      uofmsh::Token(uofmsh::Token::Type::REDIRECT_RIGHT, ">", 0, 0, 0),
      uofmsh::Token(uofmsh::Token::Type::TOKEN, "cowsay", 0, 0, 0)
    );

    uofmsh::Redirection r2(
      uofmsh::Token(uofmsh::Token::Type::REDIRECT_RIGHT, ">", 0, 0, 0),
      uofmsh::Token(uofmsh::Token::Type::TOKEN, "cowsay", 0, 0, 0)
    );

    WHEN("== is called with the redirections") {
      THEN("It returns true") {
        REQUIRE((r1 == r2) == true);
      }
    }
  }
}

SCENARIO("Using == with Tokens") {
  GIVEN("Two tokens with the same members") {
    uofmsh::Token t1(uofmsh::Token::Type::TOKEN, "cowsay", 0, 0, 0);
    uofmsh::Token t2(uofmsh::Token::Type::TOKEN, "cowsay", 0, 0, 0);

    WHEN("== is called with the tokens") {
      THEN("It returns true") {
        REQUIRE((t1 == t2) == true);
      }
    }
  }
}

SCENARIO("Using an abstract syntax tree") {

  GIVEN("A Parser and input") {
    std::string input = "> newfile";

    uofmsh::Parser parser(input);

    uofmsh::Program expected({
      uofmsh::Pipeline({
        uofmsh::Command(
          {
            uofmsh::Redirection(
              uofmsh::Token(uofmsh::Token::Type::REDIRECT_RIGHT, ">", 0, 0, 0),
              uofmsh::Token(uofmsh::Token::Type::TOKEN, "filename", 0, 0, 0)
            )
          },
          std::vector<uofmsh::Token> {},
          std::vector<uofmsh::Redirection> {}
        )
      })
    });

    THEN("The parser creates the AST") {
      REQUIRE(parser.parse()
                    .getPipelines().size() == 1);
      REQUIRE(parser.parse()
                    .getPipelines()[0]
                    .getCommands().size() == 1);
      REQUIRE(parser.parse()
                    .getPipelines()[0]
                    .getCommands()[0]
                    .getPrefix().size() == 1);
      REQUIRE(parser.parse()
                    .getPipelines()[0]
                    .getCommands()[0]
                    .getPrefix()[0]
                    .getRedirectionOp()
                    .getType() == uofmsh::Token::Type::REDIRECT_RIGHT);
    }
  }

  // cat --help >> filename
  GIVEN("A list of tokens") {
    uofmsh::Token redirectOp(
      uofmsh::Token::Type::DREDIRECT_RIGHT, ">>", 0, 0, 0);

    uofmsh::Token filename(
      uofmsh::Token::Type::TOKEN, "filename", 0, 0, 0);

    auto elements = {
      uofmsh::Token(uofmsh::Token::Type::TOKEN, "cat", 0, 0, 0),
      uofmsh::Token(uofmsh::Token::Type::TOKEN, "--help", 0, 0, 0)
    };

    THEN("An AST can be created using the tokens") {
      uofmsh::Program program({
        uofmsh::Pipeline({
          uofmsh::Command(
            {  },
            elements,
            { uofmsh::Redirection(redirectOp, filename) }
          )
        })
      });

      REQUIRE(program.getPipelines().size() == 1);

      REQUIRE(program.getPipelines()[0]
                     .getCommands()[0]
                     .getElements()[0].getLexeme() == "cat");
    }
  }
}
