// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"
#include "../src/parser.hpp"

SCENARIO("Using an abstract syntax tree") {

  GIVEN("A Parser and input") {
    std::string input = "cat file1 file2 | wc -l >> output";

    uofmsh::Parser parser(input);

    // cat file1 file2 | wc -l >> output
    uofmsh::Program expected({
      uofmsh::Pipeline({
        uofmsh::Command(
          std::vector<uofmsh::Redirection> {},
          {
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "cat", 1, 0, 3),
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "file1", 1, 4, 9),
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "file2", 1, 10, 15)
          },
          std::vector<uofmsh::Redirection> { }
        ),
        uofmsh::Command(
          std::vector<uofmsh::Redirection> {},
          {
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "wc", 1, 18, 20),
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "-l", 1, 21, 23)
          },
          {
            uofmsh::Redirection(
              uofmsh::Token(uofmsh::Token::Type::DREDIRECT_RIGHT, ">>", 1, 24, 26),
              uofmsh::Token(uofmsh::Token::Type::TOKEN, "output", 1, 27, 33)
            )
          }
        )
     })
    });

    WHEN("The parser creates the AST") {
      auto ast = parser.parse();

      THEN("The AST is correct") {
        //std::cout << ast;
        REQUIRE(ast == expected);
      }
    }
  }
}
