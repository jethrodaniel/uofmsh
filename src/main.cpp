#include <string>

#include "uofmsh.hpp"
#include "helpers.hpp"

// Entry point for our shell
int main(int argc, char **argv) {
  // To avoid the unused params warning from gcc, we reference the parmaeter
  char *program_name = argv[argc - argc];

  // To avoid the unused variable warning from gcc, we use the variable
  (void)program_name;

  // Setup a new shell
  uofmsh::Shell shell = uofmsh::Shell("~> ");

  // Start the shell
  return shell.start();
}

