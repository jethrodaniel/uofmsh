# Makefile for this project

# Compliler options
CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

# Valgrind memory-checking options
VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1

# Default rule, will run when make is called with no arguments
default: test clean

test: tests.out
	@echo "Running helper tests ..."
	@./tests.out

memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: test/test_helpers.c src/helpers.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/helpers.c vendor/Unity/src/unity.c test/test_helpers.c -o tests.out
