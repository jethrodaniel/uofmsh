# uofmsh

A shell, written in c

Features
* Unit testing of C helper functions using [Unity](https://github.com/ThrowTheSwitch/Unity)
* Interactive testing using [Aruba](https://github.com/cucumber/aruba) and [Cucumber](https://github.com/cucumber/cucumber-ruby)
* Cross-platform development environment using [Vagrant](https://www.vagrantup.com)

Dependencies
* C language
* Un\*x environment


## Requirements
---

### To compile and run the shell

* A C compiler, such as [GCC](https://gcc.gnu.org/)

### Additionally, to use the included makefile for project tasks

* [GNU Make](https://www.gnu.org/software/make/)

### Additionally, to run the tests

* [Git](https://git-scm.com/), to add Unity as a submodule
* [Ruby](https://www.ruby-lang.org/en/), to run the Aruba/Cucumber tests. [RVM](https://rvm.io/) is the prefered installation method.

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


## Usage
---

To show available commands

```
make
```


## Testing
---

### Using Vagrant

By using Vagrant, we set up all dependencies in the Vagranfile, so getting the
right Un\*x enviroment with all the development dependencies is easy.

Make sure Vagrant is installed, then run the following commands in Bash

```
./vagrant up    # To create the vm
./vagrant ssh   # To ssh into the vm
```

When finished

```
./vagrant halt  # To halt the vm
```

### Requirements

* Download Unity, which is included as a submodule
     ```
     git submodule init && git submodule update
     ```

Alternatively, you can download all Unity and clone at the same time using
```
git clone --recurse-submodules https://github.com/jethrodaniel/uofmsh.git
```

* Install the Ruby gems (provided you've already installed Ruby)
     ```
     gem install bundle
     bundle
     ```

