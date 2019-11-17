require "string_scanner"

require "./log"

module Vodka
  class Token
    enum Types
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

      WORD
      ASSIGNMENT_WORD
      NAME
    end

    def initialize(@line : Int32,
                   @column : Int32,
                   @type : Types,
                   @text : String)
    end

    def to_s
      "[#{@line + 1}:#{@column + 1}] #{@type} \`#{@text}`"
    end
  end

  # scanner - keeps track of position in file, line number, etc.
  # lexer - constructs TOKENS
  #
  # The grammar for a posix shell is
  #
  # bnf
  #
  #
  class Lexer
    include Vodka::Log

    class Error < Exception
    end

    property input
    getter tokens

    def initialize(@input : String)
      @scanner = StringScanner.new @input
      @tokens = [] of Token
      @curr_line = 0
      @curr_col = 0

      scan_tokens!
    end

    def to_s
      @tokens.map(&.to_s).join "\n"
    end

    # Parse the entire input into a list of TOKENS.
    #
    # TODO: better names
    private def scan_tokens!
      until @scanner.eos?
        scan_token!
      end
    end

    # advance the scanner and attempt to match a TOKEN
    #
    # TODO: better names
    private def scan_token!
      log.info "[lexer] current: #{curr_char.inspect}"

      case curr_char
      when "("
        add_token type: Token::Types::LEFT_PAREN, text: curr_char
        @curr_col += 1
        advance!
      when ")"
        add_token type: Token::Types::RIGHT_PAREN, text: curr_char
        @curr_col += 1
        advance!
      when "{"
        add_token type: Token::Types::LEFT_BRACE, text: curr_char
        @curr_col += 1
        advance!
      when "}"
        add_token type: Token::Types::RIGHT_BRACE, text: curr_char
        @curr_col += 1
        advance!
      when ";"
        add_token type: Token::Types::SEMI, text: curr_char
        @curr_col += 1
        advance!
      when "#" # Skip comment lines
        @curr_col += if m = @scanner.scan_until(/\n|$/)
                       m.size
                     else
                       1
                     end
      when ":"
        add_token type: Token::Types::COLON, text: curr_char
        @curr_col += 1
        advance!
      when "-"
        add_token type: Token::Types::HYPHEN, text: curr_char
        @curr_col += 1
        advance!
      when "\\"
        add_token type: Token::Types::BACKSLASH, text: curr_char
        @curr_col += 1
        advance!
      when "\n"
        add_token type: Token::Types::NEWLINE, text: curr_char
        @curr_line += 1
        advance!
      when " " # Ignore white space
        @curr_col += 1
        advance!
      when "<"
        log.info "[lexer] next_char: #{next_char.inspect}"
        if next_char == "<"
          add_token type: Token::Types::DREDIRECT_LEFT, text: "<<"
          @curr_col += 2
          advance! 2
        else
          add_token type: Token::Types::REDIRECT_LEFT, text: "<"
          @curr_col += 1
          advance!
        end
      when ">"
        log.info "[lexer] next_char: #{next_char.inspect}"
        if next_char == "<"
          add_token type: Token::Types::DREDIRECT_RIGHT, text: ">>"
          @curr_col += 2
          advance! 2
        else
          add_token type: Token::Types::REDIRECT_RIGHT, text: ">"
          @curr_col += 1
          advance!
        end
      when "!"
        log.info "[lexer] next_char: #{next_char.inspect}"
        if next_char == "!"
          add_token type: Token::Types::BANGBANG, text: "!!"
          @curr_col += 2
          advance! 2
        else
          add_token type: Token::Types::BANG, text: "!"
          @curr_col += 1
          advance!
        end
      when "|"
        log.info "[lexer] next_char: #{next_char.inspect}"
        if next_char == "|"
          add_token type: Token::Types::OR_IF, text: "||"
          @curr_col += 2
          advance! 2
        else
          add_token type: Token::Types::PIPE, text: "|"
          @curr_col += 1
          advance!
        end
      when "&"
        log.info "[lexer] next_char: #{next_char.inspect}"
        if next_char == "&"
          add_token type: Token::Types::AND_IF, text: "&&"
          @curr_col += 2
          advance! 2
        else
          add_token type: Token::Types::AND, text: "&"
          @curr_col += 1
          advance!
        end
      when "'"
        # SINGLE_QUOTED_STR # 'a single quoted string'
      when "\""
        # DOUBLE_QUOTED_STR # "a double quoted string"
      when "`"
        # BACKTICK_STR      # `a backtick quoted string`
      else
        # Possibly
        # IO_NUMBER
        # log.info "[lexer] next_char: #{next_char.inspect}"

        if m = match(/\d+\>\>/)
          add_token type: Token::Types::DREDIRECT_RIGHT, text: m
          @curr_col += m.size
          advance! /\d+\>\>/
        elsif m = match(/\d+\>/)
          add_token type: Token::Types::REDIRECT_RIGHT, text: m
          @curr_col += m.size
          advance! /\d+\>/
        elsif m = match(/\d+\<\</)
          add_token type: Token::Types::DREDIRECT_LEFT, text: m
          @curr_col += m.size
          advance! /\d+\<\</
        elsif m = match(/\d+\</)
          add_token type: Token::Types::REDIRECT_LEFT, text: m
          @curr_col += m.size
          advance! /\d+\</
        elsif m = match(/(\w|\d)+/)
          add_token type: Token::Types::WORD, text: m
          @curr_col += m.size
          advance! /(\w|\d)+/
        else
          raise Lexer::Error.new("unexpected character: #{next_char}")
        end
      end
    end

    # The current character.
    #
    # @return the current character
    private def curr_char
      @scanner.string[@scanner.offset].to_s
    end

    # Check what character is next.
    #
    # @return the next character
    private def next_char
      if @scanner.string.size - 1 < @scanner.offset + 1
        return "" # In case we're currently on the last character
      end

      @scanner.string[@scanner.offset + 1].to_s
    end

    # Check what character was previous to our current one.
    #
    # @return the previous character
    private def prev_char
      @scanner.string[@scanner.offset - 1].to_s
    end

    # @return the current scanner offset
    private def advance!
      @scanner.offset += 1
    end

    # @param n: the number of characters to advance by
    # @return the current scanner offset
    private def advance!(n : Number)
      @scanner.offset += n
    end

    # Advance the scanner by pattern's match result
    #
    # @return the scanner's match result
    private def advance!(pattern : String | Regex)
      @scanner.scan pattern
    end

    # Check if the scanner matches a provided regex, without advancing
    #
    # @return [String] the matched input
    private def match(pattern)
      @scanner.check pattern
    end

    # Add a new token to our list.
    #
    # @return [Vodka::Token] the new token that was added to @tokens
    private def add_token(type : Token::Types, text : String)
      @tokens << Token.new line: @curr_line, column: @curr_col, type: type, text: text
    end
  end
end
