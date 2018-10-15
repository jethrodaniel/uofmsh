#include "uofmsh.hpp"

namespace uofmsh {

// Entry point for our shell
int Shell::main(int argc, char **argv) {

  if (argc > 2) {
    std::cout << "Usage: uofmsh [script]\n";
    exit(64);
  } else if (argc == 2) {
    // std::cout << "running script " << argv[1] << "\n";
    runFile(std::string(argv[1]));
  } else {
    // std::cout << "interactive\n";
    runPrompt();
    exit(0);
  }

  return 0;
}

// Reads a file into a string, then runs the string as input
void Shell::runFile(std::string fileName) {
  std::ifstream ifs(fileName);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  std::string file(buffer.str());

  run(file);

  exit(65);
}

// Reads and executes input interactively
void Shell::runPrompt() {
  while (true) {
    std::cout << "uofmsh> ";

    std::string line;
    std::getline(std::cin >> std::ws, line);

    run(line);

    Shell::hadError = false;
  }
}

// Run a string of input
void Shell::run(std::string source) {
  try {
    Parser parser(source);
    interpreter.interpret(parser.parse(true));
  } catch (Error e) {
    error(e);
  }
}

void Shell::error(Error e) {
  hadError = true;

  std::cerr << "Error: ["
            << e.getLine() << ","
            << e.getColumn() << "] "
            << e.getMsg() << "\n";
}

} // namespace uofmsh

