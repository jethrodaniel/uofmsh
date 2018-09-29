#ifndef UOFMSH_H
#define UOFMSH_H

#include <algorithm>
#include <string>
#include <vector>

#include "helpers.hpp"

namespace uofmsh {

// Represents a shell's data and methods
class Shell {
  std::string prompt;
  std::vector<std::string> commands;

  public:

    // @return  a new shell instance
    explicit Shell(const std::string &prompt) : prompt(prompt) { }

    Shell() : prompt("uofmsh> ") { }

    // Starts the user input loop
    //
    // @return  the shell's exit status
    int start();

    // @return  this shell's prompt
    const std::string getPrompt() {
      return this->prompt;
    }

    // @return  this shell's commands
    std::vector<std::string> getCommands() {
      return this->commands;
    }

    // Adds a command to this shell
    void addCommand(std::string command) {
      this->commands.push_back(command);
    }

    // Parses input and creates commands
    void parse(std::string input) {
      auto commands = helpers::split(input, ";");

      for (auto &c : commands) {
        helpers::trim(c, " \t");
        addCommand(c);
      }
    }
};

} // namespace uofmsh

#endif
