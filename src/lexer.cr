require "string_scanner"

require "./log"
require "./token"

module Ometa
  class Lexer
    include Ometa::Log

    class Error < Exception
    end

    getter input, tokens, line_number, column_number

    def initialize(@input : String)
      log.info "starting lexer..."
      log.debug "debugging lexer..."

      @reader = Char::Reader.new @input
      @tokens = [] of Token
      @line_number = 1
      @column_number = 1

      lex!
    end

    # Returns all the tokens, in a readable manner
    def to_s
      @tokens.map(&.to_s).join "\n"
    end

    # Parse the entire input into a list of TOKENS
    private def lex!
      while @reader.has_next?
        next_token!
      end
    end

    # Handle the current character, attempt to match a TOKEN
    #
    # This is called repeatedly until the scanner hits the end of input
    private def next_token!
      log.debug "[lexer] current: #{curr_char.inspect}"

      case curr_char
      when "("
        add_token type: Token::Types::LEFT_PAREN, text: curr_char
        @column_number += 1
        advance!
      when ")"
        add_token type: Token::Types::RIGHT_PAREN, text: curr_char
        @column_number += 1
        advance!
      when "{"
        add_token type: Token::Types::LEFT_BRACE, text: curr_char
        @column_number += 1
        advance!
      when "}"
        add_token type: Token::Types::RIGHT_BRACE, text: curr_char
        @column_number += 1
        advance!
      when ";"
        add_token type: Token::Types::SEMI, text: curr_char
        @column_number += 1
        advance!
        # when "#" # Skip comment lines
        #   @column_number += if m = @scanner.scan_until(/\n|$/)
        #                       m.size
        #                     else
        #                       1
        #                     end
      when "\n"
        add_token type: Token::Types::NEWLINE, text: curr_char
        @line_number += 1
        @column_number = 0
        advance!
      else
        if curr_char.to_s.match(/(\w|\d)+/)
          m = curr_char
          add_token type: Token::Types::WORD, text: m
          # @column_number += m.size
          # advance! /(\w|\d)+/
          advance!
        else
          raise Lexer::Error.new("unexpected character: #{next_char}")
        end
      end
    end

    private def curr_pos
      "[#{@line_number}:#{@column_number}]"
    end

    private def curr_char
      @reader.current_char
    end

    private def next_char
      @reader.peek_next_char
    end

    private def prev_char
      @reader.previous_char
    end

    private def advance!
      @reader.next_char
    end

    private def advance!(n : Number)
      n.times { advance! }
    end

    private def add_token(type : Token::Types, text : Char | String)
      @tokens << Token.new(
        line: @line_number,
        column: @column_number,
        type: type,
        text: text.to_s
      )
    end
  end
end
