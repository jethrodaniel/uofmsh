#include "uofmsh.hpp"

namespace uofmsh {

bool Shell::hadError = false;

// Entry point for our shell
int Shell::main(int argc, char **argv) {

  if (argc > 2) {
    std::cout << "Usage: uofmsh [script]\n";
    exit(64);
  } else if (argc == 2) {
    std::cout << "running script " << argv[1] << "\n";
    runFile(std::string(argv[1]));
  } else {
    std::cout << "interactive\n";
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
    std::cout << parser.parse(true) << "\n";
    // Interpreter interpreter(parser.parser());
  } catch (const Scanner::Exception e) {
    error(e.line, e.start, e.msg);
  } catch (Parser::Exception e) {
    error(e.getError());
  }
}

void Shell::error(Error e) {
  Shell::report(e.getLine(), e.getColumn(), e.getMsg());
  Shell::hadError = true;
}

void Shell::error(int line, int column, std::string msg) {
  Shell::report(line, column, msg);
  Shell::hadError = true;
}

void Shell::report(int line, int column, std::string msg) {
  std::cerr << "Error: [" << line << "," << column << "] " << msg << "\n";
}

} // namespace uofmsh

