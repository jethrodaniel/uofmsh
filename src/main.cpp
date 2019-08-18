#include <iostream>
#include <string>

#include "vodka.hpp"

// Entry point for our shell
int main(int argc, char **argv) {
  vodka::Shell shell;
  return shell.main(argc, argv);
}

