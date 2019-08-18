CPP = g++-8

CPP_FLAGS  = -std=c++17
CPP_FLAGS += -g
CPP_FLAGS += -pedantic
CPP_FLAGS += -Wall
CPP_FLAGS += -Wextra
CPP_FLAGS += -Werror

spec_FLAGS  = -std=c++17
spec_FLAGS += -Wall
spec_FLAGS += -I./spec/Catch2

PROGRAM_NAME = vodka

SOURCES    := $(shell find src -name '*.cpp')
spec_SETUP := './spec/setup.cpp'
specS      := $(shell find ./spec -name '*.cpp'            \
                                  -not -path '*Catch2*'    \
                                  -not -name "*setup.cpp")

.PHONY: usage
usage:
	@echo "Usage\n"
	@echo "  make COMMAND"
	@echo "\nCOMMANDS\n"
	@echo "  build       Compiles the source code into an executable"
	@echo "  clean       Removes generated files, except .setup.o and .spec.out"
	@echo "  cucumber    Runs the aruba/cucumber specs"
	@echo "  lint        Runs the linter"
	@echo "  style       Formats source and spec files to adhere to project standards"
	@echo "  spec        Runs the specs"
	@echo "  purge       Removes all generated files"
	@echo

.PHONY: build
build:
	@echo "Compiling source code into ./$(PROGRAM_NAME)"
	@$(CPP) $(CPP_FLAGS) $(SOURCES) -o $(PROGRAM_NAME)

.PHONY: clean
clean:
	@echo "Removing generated files, except .setup.o and .spec.out"
	rm -rf $(PROGRAM_NAME) tmp

.PHONY: cucumber
cucumber: build bundle
	@echo "Running cli specs"
	bundle exec cucumber

bundle: gem
	bundle

gem: ruby
ifeq ( , $(shell which bundle))
	gem install bundle
endif

ruby:
ifeq ( , $(shell which ruby))
	$(error Please install Ruby to run the aruba/cucumber specs)
endif

.PHONY: lint
lint:
	@echo "Running the linter"
ifeq ( , $(shell which cppcheck))
	$(error Please install cppcheck to run the linter)
else
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES)
endif

PHONY: style
style:
ifeq ( , $(shell which astyle))
	$(error Please install astyle to run the formatter)
else
	@echo "Formating source and spec files"
	astyle --project=.astylerc $(SOURCES) $(specS)
endif

.PHONY: spec
spec: .spec.out
	@echo "Running the specs..."
	./.spec.out

.spec.out: .setup.o $(specS)
	$(CPP) $(spec_FLAGS) .setup.o $(specS) -o .spec.out

.setup.o:
	$(CPP) $(spec_FLAGS) -c $(spec_SETUP) -o .setup.o

PHONY: purge
purge:
	@echo "Removing all generated files"
	rm -rf $(PROGRAM_NAME) tmp *.o *.out .spec.out .setup.o

