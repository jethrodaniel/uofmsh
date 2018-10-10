#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "uofmsh.hpp"
#include "parser.hpp"

namespace uofmsh {

// Represents an interpreter, which executes the abstract syntax tree
class Interpreter {

public:
  // @return  A new interpreter instance
  Interpreter() { }

  // Interpret and run the AST
  void interpret(Program p) {
    auto pipelines = p.getPipelines();

    if (pipelines.size() == 0)
      return;

    for (auto p : pipelines) {
      for (auto c : p.getCommands()) {
        //std::cout << "\n" << c << "\n";
      }
    }

  }
};

} // namespace uofmsh

#endif
