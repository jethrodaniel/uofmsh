#include <iostream>
#include <string>

#include "uofmsh.hpp"

// Entry point for our shell
int main(int argc, char **argv) {
  uofmsh::Shell shell;
  return shell.main(argc, argv);
}

