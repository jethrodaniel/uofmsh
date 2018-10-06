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

void Shell::runFile(std::string fileName) {
  std::ifstream ifs { fileName };
  std::string file {
    std::istreambuf_iterator<char>(ifs),
    std::istreambuf_iterator<char>()
  };

  run(file);

  exit(65);
}

void Shell::runPrompt() {
  while (true) {
    std::cout << "uofmsh> ";

    std::string line;
    std::getline(std::cin >> std::ws, line);

    run(line);

    Shell::hadError = false;
  }
}

void Shell::run(std::string source) {
  Scanner scanner(source);

  auto tokens = scanner.scanTokens();

  std::cout << "Tokens: " << tokens.size() << "\n";

  for (unsigned int i = 0; i < tokens.size(); i++)
    std::cout << i << ": " << tokens[i] << "\n";

}

void Shell::error(int line, int column, std::string msg) {
  Shell::report(line, column, msg);
}

void Shell::report(int line, int column, std::string msg) {
  std::cerr << "Error: [" << line << "," << column << "] " << msg << "\n";
  Shell::hadError = true;
}

} // namespace uofmsh

