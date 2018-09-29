// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.cpp"

TEST_CASE("Using a shell object") {

  std::string prompt;

  GIVEN("A shell created with a prompt") {
    prompt = "~> ";
    uofmsh::Shell shell(prompt);

    THEN("It has a prompt") {
      REQUIRE(shell.getPrompt().compare(prompt) == 0);
    }
  }

  GIVEN("A shell created without a prompt") {
    uofmsh::Shell shell;

    THEN("It has a default prompt") {
      REQUIRE(shell.getPrompt().size() > 0);
    }
  }

}
