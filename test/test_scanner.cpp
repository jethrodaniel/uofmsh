// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"

SCENARIO("Scanning input") {

  GIVEN("A scanner and input") {
    std::string input = " ( ) { } ; : < << > >> ! !! & && | ||"
                        "# a comment\n"
                        "ruby -w --debug program < input >> output "
                        " \\ ' single quotes ' \" double  quotes \" "
                        " ` backticks ` "
                        " 123< 123<<  321>  321>>"
                        "  /slashes/are/just/words  ";

    uofmsh::Scanner scanner(input);

    WHEN("The scanner scans the input") {
      auto tokens = scanner.scanTokens();

      THEN("It tokenizes the input correctly") {
        REQUIRE(tokens[0].getType() == uofmsh::Token::Type::LEFT_PAREN);
        REQUIRE(tokens[0].getLexeme() == "(");

        REQUIRE(tokens[1].getType() == uofmsh::Token::Type::RIGHT_PAREN);
        REQUIRE(tokens[1].getLexeme() == ")");

        REQUIRE(tokens[2].getType() == uofmsh::Token::Type::LEFT_BRACE);
        REQUIRE(tokens[2].getLexeme() == "{");

        REQUIRE(tokens[3].getType() == uofmsh::Token::Type::RIGHT_BRACE);
        REQUIRE(tokens[3].getLexeme() == "}");

        REQUIRE(tokens[4].getType() == uofmsh::Token::Type::SEMI);
        REQUIRE(tokens[4].getLexeme() == ";");

        REQUIRE(tokens[5].getType() == uofmsh::Token::Type::COLON);
        REQUIRE(tokens[5].getLexeme() == ":");

        REQUIRE(tokens[6].getType() == uofmsh::Token::Type::REDIRECT_LEFT);
        REQUIRE(tokens[6].getLexeme() == "<");

        REQUIRE(tokens[7].getType() == uofmsh::Token::Type::DREDIRECT_LEFT);
        REQUIRE(tokens[7].getLexeme() == "<<");

        REQUIRE(tokens[8].getType() == uofmsh::Token::Type::REDIRECT_RIGHT);
        REQUIRE(tokens[8].getLexeme() == ">");

        REQUIRE(tokens[9].getType() == uofmsh::Token::Type::DREDIRECT_RIGHT);
        REQUIRE(tokens[9].getLexeme() == ">>");

        REQUIRE(tokens[10].getType() == uofmsh::Token::Type::BANG);
        REQUIRE(tokens[10].getLexeme() == "!");

        REQUIRE(tokens[11].getType() == uofmsh::Token::Type::BANGBANG);
        REQUIRE(tokens[11].getLexeme() == "!!");

        REQUIRE(tokens[12].getType() == uofmsh::Token::Type::AND);
        REQUIRE(tokens[12].getLexeme() == "&");

        REQUIRE(tokens[13].getType() == uofmsh::Token::Type::AND_IF);
        REQUIRE(tokens[13].getLexeme() == "&&");

        REQUIRE(tokens[14].getType() == uofmsh::Token::Type::PIPE);
        REQUIRE(tokens[14].getLexeme() == "|");

        REQUIRE(tokens[15].getType() == uofmsh::Token::Type::OR_IF);
        REQUIRE(tokens[15].getLexeme() == "||");

        REQUIRE(tokens[16].getType() == uofmsh::Token::Type::NEWLINE);
        REQUIRE(tokens[16].getLexeme() == "\n");

        REQUIRE(tokens[17].getType() == uofmsh::Token::Type::TOKEN);
        REQUIRE(tokens[17].getLexeme() == "ruby");

        REQUIRE(tokens[18].getType() == uofmsh::Token::Type::TOKEN);
        REQUIRE(tokens[18].getLexeme() == "-w");

        REQUIRE(tokens[19].getType() == uofmsh::Token::Type::TOKEN);
        REQUIRE(tokens[19].getLexeme() == "--debug");

        REQUIRE(tokens[20].getType() == uofmsh::Token::Type::TOKEN);
        REQUIRE(tokens[20].getLexeme() == "program");

        REQUIRE(tokens[21].getType() == uofmsh::Token::Type::REDIRECT_LEFT);
        REQUIRE(tokens[21].getLexeme() == "<");

        REQUIRE(tokens[22].getType() == uofmsh::Token::Type::TOKEN);
        REQUIRE(tokens[22].getLexeme() == "input");

        REQUIRE(tokens[23].getType() == uofmsh::Token::Type::DREDIRECT_RIGHT);
        REQUIRE(tokens[23].getLexeme() == ">>");

        REQUIRE(tokens[24].getType() == uofmsh::Token::Type::TOKEN);
        REQUIRE(tokens[24].getLexeme() == "output");

        REQUIRE(tokens[25].getType() == uofmsh::Token::Type::BACKSLASH);
        REQUIRE(tokens[25].getLexeme() == "\\");

        REQUIRE(tokens[26].getType() == uofmsh::Token::Type::SINGLE_QUOTED_STR);
        REQUIRE(tokens[26].getLexeme() == " single quotes ");

        REQUIRE(tokens[27].getType() == uofmsh::Token::Type::DOUBLE_QUOTED_STR);
        REQUIRE(tokens[27].getLexeme() == " double  quotes ");

        REQUIRE(tokens[28].getType() == uofmsh::Token::Type::BACKTICK_STR);
        REQUIRE(tokens[28].getLexeme() == " backticks ");

        REQUIRE(tokens[29].getType() == uofmsh::Token::Type::IO_NUMBER);
        REQUIRE(tokens[29].getLexeme() == "123");

        REQUIRE(tokens[30].getType() == uofmsh::Token::Type::REDIRECT_LEFT);
        REQUIRE(tokens[30].getLexeme() == "<");

        REQUIRE(tokens[31].getType() == uofmsh::Token::Type::IO_NUMBER);
        REQUIRE(tokens[31].getLexeme() == "123");

        REQUIRE(tokens[32].getType() == uofmsh::Token::Type::DREDIRECT_LEFT);
        REQUIRE(tokens[32].getLexeme() == "<<");

        REQUIRE(tokens[33].getType() == uofmsh::Token::Type::IO_NUMBER);
        REQUIRE(tokens[33].getLexeme() == "321");

        REQUIRE(tokens[34].getType() == uofmsh::Token::Type::REDIRECT_RIGHT);
        REQUIRE(tokens[34].getLexeme() == ">");

        REQUIRE(tokens[35].getType() == uofmsh::Token::Type::IO_NUMBER);
        REQUIRE(tokens[35].getLexeme() == "321");

        REQUIRE(tokens[36].getType() == uofmsh::Token::Type::DREDIRECT_RIGHT);
        REQUIRE(tokens[36].getLexeme() == ">>");

        REQUIRE(tokens[37].getType() == uofmsh::Token::Type::TOKEN);
        REQUIRE(tokens[37].getLexeme() == "/slashes/are/just/words");

        REQUIRE(tokens[tokens.size() - 1].getType() == uofmsh::Token::Type::END);
        REQUIRE(tokens[tokens.size() - 1].getLexeme() == "END");
      }
    }
  }
}
