#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define MAX_LINE_LENGTH   255
#define PROMPT            "uofmsh> "
#define WHITESPACE_DELIMS " \t"

int main()
{
  // The line to be read from input
  char line[MAX_LINE_LENGTH];

  bool newline_only = false;

  while (!newline_only) {
    printf("%s", PROMPT);

    // Use fgets to save the next line of input in line
    fgets(line, sizeof line, stdin);

    // Exit if command is exit
    if (strcmp("exit\n", line) == 0) {
      printf("exit");
      newline_only = true;
    }

  }

  return EXIT_SUCCESS;
}
