require "./log"
require "./ast"

module Vodka
  class Parser
    class Error < Exception
    end

    property input
    getter lexer

    def initialize(@input : String)
      @lexer = Lexer.new @input
      @ast = [] of AST
    end

    # Parse the TOKENS into an AST tree
    def parse!
      puts @lexer.to_s
      # log.info "PARSER:  #{next_lexeme}"
    end
  end
end
