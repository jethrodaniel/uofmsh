require "./log"

module Vodka
  class Parser
    include Vodka::Log

    property input

    def initialize(@input : String)
      @lexer = Lexer.new @input
    end

    # Parse the TOKENS into an AST tree, incrementally
    def next_ast_node
      next_lexeme = @lexer.next_lexeme
      log.info "next_lexeme: #{next_lexeme}"
      next_lexeme
    end
  end
end
