#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "uofmsh.hpp"
#include "parser.hpp"

namespace uofmsh {

// Represents an interpreter, which executes the abstract syntax tree
class Interpreter {

public:
  // Interpret and run the AST
  void interpret(Program p) {
    auto pipelines = p.getPipelines();

    // if (pipelines.size() == 0)
    //   return;
  }
};

} // namespace uofmsh

#endif
