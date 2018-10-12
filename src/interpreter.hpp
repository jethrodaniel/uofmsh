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

  // Exits a process on error
  void die(std::string msg) const {
    perror(msg.c_str());
    _exit(EXIT_FAILURE);
  }

public:
  // @return  A new interpreter instance
  explicit Interpreter() { }

  // void interpretPipeline(Pipeline p) {
  //   // Each pipe is represented by two file descripters
  //   std::vector<int[2]> pipes(p.getCommands().size() - 1);

  //   for (unsigned int i = 0; i < p.getCommands().size(); i++) {
  //     // Connect the stdout of each command to the stdin of the next command,
  //     // except for the last comand

  //     if (i == p.getCommands().size() - 1) {
  //       // last command in this pipeline
  //       // std::cout << "last command in pipeline " << i << ": " << pipelines[i].getCommands()[j];
  //     } else {
  //       // not the last command
  //
  //       // Create the pipe
  //       if (pipe(pipes[i]) == -1) {
  //         auto error = "Pipe " + std::to_string(i) + " failed. Exiting.";
  //         perror(error.c_str());
  //         exit(1);
  //       }
  //     }
  //   }
  // }

  // Runs a simple command without any redirection
  void interpretCommand(Command c) {
    auto elements = c.getElements();

    char **args = new char*[elements.size() + 1];

    for (unsigned int i = 0; i < elements.size(); i++)
      args[i] = strdup(elements[i].getLexeme().c_str());

    args[elements.size()] = NULL; // exec requires a NULL terminator

    pid_t pid;  // Hold the process id of the command to execute
    int status; // The status, updated by wait

    // Run the command as a child process
    if ((pid = fork()) == -1)
      die("Bad fork. Exiting.");
    else if (pid == 0) {
      execvp(args[0], args);
      die("Bad exec. Exiting.");
    } else
      if (wait(&status) < 0)
        die("Bad wait. Exiting.");
  }

  // Interpret and run the AST
  void interpret(Program p) {
    auto pipelines = p.getPipelines();

    if (pipelines.size() == 0)
      return;

    // for (auto p : pipelines)
    //   interpretPipeline(p);

    interpretCommand(p.getPipelines()[0].getCommands()[0]);
  }

};

} // namespace uofmsh

#endif
