#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define MAX_LINE_LENGTH   255
#define PROMPT            "uofmsh> "
#define WHITESPACE_DELIMS " \t"

int shell_loop()
{
  // The line to be read from input
  char line[MAX_LINE_LENGTH];

  // Read commands until the shell is exited via exit or an interrupt
  while (true) {
      // Print the prompt before user input
      printf("%s", PROMPT);

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
        // printf("%i: %s ", i, tokens[i]);
      }

      // Break out of input loop if command is exit
      if (strcmp("exit\n", line) == 0) {
        printf("exit");
        break;
      }
  }

  return EXIT_SUCCESS;
}

int main()
{
  shell_loop();
}
