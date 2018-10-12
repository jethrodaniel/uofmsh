#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <algorithm>

#include "uofmsh.hpp"
#include "parser.hpp"


namespace uofmsh {

// Represents an interpreter, which executes the abstract syntax tree
class Interpreter {

  static const auto PIPE_READ  = 0,
                    PIPE_WRITE = 1;

public:
  // @return  A new interpreter instance
  explicit Interpreter() { }

  // Runs a simple command without any redirection
  void interpretCommand(Command c) {
    auto elements = c.getElements();

    char **args = new char*[elements.size() + 1];

    for (unsigned int i = 0; i < elements.size(); i++)
      args[i] = strdup(elements[i].getLexeme().c_str());

    args[elements.size()] = NULL;

    pid_t pid; // Hold the process id of the command to execute

    int status;

    if ((pid = fork()) == -1) {
      perror("Bad fork. Exiting.");
      exit(1);
    } else if (pid == 0) {
      // Run the command as a child process
      execvp(args[0], args);

      perror("Bad exec. Exiting.");
      exit(1);
    } else {
      if (wait(&status) < 0) {
        perror("Bad wait. Exiting.");
        exit(1);
      }
      // Parent finished
    }

  }

  // Interpret and run the AST
  void interpret(Program p) {
    auto pipelines = p.getPipelines();

    if (pipelines.size() == 0)
      return;

    interpretCommand(p.getPipelines()[0].getCommands()[0]);
  }

};

} // namespace uofmsh

#endif
