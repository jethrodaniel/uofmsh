require "string_scanner"

require "./log"

module Vodka
  # scanner - keeps track of position in file, line number, etc.
  # lexer - constructs TOKENS
  #
  # The grammar
  class Lexer
    include Vodka::Log

    property input

    enum Token
      LEFT_PAREN  # (
      RIGHT_PAREN # )
      LEFT_BRACE  # {
      RIGHT_BRACE # }
      SEMI        # ;
      POUND       # #
      COLON       # :
      HYPHEN      # -
      BACKSLASH   # '\'

      REDIRECT_LEFT   # <
      DREDIRECT_LEFT  # <<
      REDIRECT_RIGHT  # >
      DREDIRECT_RIGHT # >>
      BANG            # !
      BANGBANG        # !!
      AND             # &
      AND_IF          # &&
      PIPE            # |
      OR_IF           # ||

      SINGLE_QUOTED_STR # 'a single quoted string'
      DOUBLE_QUOTED_STR # "a double quoted string"
      BACKTICK_STR      # `a backtick quoted string`

      IO_NUMBER
      NEWLINE
      END # EOF

      # A generic token, which could be any of the below tokens,
      # depending on the context
      TOKEN

      WORD
      ASSIGNMENT_WORD
      NAME
    end

    def initialize(@input : String)
      @scanner = StringScanner.new @input
    end

    # parse the input into TOKENS
    def next_lexeme
      return nil if @scanner.eos?

      next_char = @scanner.peek 1

      log.info "next_char: #{next_char}"

      case next_char
      when "q"
        # puts "yo!"
      else
        # puts "no!"
      end

      next_char
    end
  end
end
