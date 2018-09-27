CPP = g++

CPP_FLAGS  = -std=c++11
CPP_FLAGS += -g
CPP_FLAGS += -pedantic
CPP_FLAGS += -Wall
CPP_FLAGS += -Wextra
CPP_FLAGS += -Werror

TEST_FLAGS  = -std=c++11
TEST_FLAGS += -Wall
TEST_FLAGS += -I./test/Catch2

PROGRAM_NAME = uofmsh

SOURCES    := $(shell find src -name '*.cpp')
TEST_SETUP := './test/setup.cpp'
TESTS      := $(shell find ./test -name '*.cpp'            \
                                  -not -path '*Catch2*'    \
                                  -not -name "*setup.cpp")

.PHONY: usage
usage:
	@echo "Usage\n"
	@echo "  make COMMAND"
	@echo "\nCOMMANDS\n"
	@echo "  build       Compiles the source code into an executable"
	@echo "  clean       Removes generated files, except .setup.o and .test.out"
	@echo "  cucumber    Runs the aruba/cucumber tests"
	@echo "  test        Runs the helper tests"
	@echo "  purge       Removes all generated files."
	@echo

.PHONY: clean
clean:
	@echo "Removing generated files, except .setup.o and .test.out"
	rm -rf $(PROGRAM_NAME) tmp

.PHONY: purge
purge:
	@echo "Removing all generated files"
	rm -rf $(PROGRAM_NAME) tmp *.o *.out .test.out .setup.o


.PHONY: build
build:
	@echo "Compiling source code into ./$(PROGRAM_NAME)"
	@$(CPP) $(CPP_FLAGS) $(SOURCES) -o $(PROGRAM_NAME)

.PHONY: test
test: .test.out
	@echo "Running the tests..."
	./.test.out

.test.out: .setup.o $(TESTS)
	$(CPP) $(TEST_FLAGS) .setup.o $(TESTS) -o .test.out

.setup.o:
	$(CPP) $(TEST_FLAGS) -c $(TEST_SETUP) -o .setup.o

.PHONY: cucumber
cucumber: build bundle
	@echo "Running cli tests"
	bundle exec cucumber

bundle: gem
	bundle

gem: ruby
ifeq ( , $(shell which bundle))
	gem install bundle
endif

ruby:
ifeq ( , $(shell which ruby))
	$(error Please install Ruby to run the aruba/cucumber tests)
endif
