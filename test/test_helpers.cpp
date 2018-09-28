// Tests for any helper functions

// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

// Our helpers
#include "../src/helpers.cpp"

TEST_CASE("Splitting a string by a set of delimiters") {

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
