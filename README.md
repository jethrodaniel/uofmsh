# uofmsh

A basic shell

Supports
* Semicolon separated pipelines
* Redirection (including io numbers)
* Commands
* Builtins: only `cd` and `exit`

For example,
```
~> make
Usage

  make COMMAND

COMMANDS

  build       Compiles the source code into an executable
  clean       Removes generated files, except .setup.o and .test.out
  cucumber    Runs the aruba/cucumber tests
  lint        Runs the linter
  style       Formats source and test files to adhere to project standards
  test        Runs the tests
  purge       Removes all generated files
~> make build
Compiling source code into ./uofmsh
~> ./uofmsh
uofmsh> ls
features  Gemfile  Gemfile.lock  LICENSE  makefile  README.md  src  test  uofmsh
uofmsh> ls | grep Gem | cowsay > cow; foo 2> error; uptime -p
up 6 days, 5 hours, 44 minutes
uofmsh> cat cow
 _____________________
< Gemfile Gemfile.lock >
 ----------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
uofmsh> cat error
Bad exec. Exiting.: No such file or directory
uofmsh> pwd
/home/jethro/school/fall_2018/os/proj1/uofmsh
uofmsh> cd ..
uofmsh> pwd
/home/jethro/school/fall_2018/os/proj1
uofmsh> cd -
uofmsh> pwd
/home/jethro/school/fall_2018/os/proj1/uofmsh
uofmsh> cd /
uofmsh> pwd
/
uofmsh> exit
```

Development Features
* C++ testing with [Catch](https://github.com/catchorg/Catch2)
* Interactive testing using [Aruba](https://github.com/cucumber/aruba) and [Cucumber](https://github.com/cucumber/cucumber-ruby)

## Dependencies
---

### To compile and run the shell

* A C++17 compiler, such as [g++](https://gcc.gnu.org/)

### Additionally, to use the included makefile for project tasks

* [GNU Make](https://www.gnu.org/software/make/)

### Additionally, to run the tests

* [Git](https://git-scm.com/), to add Catch as a submodule
* [Ruby](https://www.ruby-lang.org/en/), to run the Aruba/Cucumber tests. [RVM](https://rvm.io/) is the suggested installation method.

## Installation
---

* Clone the repo or download it
     ```
     git clone https://github.com/jethrodaniel/uofmsh.git
     ```

* Move into the project directory
     ```
     cd uofmsh
     ```

* Create the executable shell
     ```
     make build
     ```

## Development
---

### To show available project commands

```
make
```

### To run the unit tests

* Download Catch, which is included as a submodule
     ```
     git submodule init
     git submodule update
     ```

* Alternatively, you can download all submodules and clone at the same time using
     ```
     git clone --recurse-submodules https://github.com/jethrodaniel/uofmsh.git
     ```

### To run the aruba/cucumber tests

* Also installs the required Ruby gems. Fails if Ruby isn't already installed.
     ```
     make cucumber
     ```

## References

A big thanks to the following

- https://weblog.jamisbuck.org/2015/7/30/writing-a-simple-recursive-descent-parser.html
- http://www.craftinginterpreters.com/
- http://parsingintro.sourceforge.net/
