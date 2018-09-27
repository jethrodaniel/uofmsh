// Tests for any helper functions

// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

// Our helpers
#include "../src/helpers.cpp"

TEST_CASE("\"example\" is returned") {
    REQUIRE(example() == "example");
}
