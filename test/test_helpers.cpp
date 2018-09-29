// Tests for any helper functions

// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

// Our helpers
#include "../src/helpers.cpp"

TEST_CASE("Splitting a string by a string of delimiters") {
  std::string input;
  std::vector<std::string> output;

  GIVEN("A string containing the delimiters") {
    input  = "veni,\nvidi, vici";
    output = uofmsh::split(input, " ,\n");

    THEN("It splits by the delimiters") {
      REQUIRE(output.size() == 3);

      REQUIRE(output[0] == "veni");
      REQUIRE(output[1] == "vidi");
      REQUIRE(output[2] == "vici");
    }
  }

  GIVEN("A string consisting of the delimiters") {
    input  = "!@#$%^&*";
    output = uofmsh::split(input, "!@#$%^&*");

    THEN("It collects nothing") {
      REQUIRE(output.size() == 0);
    }
  }

  GIVEN("An empty string") {
    input  = "";
    output = uofmsh::split(input, " ");

    THEN("It collects nothing") {
      REQUIRE(output.size() == 0);
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

  GIVEN("A string surrounded by whitespace") {
    str     = "\t   doggos\n    \t\f";
    trimmed = "doggos";

    uofmsh::trim(str, " \t\f\n");

    THEN("It removes the whitespace") {
      REQUIRE(str.compare(trimmed) == 0);
    }
  }


}
