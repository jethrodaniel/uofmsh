require "./log"
require "./ast"

module Vodka
  class Parser
    include Vodka::Log

    class Error < Exception
    end

    property input

    def initialize(@input : String)
      @lexer = Lexer.new @input
      @ast = [] of AST
    end

    # Parse the TOKENS into an AST tree
    def parse!
      @lexer.scan_tokens!
      @lexer.tokens.each do |t|
        puts "    token: #{t}"
      end
      # log.info "PARSER:  #{next_lexeme}"
    end
  end
end
