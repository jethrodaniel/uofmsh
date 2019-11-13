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

require "string_scanner"
require "logger"

module VodkaSupport
  module Log
    def log
      Logger.new(STDOUT).tap { log.level = Logger::INFO }
    end
  end
end

module Vodka
  VERSION = "0.2.0"

  class Error
  end

  # scanner - keeps track of position in file, line number, etc.
  # lexer - constructs TOKENS
  class Lexer
    # include VodkaSupport::Log

    property input

    def initialize(@input : String)
      @scanner = StringScanner.new @input
    end

    # parse the input into TOKENS
    def next_lexeme
      return nil if @scanner.eos?

      next_char = @scanner.peek 1

      # log.info "next_char: #{next_char}"

      case next_char
      when "q"
        puts "yo!"
      else
        puts "no!"
      end

      "TOKEN"
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
    # include VodkaSupport::Log

    property input

    def initialize(@input : String)
      @lexer = Lexer.new @input
    end

    # Parse the TOKENS into an AST tree, incrementally
    def next_ast_node
      next_lexeme = @lexer.next_lexeme
      # log.info "next_lexeme: #{next_lexeme}"
      next_lexeme
    end
  end

  class Interpreter
    # include VodkaSupport::Log

    property input

    def initialize(@input : String)
      @parser = Parser.new @input
    end

    # Run the AST tree as a program
    def interpret!
      next_node = @parser.next_ast_node

      # log.info "next_ast_node: #{next_node}"

      # case next_node
      # when nil
      # end
    end
  end

  class Shell
    # include VodkaSupport::Log

    property prompt

    BANNER = <<-COW
                  ^__^
          _______/(oo)
      /\\/(       /(__)🚬    vodka.
         ||w----||
         ||     ||
    COW

    def initialize(@prompt : String)
      @prompt ||= "λ"
      # @interpreter ||= Interpreter.new ""
    end

    # Run the interactive shell, i.e, the REPL
    def repl!(banner = false, fortune = false)
      puts BANNER if banner

      puts %x{fortune} if fortune

      loop do
        print "#{@prompt}"
        input = gets.not_nil!.chomp || ""

        # TODO cleanup
        interpreter = Interpreter.new input

        interpreter.interpret!
      end
    end

    # Run a single line of input
    def eval!(input : String)
      # # TODO: dont handle builtins differently, just check if builtin first
      # if input == "q" || input == "exit"
      #   puts "bye! <3"
      #   exit 1
      # end
    end

    def to_s
      "[vodka shell] #{@prompt}"
    end
  end
end
