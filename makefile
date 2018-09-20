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
	@echo "  test         Runs the helper tests, then the cli tests"
	@echo "  clean        Removes any makefile-generated files"
	@echo "  memcheck     Checks memory-usage using valgrind\n"

run: build
	@echo "Running ./$(PROGRAM_NAME)\n"
	@./$(PROGRAM_NAME)
	@echo

build:
	@echo "Compiling source code into ./$(PROGRAM_NAME)\n"
	@$(CC) $(CFLAGS) src/uofmsh.c src/helpers.c -o $(PROGRAM_NAME)

test: _test_helpers _test_cli clean

_test_cli: build
	@echo "Running cli tests"
	bundle exec cucumber

clean:
	@echo "Removing any generated files"
	rm -rf *.o *.out *.out.dSYM $(PROGRAM_NAME)
	@echo

memcheck: _memcheck clean

_memcheck: _tests.out
	@echo "\nRunning memory checks using valgrind ..."
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed\n"

_test_helpers: _tests.out
	@echo "\nRunning helper tests"
	@./tests.out

_tests.out: test/test_helpers.c src/helpers.c
	@echo "\nCompiling $@"
	@$(CC) $(CFLAGS) src/helpers.c vendor/Unity/src/unity.c test/test_helpers.c -o tests.out

