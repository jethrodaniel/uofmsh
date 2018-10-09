// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"
#include "../src/parser.hpp"

SCENARIO("Using an abstract syntax tree") {

  GIVEN("A Parser and input") {
    std::string input = "> newfile newfile";

    uofmsh::Parser parser(input);

    uofmsh::Program expected({
      uofmsh::Pipeline({
        uofmsh::Command(
          {
            uofmsh::Redirection(
              uofmsh::Token(uofmsh::Token::Type::REDIRECT_RIGHT, ">", 1, 0, 1),
              uofmsh::Token(uofmsh::Token::Type::TOKEN, "newfile", 1, 2, 9)
            )
          },
          {
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "newfile", 1, 10, 17)
          },
          std::vector<uofmsh::Redirection> {}
        )
      })
    });

    THEN("The parser creates the AST") {
      auto ast = parser.parse();
      // std::cout << ast.getPipelines()[0].getCommands()[0];
      REQUIRE(ast == expected);
    }
  }
}
