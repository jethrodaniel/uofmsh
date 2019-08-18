// Include Catch
#include "../third_party/Catch2/single_include/catch2/catch.hpp"

#include "../src/vodka.hpp"
#include "../src/parser.hpp"

SCENARIO("Using an abstract syntax tree") {

  GIVEN("A Parser and input") {
    std::string input = "> newfile;\n"
                        "cat file1 file2 | wc -l 123>> output";

    vodka::Parser parser(input);

    vodka::Program expected({
      vodka::Pipeline({
        vodka::Command(
          {
            vodka::Redirection(
              vodka::Token(vodka::Token::Type::REDIRECT_RIGHT, ">", 1, 0, 1),
              vodka::Token(vodka::Token::Type::TOKEN, "newfile", 1, 2, 9)
            )
          },
          std::vector<vodka::Token> {},
          std::vector<vodka::Redirection> {}
        )
      }),
      vodka::Pipeline({
        vodka::Command(
          std::vector<vodka::Redirection> {},
          {
            vodka::Token(vodka::Token::Type::TOKEN, "cat", 2, 11, 14),
            vodka::Token(vodka::Token::Type::TOKEN, "file1", 2, 15, 20),
            vodka::Token(vodka::Token::Type::TOKEN, "file2", 2, 21, 26)
          },
          std::vector<vodka::Redirection> { }
        ),
        vodka::Command(
          std::vector<vodka::Redirection> {},
          {
            vodka::Token(vodka::Token::Type::TOKEN, "wc", 2, 29, 31),
            vodka::Token(vodka::Token::Type::TOKEN, "-l", 2, 32, 34)
          },
          {
            vodka::Redirection(
              vodka::Token(vodka::Token::Type::IO_NUMBER, "123", 2, 35, 38),
              vodka::Token(vodka::Token::Type::DREDIRECT_RIGHT, ">>", 2, 38, 40),
              vodka::Token(vodka::Token::Type::TOKEN, "output", 2, 41, 47)
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
