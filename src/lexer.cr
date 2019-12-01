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
      log.debug "[lex] current: #{curr_char.inspect}"
      log.debug "[lex] next: #{next_char.inspect}"
      while has_next?
        next_token!
      end
    end

    private def has_next?
      @reader.has_next? && next_char != '\0'
    end

    private def at_start?
      @line_number == 1 && @column_number == 1
    end

    # Handle the current character, attempt to match a TOKEN
    #
    # This is called repeatedly until the scanner hits the end of input
    private def next_token!
      log.debug "[next_token] current: #{curr_char.inspect}"

      advance! unless at_start?

      case curr_char
      when '('
        add_token type: Token::Types::LEFT_PAREN, text: curr_char
        @column_number += 1
      when ')'
        add_token type: Token::Types::RIGHT_PAREN, text: curr_char
        @column_number += 1
      when '{'
        add_token type: Token::Types::LEFT_BRACE, text: curr_char
        @column_number += 1
      when '}'
        add_token type: Token::Types::RIGHT_BRACE, text: curr_char
        @column_number += 1
      when ';'
        add_token type: Token::Types::SEMI, text: curr_char
        @column_number += 1
        # when "#"
        # until next_char == '\n' ||
        #   @column_number += if m = @scanner.scan_until(/\n|$/)
        #                       m.size
        #                     else
        #                       1
        #                     end
      when '\n'
        add_token type: Token::Types::NEWLINE, text: curr_char
        @line_number += 1
        @column_number = 1
      when '\u{0}' # do nothing
      when ' '
        @column_number += 1
      else
        log.debug ">> else"
        if curr_char.letter? || curr_char == '_'
          m = curr_char.to_s
          while has_next? && (next_char.alphanumeric? || next_char == '_')
            log.debug ">>>> next_char: #{next_char}"
            advance!
            m += curr_char.to_s
          end

          add_token type: Token::Types::WORD, text: m
          @column_number += m.size
        else
          raise Lexer::Error.new("unexpected character: #{next_char.inspect}")
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
      log.debug "advance!..."
      @reader.next_char
    end

    private def advance!(n : Number)
      n.times { advance! }
    end

    private def add_token(type : Token::Types, text : Char | String)
      t = Token.new(
        line: @line_number,
        column: @column_number,
        type: type,
        text: text.to_s
      )
      log.debug { "adding token #{t.to_s}" }
      @tokens << t
    end
  end
end
