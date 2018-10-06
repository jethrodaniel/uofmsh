// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.hpp"

// SCENARIO("Setting the shell prompt") {
//
//   GIVEN("A shell instance") {
//
//     WHEN("A shell is created with a prompt") {
//       const std::string prompt = "~> ";
//       uofmsh::Shell shell(prompt);
//
//       THEN("It has the supplied prompt") {
//         REQUIRE(shell.getPrompt().compare(prompt) == 0);
//       }
//     }
//
//     WHEN("A shell is created without a prompt") {
//       uofmsh::Shell shell;
//
//       THEN("It has a default prompt") {
//         REQUIRE(shell.getPrompt().size() > 0);
//       }
//     }
//   }
// }
