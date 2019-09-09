#include "vodka.hpp"

namespace vodka {

// Entry point for our shell
int Shell::main(int argc, char **argv) {

  if (argc > 2) {
    std::cout << "Usage: vodka [script]\n";
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

  // init the repl
  replxx::Replxx repl;

  // the path to the history file
  std::string history_file {"./.vodka_history"};

  // load the history file if it exists
  repl.history_load(history_file);

  // set the max history size
  repl.set_max_history_size(128);

  // set the max number of hint rows to show
  repl.set_max_hint_rows(3);

  // @todo - add a verbose `--welcome` flag
  // std::cout
  //   << "vodka\n"
  //   << "Press 'tab' to view autocompletions\n"
  //   << "Type 'help' for help\n"
  //   << "Type 'quit' or 'exit' to exit\n\n";

  // set the repl prompt
  std::string prompt {"\x1b[1;32mvodka\x1b[0m> "};

  // main repl loop
  while (true) {
    // display the prompt and retrieve input from the user
    char const* cinput{nullptr};

    do {
      cinput = repl.input(prompt);
    } while ((cinput == nullptr) && (errno == EAGAIN));

    if (cinput == nullptr)
      break;

    // change cinput into a std::string
    // easier to manipulate
    std::string input {cinput};

    if (input.empty()) {
      // user hit enter on an empty line
      continue;

    } else if (input.compare(0, 5, "quit") == 0 || input.compare(0, 5, "exit") == 0) {
      // exit the repl
      repl.history_add(input);
      break;
    } else if (input.compare(0, 5, "help") == 0) {
      // display the help output
      std::cout
        << "These shell commands are defined internally.\n"
        << "Type `help` to see this list.\n"
        << "Type `help name` to find out more about the function `name` (@todo).\n"
        << "\n"
        << "help              displays the help output"
        << "quit/exit         exit the repl\n"
        << "clear             clears the screen\n"
        << "history           displays the history\n"
        << "prompt <str>      set the repl prompt to <str> (@todo)\n"
        << "\n";

      repl.history_add(input);
      continue;
    } else if (input.compare(0, 7, "prompt") == 0) {
      // set the repl prompt text
      auto pos = input.find(" ");

      if (pos == std::string::npos)
        std::cout << "Error: 'prompt' missing argument\n";
      else
        prompt = input.substr(pos + 1) + " ";

      repl.history_add(input);
      continue;
    } else if (input.compare(0, 8, "history") == 0) {
      // display the current history
      for (size_t i = 0, sz = repl.history_size(); i < sz; ++i)
        std::cout << std::setw(4) << i << ": " << repl.history_line(i) << "\n";

      repl.history_add(input);
      continue;
    } else if (input.compare(0, 6, "clear") == 0) {
      // clear the screen
      repl.clear_screen();

      repl.history_add(input);
      continue;
    } else {
      // default action
      run(input);
      repl.history_add(input);
      continue;
    }
  }

  // save the history
  repl.history_save(history_file);

  /* std::cout << "\nExiting vodka\n"; */

  // while (true) {
  //   std::cout << "vodka> ";

  //   std::string line;
  //   std::getline(std::cin >> std::ws, line);

  //   run(line);

  //   Shell::hadError = false;
  // }
}

// Run a string of input
void Shell::run(std::string source) {
  try {
    Parser parser(source);
    interpreter.interpret(parser.parse(true));
  } catch (Error &e) {
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

} // namespace vodka

