// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"
#include "../src/parser.hpp"

SCENARIO("Using an abstract syntax tree") {

  GIVEN("A Parser and input") {
    std::string input = "> newfile; cat file1 file2 | wc -l >> output";

    uofmsh::Parser parser(input);

    // cat file1 file2 | wc -l >> output
    uofmsh::Program expected({
      uofmsh::Pipeline({
        uofmsh::Command(
          {
            uofmsh::Redirection(
              uofmsh::Token(uofmsh::Token::Type::REDIRECT_RIGHT, ">", 1, 0, 1),
              uofmsh::Token(uofmsh::Token::Type::TOKEN, "newfile", 1, 2, 9)
            )
          },
          std::vector<uofmsh::Token> {},
          std::vector<uofmsh::Redirection> {}
        )
      }),
      uofmsh::Pipeline({
        uofmsh::Command(
          std::vector<uofmsh::Redirection> {},
          {
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "cat", 1, 11, 14),
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "file1", 1, 15, 20),
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "file2", 1, 21, 26)
          },
          std::vector<uofmsh::Redirection> { }
        ),
        uofmsh::Command(
          std::vector<uofmsh::Redirection> {},
          {
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "wc", 1, 29, 31),
            uofmsh::Token(uofmsh::Token::Type::TOKEN, "-l", 1, 32, 34)
          },
          {
            uofmsh::Redirection(
              uofmsh::Token(uofmsh::Token::Type::DREDIRECT_RIGHT, ">>", 1, 35, 37),
              uofmsh::Token(uofmsh::Token::Type::TOKEN, "output", 1, 38, 44)
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
