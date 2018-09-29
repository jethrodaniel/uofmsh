// Tests for any helper functions

// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

// Our helpers
#include "../src/helpers.cpp"

TEST_CASE("Splitting a string by a delimiter") {
  std::string input;
  std::vector<std::string> words;

  GIVEN("A regular string") {
    input = "veni,vidi,vici";
    words = uofmsh::split(input, ',');

    THEN("It splits by the delimiter") {
      REQUIRE(words.size() == 3);

      REQUIRE(words[0] == "veni");
      REQUIRE(words[1] == "vidi");
      REQUIRE(words[2] == "vici");
    }
  }

  GIVEN("A single character empty string") {
    input = "";
    words = uofmsh::split(input, ' ');

    THEN("It collects nothing") {
      REQUIRE(words.size() == 0);
    }
  }

  GIVEN("A large empty string") {
    input = "               ";
    words = uofmsh::split(input, ' ');

    THEN("It collects nothing") {
      REQUIRE(words.size() == 0);
    }
  }
}

TEST_CASE("Trimming a string of by a group of delimiters") {
  std::string str, trimmed;

  GIVEN("A string with spaces on the left") {
    str      = "   space on the left";
    trimmed  = "space on the left";

    uofmsh::trim(str, "\n\t ");

    THEN("It removes the leading spaces") {
      REQUIRE(str.compare(trimmed) == 0);
    }
  }

  GIVEN("A string with $'s on the right") {
    str     = "cash$$$$$$";
    trimmed = "cash";

    uofmsh::trim(str, "$");

    THEN("It removes the trailing $'s") {
      REQUIRE(str.compare(trimmed) == 0);
    }
  }

  GIVEN("A string surrounded by spaces") {
    str     = "    doggos     ";
    trimmed = "doggos";

    uofmsh::trim(str, " ");

    THEN("It removes the spaces") {
      REQUIRE(str.compare(trimmed) == 0);
    }
  }


}
