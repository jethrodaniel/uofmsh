# vodka shell
#
# At the moment, vodka's goal is to be a `sh` clone. When this is done,
# then we can move this functionality into a `--posix` flag.
#
# - POSIX shell specs: https://pubs.opengroup.org/onlinepubs/9699919799/
#
# ## How it do
#
# - scanner - reads input text, keeps track of current position
# - lexer - reads in source, creates TOKENS
# - parser - reads in the TOKENS outputed by the lexer, outputs a AST
# - interpreter - runs the AST as a program
# - shell - decides if running a file or a repl, evals/interprets code, etc
#
# In the current C++ version, each stage makes a separate pass.
# We can avoid this, by having each work incrementally like so:
#
# - the lexer and scanner's calls are for collections, one at a time
# - the single pass is up after parsing, then a pass through the AST is needed to run the interpreter
#
# **Note**: the lexer and scanner may be combined
#
# #### Error handling
#
# In the current C++ version, errors are just thrown from any level up to the shell.
#
# Since we're parsing incrementally now, just attach error info to each one of
# the incremental requests.
#
# ## License
#
# MIT.
#
# TODO: write docs
#
module Vodka
  VERSION = "0.2.0"

  class Error
  end

  # Keep track of position in file, line number, etc.
  # Basically just StringScanner in Ruby
  class Scanner
  end

  class Lexer
    property input

    def initialize(@input : String)
    end

    # parse the input into TOKENS, return as a lazy collection
    def lexemes
    end
  end

  module AST
    class Program
    end

    class Pipeline
    end

    class Command
    end

    class Redirection
    end

    class FileDescriptor
    end

    # ...
  end

  class Parser
    property input

    def initialize(@input : String)
    end

    # Parse the TOKENS into an AST tree.
    #
    # This calls #lexemes, and finishes a complete pass of the input.
    def parse
    end

    # Parse the TOKENS into an AST tree, incrementally
    #
    # This calls #lexemes
    def ast_nodes
    end

    # Return lexer to start of input
    def rewind
    end
  end

  class Interpreter
    property input

    def initialize(@input : String)
    end

    # Run the AST tree as a program
    def interpret
    end
  end

  class Shell
    property prompt

    def initialize(@prompt : String)
    end

    # Run the interactive shell, i.e, the REPL
    def repl!
      loop do
        print "#{@prompt}"
        input = gets.not_nil!.chomp
        eval! input
      end
    end

    # Run a single line of input
    def eval!(input : String)
      if input == "q" || input == "exit"
        puts "bye! <3"
        exit 1
      end
    end

    def to_s
      "[vodka shell] #{@prompt}"
    end
  end
end
