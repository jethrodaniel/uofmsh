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
# TODO: all below
#
# In the current version, each stage makes a separate pass.
# We can avoid this, by having each work incrementally like so:
#
# - the lexer and scanner's calls are for collections, one at a time
# - the single pass is up after parsing, then a pass through the AST is needed to run the interpreter
#
# **Note**: the lexer and scanner may be combined like this
#
# #### Error handling
#
# In the current version, errors are just thrown from any level up to the shell.
#
# Since we're parsing incrementally now, just attach error info to each one of
# the incremental requests.
#
module Vodka
  VERSION = "0.2.0"

  class Error; end

  property log : Logger = Logger.new(STDOUT, level: Logger::INFO)
end

require "./log"
require "./lexer"
require "./parser"
require "./interpreter"
require "./shell"
