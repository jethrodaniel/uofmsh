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
	@echo "  clean       Removes any generated files. (all=true) to rm ./.test.out"
	@echo "  test        Runs the helper tests"
	@echo "  cucumber    Runs the aruba/cucumber tests"
	@echo

.PHONY: clean
clean:
ifneq (${all},'true')
	@echo "Removing any generated files, except for ./.test.out"
	rm -rf *.o $(PROGRAM_NAME) tmp
else
	@echo "Removing all generated files"
	rm -rf *.o *.out $(PROGRAM_NAME) tmp .test.out .setup.o
endif

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
	bundle --quiet

gem: ruby
ifeq ( , $(shell which bundle))
	gem install bundle
endif

ruby:
ifeq ( , $(shell which ruby))
	$(error Please install Ruby to run the aruba/cucumber tests)
endif
