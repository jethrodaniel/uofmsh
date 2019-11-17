require "./log"
require "./parser"

module Vodka
  class Interpreter
    property input
    property parser : Vodka::Parser

    property log : Logger = Logger.new(STDOUT, level: Logger::INFO)

    def initialize(@input : String)
      log.debug "starting interpreter ..."

      @parser = Parser.new @input

      puts @parser.lexer.to_s if @parser.lexer.tokens.size > 0
    end
  end
end
