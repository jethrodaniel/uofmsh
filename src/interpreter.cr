require "./log"

module Vodka
  class Interpreter
    include Vodka::Log

    property input

    def initialize(@input : String)
      begin
        ast = @parser.parse!
        @ast = Parser.new @input
        # log.info "INTERPRETER: #{next_node}"
      rescue e : Vodka::Lexer::Error | Vodka::Parser::Error
        raise e
      end
    end
  end
end
