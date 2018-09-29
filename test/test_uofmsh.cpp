// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.cpp"

SCENARIO("Setting the shell prompt") {

  GIVEN("A shell instance") {
    std::string prompt;

    WHEN("A shell created with a prompt") {
      prompt = "~> ";
      uofmsh::Shell shell(prompt);

      THEN("It has the supplied prompt") {
        REQUIRE(shell.getPrompt().compare(prompt) == 0);
      }
    }

    WHEN("A shell created without a prompt") {
      uofmsh::Shell shell;

      THEN("It has a default prompt") {
        REQUIRE(shell.getPrompt().size() > 0);
      }
    }
  }
}

SCENARIO("Adding commands to the shell") {

  GIVEN("A shell instance") {
    std::vector<std::string> commands;

    WHEN("Given input") {
      uofmsh::Shell shell;
      auto input = " \tuptime -p > file; date; fortune | cowsay";

      commands = { "uptime -p > file", "date", "fortune | cowsay" };

      shell.parse(input);

      THEN("The shell can parse the input") {
        REQUIRE(shell.getCommands() == commands);
      }
    }

    WHEN("Commands are added") {
      uofmsh::Shell shell;

      commands = { "uptime -p > file", "date", "fortune | cowsay" };

      REQUIRE(shell.getCommands().size() == 0);

      for (auto c : commands)
        shell.addCommand(c);

      THEN("Then the shell has those commands") {
        REQUIRE(shell.getCommands() == commands);
      }
    }
  }
}
