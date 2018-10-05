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
  (void)source;
  // Scanner scanner(source);

  // auto tokens = scanner.scanTokens();

  // for (const auto &t : tokens)
  //   std::cout << t << "\n";

}

void Shell::error(int line, std::string message) {
  Shell::report(line, "", message);
}

void Shell::report(int line, std::string where, std::string message) {
  std::cerr << "[line " << line << "] Error" << where << ": " + message;
  Shell::hadError = true;
}

} // namespace uofmsh

