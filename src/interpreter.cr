module Vodka
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
end
