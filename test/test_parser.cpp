// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"
#include "../src/parser.hpp"

SCENARIO("Using an abstract syntax tree") {

  GIVEN("A list of tokens") {
    uofmsh::Token redirectOp(
      uofmsh::Token::Type::DREDIRECT_RIGHT, ">>", 0, 0, 0);

    uofmsh::Token filename(
      uofmsh::Token::Type::TOKEN, "filename", 0, 0, 0);

    auto elements = {
      uofmsh::Token(uofmsh::Token::Type::TOKEN, "cat", 0, 0, 0),
      uofmsh::Token(uofmsh::Token::Type::TOKEN, "--help", 0, 0, 0)
    };

    THEN("An AST can be created manually using the tokens") {
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
