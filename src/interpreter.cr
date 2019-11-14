require "./log"

module Vodka
  class Interpreter
    include Vodka::Log

    property input

    def initialize(@input : String)
      @parser = Parser.new @input
    end

    # Run the AST tree as a program
    def interpret!
      begin
        ast = @parser.parse!
        # log.info "INTERPRETER: #{next_node}"
      rescue e : Vodka::Lexer::Error
        raise e
      end
    end
  end
end
