#include <iostream>

#include "uofmsh.hpp"
#include "helpers.hpp"

namespace uofmsh {

// User input loop
int Shell::start() {
  // The line to be read from input
  std::string input;

  bool reading_input = true;

  // Read commands until the shell is exited via exit or an interrupt
  while (reading_input) {
    // Print the prompt first
    std::cout << this->prompt;

    // Get user input
    std::getline(std::cin >> std::ws, input);

    auto commands = split(input, ' ');

    for (auto i = commands.begin(); i != commands.end(); i++) {
      auto element = *i;
      auto index = i - commands.begin();
      std::cout << index << ": " << element << "\n";
    }

    // Break out of input loop if command is exit
    if (input.compare("exit") == 0) {
      std::cout << "exit" << "\n";
      reading_input = false;
    }
  }

  return EXIT_SUCCESS;
}

} // namespace uofmsh

