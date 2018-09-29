#ifndef UOFMSH_H
#define UOFMSH_H

namespace uofmsh {

// Represents a shell's data and methods
class Shell {
  std::string prompt;

  public:
    // @return  a new shell instance
    Shell(std::string prompt = "uofmsh> ") {
      this->prompt = prompt;
    }

    // Starts the user input loop
    //
    // @return  the shell's exit status
    int start();

    // @return  this shell's prompt
    const std::string getPrompt() {
      return this->prompt;
    }
};

} // namespace uofmsh

#endif
