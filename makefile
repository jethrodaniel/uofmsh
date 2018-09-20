# Makefile for this project

# Compliler options
CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

# valgrind memory-checking options
VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1

# Name of the output program
PROGRAM_NAME = uofmsh

# Default rule, will run when make is called with no arguments
default:
	@echo "Usage\n"
	@echo "  make COMMAND"
	@echo "\nCOMMANDS\n"
	@echo "  build        Compiles the source code into an executable"
	@echo "  run          Runs 'build', then runs the executable"
	@echo "  test         Runs the helper tests"
	@echo "  clean        Removes any makefile-generated files"
	@echo "  memcheck     Checks memory-usage using valgrind\n"

run: build
	@echo "Running ./$(PROGRAM_NAME)\n"
	@./$(PROGRAM_NAME)

build:
	@$(CC) $(CFLAGS) src/uofmsh.c src/helpers.c -o $(PROGRAM_NAME)
	@echo "Compiled source code into ./$(PROGRAM_NAME)"

test: _test clean

clean:
	rm -rf *.o *.out *.out.dSYM $(PROGRAM_NAME)
	@echo "Removed any generated files"

memcheck: _memcheck clean

_memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

_test: _tests.out
	@echo "Running helper tests"
	@./tests.out

_tests.out: test/test_helpers.c src/helpers.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/helpers.c vendor/Unity/src/unity.c test/test_helpers.c -o tests.out

