// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.cpp"

SCENARIO("Scanning input") {

  GIVEN("A scanner and input") {
    std::string input = " ( ) { } ; : < << > >> ! !! & && | ||"
                        "# a comment\n"
                        "ruby -w --debug program < input >> output "
                        " \\ ' single quotes ' \" double  quotes \" "
                        " ` backticks ` ";

    uofmsh::Scanner scanner(input);

    WHEN("The scanner scans the input") {
      auto tokens = scanner.scanTokens();

      THEN("It tokenizes the input correctly") {
        REQUIRE(tokens[0].getType() == uofmsh::Shell::TokenType::LEFT_PAREN);
        REQUIRE(tokens[0].getLexeme() == "(");

        REQUIRE(tokens[1].getType() == uofmsh::Shell::TokenType::RIGHT_PAREN);
        REQUIRE(tokens[1].getLexeme() == ")");

        REQUIRE(tokens[2].getType() == uofmsh::Shell::TokenType::LEFT_BRACE);
        REQUIRE(tokens[2].getLexeme() == "{");

        REQUIRE(tokens[3].getType() == uofmsh::Shell::TokenType::RIGHT_BRACE);
        REQUIRE(tokens[3].getLexeme() == "}");

        REQUIRE(tokens[4].getType() == uofmsh::Shell::TokenType::SEMI);
        REQUIRE(tokens[4].getLexeme() == ";");

        REQUIRE(tokens[5].getType() == uofmsh::Shell::TokenType::COLON);
        REQUIRE(tokens[5].getLexeme() == ":");

        REQUIRE(tokens[6].getType() == uofmsh::Shell::TokenType::REDIRECT_LEFT);
        REQUIRE(tokens[6].getLexeme() == "<");

        REQUIRE(tokens[7].getType() == uofmsh::Shell::TokenType::DREDIRECT_LEFT);
        REQUIRE(tokens[7].getLexeme() == "<<");

        REQUIRE(tokens[8].getType() == uofmsh::Shell::TokenType::REDIRECT_RIGHT);
        REQUIRE(tokens[8].getLexeme() == ">");

        REQUIRE(tokens[9].getType() == uofmsh::Shell::TokenType::DREDIRECT_RIGHT);
        REQUIRE(tokens[9].getLexeme() == ">>");

        REQUIRE(tokens[10].getType() == uofmsh::Shell::TokenType::BANG);
        REQUIRE(tokens[10].getLexeme() == "!");

        REQUIRE(tokens[11].getType() == uofmsh::Shell::TokenType::BANGBANG);
        REQUIRE(tokens[11].getLexeme() == "!!");

        REQUIRE(tokens[12].getType() == uofmsh::Shell::TokenType::AND);
        REQUIRE(tokens[12].getLexeme() == "&");

        REQUIRE(tokens[13].getType() == uofmsh::Shell::TokenType::AND_IF);
        REQUIRE(tokens[13].getLexeme() == "&&");

        REQUIRE(tokens[14].getType() == uofmsh::Shell::TokenType::PIPE);
        REQUIRE(tokens[14].getLexeme() == "|");

        REQUIRE(tokens[15].getType() == uofmsh::Shell::TokenType::OR_IF);
        REQUIRE(tokens[15].getLexeme() == "||");

        REQUIRE(tokens[16].getType() == uofmsh::Shell::TokenType::NEWLINE);
        REQUIRE(tokens[16].getLexeme() == "\n");

        REQUIRE(tokens[17].getType() == uofmsh::Shell::TokenType::TOKEN);
        REQUIRE(tokens[17].getLexeme() == "ruby");

        REQUIRE(tokens[18].getType() == uofmsh::Shell::TokenType::TOKEN);
        REQUIRE(tokens[18].getLexeme() == "-w");

        REQUIRE(tokens[19].getType() == uofmsh::Shell::TokenType::TOKEN);
        REQUIRE(tokens[19].getLexeme() == "--debug");

        REQUIRE(tokens[20].getType() == uofmsh::Shell::TokenType::TOKEN);
        REQUIRE(tokens[20].getLexeme() == "program");

        REQUIRE(tokens[21].getType() == uofmsh::Shell::TokenType::REDIRECT_LEFT);
        REQUIRE(tokens[21].getLexeme() == "<");

        REQUIRE(tokens[22].getType() == uofmsh::Shell::TokenType::TOKEN);
        REQUIRE(tokens[22].getLexeme() == "input");

        REQUIRE(tokens[23].getType() == uofmsh::Shell::TokenType::DREDIRECT_RIGHT);
        REQUIRE(tokens[23].getLexeme() == ">>");

        REQUIRE(tokens[24].getType() == uofmsh::Shell::TokenType::TOKEN);
        REQUIRE(tokens[24].getLexeme() == "output");

        REQUIRE(tokens[25].getType() == uofmsh::Shell::TokenType::BACKSLASH);
        REQUIRE(tokens[25].getLexeme() == "\\");

        REQUIRE(tokens[26].getType() == uofmsh::Shell::TokenType::SINGLE_QUOTED_STR);
        REQUIRE(tokens[26].getLexeme() == " single quotes ");

        REQUIRE(tokens[27].getType() == uofmsh::Shell::TokenType::DOUBLE_QUOTED_STR);
        REQUIRE(tokens[27].getLexeme() == " double  quotes ");

        REQUIRE(tokens[28].getType() == uofmsh::Shell::TokenType::BACKTICK_STR);
        REQUIRE(tokens[28].getLexeme() == " backticks ");

        REQUIRE(tokens[29].getType() == uofmsh::Shell::TokenType::END);
        REQUIRE(tokens[29].getLexeme() == "END");
      }
    }
  }
}
