#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "uofmsh.hpp"
#include "parser.hpp"

namespace uofmsh {

// Represents an interpreter, which executes an abstract syntax tree
class Interpreter {
  // Readable names for pipe read and write ends
  static const auto PIPE_READ  = 0,
                    PIPE_WRITE = 1;

  // Options to pass to open
  static const auto OPEN_OUT_FLAGS = O_WRONLY | O_TRUNC | O_CREAT,
                    OPEN_OUT_MODE  = S_IRUSR  | S_IRGRP | S_IWGRP | S_IWUSR;

  // Converts a list of command elements into a format suitable
  // for execv, execvp, or execvpe
  //
  // @param  elements  A list of command elements
  // @return           The list, as a char**, for use with execv
  char **getExecArgs(std::vector<Token> elements) const {
    auto args = new char*[elements.size() + 1];

    for (unsigned int i = 0; i < elements.size(); i++)
      args[i] = strdup(elements[i].getLexeme().c_str());

    args[elements.size()] = NULL; // Must be NULL-terminated

    return args;
  }

  // Displays a message and exits a process on error
  //
  // @param  msg  The message to print
  void die(std::string msg) const {
    perror(msg.c_str());
    _exit(EXIT_FAILURE);
  }

  // Execute a single redirection
  //
  // @param  r  The redirection to execute
  void redirect(Redirection r) const {
    auto type = r.getRedirectionOp().getType();

    auto filename = r.getFilename().getLexeme().c_str();

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
  //
  // @param  command  The command whose redirections will be executed
  void redirections(Command command) const {
    // Return if no redirections
    if (command.getPrefix().size() + command.getSuffix().size() == 0)
      return;

    // Combine prefix and suffix
    auto redirections = command.getPrefix();
    for (auto r : command.getSuffix())
      redirections.push_back(r);

    // Execute each redirection
    for (auto r : redirections)
      redirect(r);
  }

  // Execute a sequence of piped commands
  //
  // @param  pipeline  The pipeline to execute
  void pipeline(Pipeline pipeline) const {
    auto commands = pipeline.getCommands();

    // Each pipe is represented by an int[2]
    std::vector<int[2]> pipes(commands.size() - 1);

    // Initialize all the pipes
    for (auto p : pipes)
      if (pipe(p) < 0)
        die("Bad pipe");

    int status; // The status of a process, updated by wait
    pid_t pid;  // Holds a process id, used by fork

    // For each command in a pipeline, connect its stdout to the stdin
    // of the next command, and its stdin from the previous command, except
    // for the first and last commands.
    for (unsigned int i = 0; i < commands.size(); i++) {
      // Run each command as a child process
      if ((pid = fork()) == -1)
        die("Bad fork. Exiting.");
      else if (pid == 0) {
        // If not the first command, then get input from last pipe
        if (i != 0)
          if ((dup2(pipes[i - 1][PIPE_READ], STDIN_FILENO) < 0))
            die("Bad dup.");

        // If not the last command, then write output to the next pipe
        if (i != commands.size() - 1)
          if ((dup2(pipes[i][PIPE_WRITE], STDOUT_FILENO) < 0))
            die("Bad dup.");

        // Close all pipe ends from the child process
        for (auto p : pipes)
          for (int i = 0; i < 2; i++)
            close(p[i]);

        // Execute any redirections
        redirections(commands[i]);

        // Run the command
        auto args = getExecArgs(commands[i].getElements());
        execvp(args[0], args);
        die("Bad exec. Exiting.");
      }
    }

    // Close all pipe ends from the parent
    for (auto p : pipes)
      for (int i = 0; i < 2; i++)
        close(p[i]);

    // In the parent, wait for all commands to finish executing
    for (auto c : commands)
      if (wait(&status) < 0)
        die("Bad wait. Exiting.");
  }

public:
  // @return  A new interpreter instance
  explicit Interpreter() { }

  // Interpret and run the AST
  //
  // @param  program  The program or AST to execute
  void interpret(Program program) const {
    auto pipelines = program.getPipelines();

    if (pipelines.size() == 0)
      return;

    for (auto p : pipelines)
      pipeline(p);
  }

};

} // namespace uofmsh

#endif
