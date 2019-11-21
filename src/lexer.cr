require "string_scanner"

require "./log"
require "./token"

module Vodka
  class Lexer
    include Vodka::Log

    class Error < Exception
    end

    getter input
    getter tokens

    def initialize(@input : String)
      log.info "starting lexer..."
      log.debug "debugging lexer..."

      @scanner = StringScanner.new @input
      @tokens = [] of Token
      @curr_line = 0
      @curr_col = 0
    end

    # Returns all the tokens, in a readable manner
    def to_s
      @tokens.map(&.to_s).join "\n"
    end

    # TODO: abstract all input to shell into an object that responds to `gets`,
    # so that input can be a string, or even stdinput, to facilitate the actual
    # _interpret as you go_ that is the REPL.
    # NOTE: that's input one character at a time
    # TODO: use chars here instead of strings
    def next_token
      if @tokens.empty? # First time
        until !@tokens.empty? || finished?
          scan_token!
        end
        if @tokens.size > 0
          return @tokens.last
        else
          return ""
        end
      end

      prev = @tokens.last

      until @tokens.last != prev || finished?
        scan_token!
      end

      prev == @tokens.last ? "" : @tokens.last
    end

    # Whether the lexer has finished parsing the input
    def finished?
      @scanner.eos?
    end

    # Parse the entire input into a list of TOKENS
    def all_tokens
      until finished?
        scan_token!
        # next_token
      end
    end

    # Handle the current character, attempt to match a TOKEN
    #
    # This is called repeatedly until the scanner hits the end of input
    private def scan_token!
      log.warn "scan_token! - curr_char: #{curr_char.inspect}, curr_pos: #{curr_pos}"

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
      when "\n"
        add_token type: Token::Types::NEWLINE, text: curr_char
        @curr_line += 1
        @curr_col = 0
        advance!
      when " ", "\t" # Ignore white space
        @curr_col += 1
        log.debug "curr_pos: #{curr_pos}"
        advance! 1
      when "<"
        log.info "[lexer] next_char: #{next_char.inspect}"
        if m = match(/\<<(?<name>\w+)/)
          m = advance!(/\<<(?<name>\w+)/)
          name = if m
                   m[2..]
                 else
                   ""
                 end
          add_token type: Token::Types::HEREDOC, text: %(<<#{name})
          @curr_col += 2 + name.size
        else
          add_token type: Token::Types::REDIRECT_LEFT, text: "<"
          @curr_col += 1
          advance!
        end
      when ">"
        log.info "[lexer] next_char: #{next_char.inspect}"
        if next_char == ">"
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
      when "\\"
        # A backslash either
        #
        # - "quotes" the next character as a literal
        # - serves to break up long lines (a `\`,`\n` pair)
        #
        # Apparently in Bash, some characters are treated special for the first
        # point. https://superuser.com/a/794968/1056015
        #
        case next_char
        when "" # Do nothing, as we ended with a backslash. TODO: error?
          @curr_col += 1
          advance!
        when "\\"
          @curr_col += 2
          add_token type: Token::Types::WORD, text: next_char
          advance! 2
        when "\n"
          @curr_line += 1
          advance! 2
        else
          # TODO: this is def not right
          #
          # Need to treat the next character as a literal... what does that
          # mean here? Do we just turn this
          #
          # ```
          # echo \$HOME
          # ```
          #
          # into
          #
          # ```
          # WORD: echo
          # WORD: $
          # WORD: HOME
          # ```
          #
          # Surely not?
          @curr_col += 2
          add_token type: Token::Types::WORD, text: next_char
          advance! 2
        end
      when "'" # single quotes cannot contain single quotes
        if m = match(/'[^']+'/)
          add_token type: Token::Types::SINGLE_QUOTE_STRING, text: m[1...-1]
          @curr_col += m.size
          advance! /'[^']+'/
        else
          raise Lexer::Error.new("unterminated single quote pair at #{curr_pos}")
        end
      when "\""
        # TODO: Double quotes have to be parsed recursively - for example
        #
        # ```
        # echo "foo$(echo "bar$(echo "!")")"
        # ```
        #
        # Double quotes allow the following:
        #
        # - parameter expansion   "${HOME}", "$HOME"
        # - command substitution  "$(echo "$HOME")", "ls `echo "$HOME`"
        # - arithmetic expansion  "1 == $((2 - 1))"
        #
        # TODO: make it the lexer's job to determine whether every one of the
        # above are properly formatted. We'll just pass DOUBLE_QUOTE_STRING to
        # the parser for now, but at least it'll be _validly formatted_. The
        # actual subshell creation and command still needs to be ran at
        # execution time, where we'll create a new Vodka::Lexer then.
        #
        # So
        #
        # ```
        # echo "look! 1 + $(echo "1 == $((1 + 1))")"
        # ```
        #
        # will be tokenized as `[WORD, DOUBLE_QUOTE_STRING]`.
        #
        if m = match(/".*"/)
          add_token type: Token::Types::DOUBLE_QUOTE_STRING, text: m[1...-1]
          @curr_col += m.size
          advance! /".*"/
        else
          raise Lexer::Error.new("unterminated double pair at #{curr_pos}")
        end
      when "`" # TODO: handle backtick strings, i.e, command substitution
        if m = match(/`.*`/)
          add_token type: Token::Types::BACKTICK_STRING, text: m[1...-1]
          @curr_col += m.size
          advance! /`.*`/
        else
          raise Lexer::Error.new("unterminated backtick pair at #{curr_pos}")
        end
      when "$"
        raise Lexer::Error.new("TODO: `$`")
      else
        if m = match(/\d+\>\>/)
          add_token type: Token::Types::DREDIRECT_RIGHT, text: m
          @curr_col += m.size
          advance! /\d+\>\>/
        elsif m = match(/\d+\>\|/)
          add_token type: Token::Types::REDIRECT_RIGHT_CLOBBER, text: m
          @curr_col += m.size
          advance! /\d+\>\|/
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
          log.warn ">>"
          advance! m.size
        else
          raise Lexer::Error.new("unexpected character: #{next_char}")
        end
      end
    end

    # Show the current position, for error messages
    private def curr_pos
      "[#{@curr_line + 1}:#{@curr_col + 1}]"
    end

    # The current character
    private def curr_char
      @scanner.string[@scanner.offset].to_s
    end

    # Check which character is next
    private def next_char
      if @scanner.string.size - 1 < @scanner.offset + 1
        return "" # In case we're currently on the last character
      end

      @scanner.string[@scanner.offset + 1].to_s
    end

    # Check what character is previous to our current position
    private def prev_char
      @scanner.string[@scanner.offset - 1].to_s
    end

    # Advance the scanner
    private def advance!
      @scanner.offset += 1
    end

    # Advance the scanner by a number of characters
    private def advance!(n : Number)
      @scanner.offset += n
    end

    # Advance the scanner by pattern's match result
    private def advance!(pattern : String | Regex)
      @scanner.scan pattern
    end

    # Check if the current input matches a provided regex, without advancing
    private def match(pattern)
      @scanner.check pattern
    end

    # Add a new token to our list
    private def add_token(type : Token::Types, text : String)
      log.warn "add_token"
      token = Token.new line: @curr_line, column: @curr_col, type: type, text: text
      log.debug "adding token: #{token.to_s}"
      @tokens << token
    end
  end
end
