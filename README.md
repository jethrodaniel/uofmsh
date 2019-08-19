# vodka

[![Build Status](https://travis-ci.com/jethrodaniel/vodka.svg?branch=master)](https://travis-ci.com/jethrodaniel/vodka)

A POSIX shell in c++ (wip)

Supports
* Semicolon separated pipelines
* Redirection (including io numbers)
* Commands
* Builtins: only `cd` and `exit`

For example,
```
λ ./make
Commands:
  make build           # Builds the project
  make clean           # Removes build files
  make clobber         # Removes all generated files
  make cucumber        # Runs the aruba/cucumber tests
  make help [COMMAND]  # Describe available commands or one specific command
  make lint            # Runs the linter
  make spec            # Runs the specs
  make vodka           # Builds and runs the project

λ ./make vodka
         run  bundle exec rake build from "."
g++-8 -std=c++17 -g -pedantic -Wall -Wextra -Werror src/main.cpp src/vodka.cpp -o vodka
vodka> ls
docs  features  Gemfile  Gemfile.lock  LICENSE  make  makefile  rakefile  README.md  spec  src  third_party  tmp  vodka
vodka> ls | grep Gem | cowsay > cow; foo 2> error; uptime -p
up 1 hour, 38 minutes
vodka> cat cow
 ______________________
< Gemfile Gemfile.lock >
 ----------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
vodka> cat error
Bad exec. Exiting.: No such file or directory
vodka> pwd
/home/jethro/code/c++/vodka
vodka> cd -
vodka> pwd
/home/jethro/code/c++/vodka
vodka> cd /
vodka> pwd
/
vodka> cd -
vodka> pwd
/home/jethro/code/c++/vodka
vodka> exit
```

vodka should be (and is tested) to be a drop-in replacement for

- `bash`` --posix`
- `sh`

Development Features
* C++ testing with [Catch2][catch2]
* Interactive testing using [Aruba][aruba] and [Cucumber][cucumber]
  - features also run against `bash` and `sh`, and are generic to any shell

## Dependencies

### Compiling and running

* `g++-8`

### Building and testing

* [Ruby](https://www.ruby-lang.org/en/), to run the Aruba/Cucumber tests, and to use rake and thor as a build system.
* [Git](https://git-scm.com/), to add Catch as a submodule
- [Catch2][catch2], for the c++ tests

## Installation

* Clone the repo or download it
     ```
     git clone https://github.com/jethrodaniel/vodka.git
     ```

* Move into the project directory
     ```
     cd vodka
     ```
- Install development dependencies (you'll need ruby and bundler installed)
     ```
     bundle
     ```

* Create the executable shell
     ```
     ./make build
     ```

## Development

### To show available project commands

```
./make
```

### To run the unit tests

* Download Catch, which is included as a submodule
     ```
     git submodule init
     git submodule update
     ```

* Alternatively, you can download all submodules and clone at the same time using
     ```
     git clone --recurse-submodules https://github.com/jethrodaniel/vodka.git
     ```

### To run the aruba/cucumber tests

* Also installs the required Ruby gems. Fails if Ruby isn't already installed.
     ```
     ./make cucumber
     ```

## TODO

- [ ] extract `features` into a separate `posix-compliance-spec` repo
- [ ] add the rest of the actual shell stuff
  - [ ] here-docs
  - [ ] readline support
  - [ ] so much more

Should POSIX compliance even be the main goal here?

POSIX compliance is the minimum requirement, basically - if more is to be added, we'll package the POSIX whatnot under `vodka --posix`, like bash.

## License

[MIT](LICENSE).

## History

This was originally a homework project - see the [assignment](docs/assignment.pdf).

## References

A big thanks to the following

- https://weblog.jamisbuck.org/2015/7/30/writing-a-simple-recursive-descent-parser.html
- http://www.craftinginterpreters.com/
- http://parsingintro.sourceforge.net/

[catch2]: https://github.com/catchorg/Catch2
[aruba]: https://github.com/cucumber/aruba
[cucumber]: https://github.com/cucumber/cucumber-ruby
