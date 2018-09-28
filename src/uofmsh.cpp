#include <iostream>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uofmsh.hpp"
#include "helpers.hpp"

// Constants
const int MAX_LINE_LENGTH = 255;
const std::string PROMPT = "uofmsh> ";

const char *WHITESPACE_DELIMS = " \t";

// Main shell user input loop
int shell_loop(void)
{
  // The line to be read from input
  char line[MAX_LINE_LENGTH];

  // Read commands until the shell is exited via exit or an interrupt
  while (true) {
      // Print the prompt before user input
      std::cout << PROMPT;

      // Use fgets to save the next line of input in line
      fgets(line, sizeof line, stdin);

      // Split the current line by whitespace characters, and save in tokens
      char tokens[255][MAX_LINE_LENGTH];

      char *token = strtok(line, WHITESPACE_DELIMS);
      for (int i = 0; token != NULL; i++) {
        strcpy(tokens[i], token);
        token = strtok(NULL, WHITESPACE_DELIMS);
      }

      for (int i = 0; tokens[i][0] != '\0'; i++) {
        printf("%i: %s\n", i, tokens[i]);
      }

      // Break out of input loop if command is exit
      if (strcmp("exit\n", line) == 0) {
        printf("exit");
        break;
      }
  }

  return EXIT_SUCCESS;
}

// Starts the shell
int main(int argc, char **argv)
{
  // To avoid the unused params warning from gcc, we reference the parmaeter
  char *program_name = argv[argc - argc];

  // To avoid the unused variable warning from gcc, we use the variable
  (void)program_name;

  // Start the shell
  return shell_loop();
}
