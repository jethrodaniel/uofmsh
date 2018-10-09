// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"
#include "../src/parser.hpp"

SCENARIO("Using == with Programs") {
  GIVEN("Two programs with the same members") {
    uofmsh::Program p1({
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
    }),

    p2({
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

    WHEN("== is called with the pipelines") {
      THEN("It returns true") {
        REQUIRE((p1 == p2) == true);
      }
    }
  }
}

SCENARIO("Using == with Pipelines") {
  GIVEN("Two pipelines with the same members") {
    uofmsh::Pipeline p1({
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
    }),

    p2({
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
    });

    WHEN("== is called with the pipelines") {
      THEN("It returns true") {
        REQUIRE((p1 == p2) == true);
      }
    }
  }
}

SCENARIO("Using == with Commands") {
  GIVEN("Two commands with the same members") {
    uofmsh::Command c1(
      {
        uofmsh::Redirection(
          uofmsh::Token(uofmsh::Token::Type::REDIRECT_RIGHT, ">", 0, 0, 0),
          uofmsh::Token(uofmsh::Token::Type::TOKEN, "filename", 0, 0, 0)
        )
      },
      std::vector<uofmsh::Token> {},
      std::vector<uofmsh::Redirection> {}
    ),

    c2(
      {
        uofmsh::Redirection(
          uofmsh::Token(uofmsh::Token::Type::REDIRECT_RIGHT, ">", 0, 0, 0),
          uofmsh::Token(uofmsh::Token::Type::TOKEN, "filename", 0, 0, 0)
        )
      },
      std::vector<uofmsh::Token> {},
      std::vector<uofmsh::Redirection> {}
    );

    WHEN("== is called with the commands") {
      THEN("It returns true") {
        REQUIRE((c1 == c2) == true);
      }
    }
  }
}

SCENARIO("Using == with Redirections") {
  GIVEN("Two redirections with the same members") {
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
