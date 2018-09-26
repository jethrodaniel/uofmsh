#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// Allocates memory for a string (upto 256 characters), then returns a pointer
// to the string. The client should call free() on the returned pointer.
char *something(void)
{
    char *string = malloc(256);

    strcpy(string, "something");

    return string;
}
