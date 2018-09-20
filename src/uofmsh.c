#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

#define SUCCESS_CODE 0
#define MAX_LINE_LENGTH 255

int main()
{
  // Prompt for the shell
  char *prompt = "uofmsh> ";

  // The line to be read from input
  char line[MAX_LINE_LENGTH];

  // Print the prompt before reading input
  printf("%s", prompt);

  // Use `fgets` to get the next line
  if (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
      // printf("line: %s\n", line);
  }

  return SUCCESS_CODE;
}
