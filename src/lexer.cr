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
      EOF

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

      current = advance!

      log.info "current: #{current}"

      case current
      when "("   then Token::LEFT_PAREN
      when ")"   then Token::RIGHT_PAREN
      when "{"   then Token::LEFT_BRACE
      when "}"   then Token::RIGHT_BRACE
      when ";"   then Token::SEMI
      when "#"   then Token::POUND
      when ":"   then Token::COLON
      when "-"   then Token::HYPHEN
      when "'\'" then Token::BACKSLASH
      when "<"
        next_char = peek 1
        log.info "  next_char: #{next_char}"
        if next_char == "<"
          advance!
          Token::DREDIRECT_LEFT
        else
          Token::REDIRECT_LEFT
        end
      when ">"
        next_char = peek 1
        log.info "> next_char: #{next_char}"
        if next_char == ">"
          advance!
          Token::DREDIRECT_RIGHT
        else
          Token::REDIRECT_RIGHT
        end
      when "!" then Token::BANG
      when "|" then Token::PIPE
      when "&" then Token::AND
        # SINGLE_QUOTED_STR # 'a single quoted string'
        # DOUBLE_QUOTED_STR # "a double quoted string"
        # BACKTICK_STR      # `a backtick quoted string`

        # IO_NUMBER
        # NEWLINE
      else
        # A generic token, which could be any of the below tokens,
        # depending on the context
        Token::TOKEN
      end
      # WORD
      # ASSIGNMENT_WORD
      # NAME
    end

    private def advance!
      current = peek 1
      @scanner.offset += 1
      current
    end

    private def peek(n)
      @scanner.peek n
    end
  end
end
