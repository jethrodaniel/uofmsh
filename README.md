# uofmsh

A basic shell

Features
* C++ testing with [Catch](https://github.com/catchorg/Catch2)
* Interactive testing using [Aruba](https://github.com/cucumber/aruba) and [Cucumber](https://github.com/cucumber/cucumber-ruby)
* Cross-platform development environment using [Vagrant](https://www.vagrantup.com)

## Dependencies
---

### To compile and run the shell

* A C++ compiler, such as [g++](https://gcc.gnu.org/)

### Additionally, to use the included makefile for project tasks

* [GNU Make](https://www.gnu.org/software/make/)

### Additionally, to run the tests

* [Git](https://git-scm.com/), to add Catch as a submodule
* [Ruby](https://www.ruby-lang.org/en/), to run the Aruba/Cucumber tests. [RVM](https://rvm.io/) is the suggested installation method.

### Additionally, if using Vagrant

* [Vagrant](https://www.vagrantup.com/downloads.html)


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

### Using Vagrant

A Vagrantfile is included that will set up a simple development environment running Ubuntu 18.04.

Make sure Vagrant is installed, then run the following commands (these may take a long time)

```
vagrant up    # To create the vm
vagrant ssh   # To ssh into the vm
```

When finished

```
vagrant halt  # To halt the vm
```
