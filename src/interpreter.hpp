#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <algorithm>

#include "uofmsh.hpp"
#include "parser.hpp"


namespace uofmsh {

// Represents an interpreter, which executes the abstract syntax tree
class Interpreter {

  static const auto PIPE_READ  = 0,
                    PIPE_WRITE = 1;

  static const auto OPEN_OUT_FLAGS = O_WRONLY | O_TRUNC | O_CREAT,
                    OPEN_OUT_MODE  = S_IRUSR  | S_IRGRP | S_IWGRP | S_IWUSR;

  // Exits a process on error
  void die(std::string msg) const {
    perror(msg.c_str());
    _exit(EXIT_FAILURE);
  }

  // Execute a single redirection
  void redirect(Redirection r) {
    auto type = r.getRedirectionOp().getType();

    const char *filename = r.getFilename().getLexeme().c_str();

    int openFile, dup;

    if (type == Token::Type::REDIRECT_RIGHT) {
      // > : Write std out to filename
      openFile = open(filename, OPEN_OUT_FLAGS, OPEN_OUT_MODE);
      dup      = dup2(openFile, 1);
    } else {
      // < : Read input from filename
      openFile = open(filename, O_RDONLY);
      dup      = dup2(openFile, 0);
    }

    if (openFile < 0)
      die("Error opening " + std::string(filename));

    if (dup < 0)
      die("Bad dup2. Exiting.");

    close(openFile);
  }

  // Execute a series of redirections
  void redirections(Command c) {
    if (c.getPrefix().size() + c.getSuffix().size() == 0)
      return;  // Return if no redirections

    // Combine prefix and suffix
    std::vector<Redirection> redirections = c.getPrefix();
    for (auto r : c.getSuffix())
      redirections.push_back(r);

    for (auto r : redirections)
      redirect(r);
  }

  // Runs a single command
  void command(Command c) {
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

      redirections(c);

      execvp(args[0], args);
      die("Bad exec. Exiting.");
    } else
      if (wait(&status) < 0)
        die("Bad wait. Exiting.");
  }

public:
  // @return  A new interpreter instance
  explicit Interpreter() { }

  // Interpret and run the AST
  void interpret(Program p) {
    auto pipelines = p.getPipelines();

    if (pipelines.size() == 0)
      return;

    for (auto p : pipelines)
      command(p.getCommands()[0]);
  }

};

} // namespace uofmsh

#endif
