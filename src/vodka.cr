# vodka shell
#
# POSIX shell specs: https://pubs.opengroup.org/onlinepubs/9699919799/
#
# ## How it do
#
# - scanner - reads input text, keeps track of current position
# - lexer - reads in source, creates TOKENS
# - parser - reads in the TOKENS outputed by the lexer, outputs a AST
# - shell - runs the AST as a program
#
# TODO
#
# In the current version, each stage makes a separate pass.
# We can avoid this, by having each work incrementally.
#
# In the current version, errors are just thrown from any level up to the shell.
#
# Since we're parsing incrementally now, just attach error info to each one of
# the incremental requests.
#
module Vodka
  VERSION = "0.2.0"

  class Error
  end
end

require "./log"
require "./lexer"
require "./parser"
require "./shell"
