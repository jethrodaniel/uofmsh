require "string_scanner"

require "./log"
require "./token"

module Vodka
  class Lexer
    include Vodka::Log

    class Error < Exception
    end

    getter io : IO::FileDescriptor # The input that we call `read_char` on
    getter? finished = false

    property input = [] of Char
    property tokens = [] of Token
    property line = 0
    property column = 0
    property start = 0
    property current : Char = '\u0000' # \B is ASCII _Start of Text_

    def initialize(@io : IO)
      log.info "starting lexer..."
      log.debug "debugging lexer..."
    end

    def self.interactive
      lex = self.new io: STDIN

      while t = lex.next_token
        puts "token: #{t.to_s.inspect}"
      end

      puts lex.to_s.inspect
    end

    def to_s
      @tokens.map(&.to_s).join "\n"
    end

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

      # we have a previous token, so get the next one
      prev = @tokens.last

      until @tokens.last != prev || finished?
        scan_token!
      end

      prev == @tokens.last ? "" : @tokens.last
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
      c = advance!

      log.warn "scan_token! - curr_char: #{curr_char.inspect}, curr_pos: #{curr_pos}"

      case curr_char
      when '('
        add_token type: Token::Types::LEFT_PAREN, text: curr_char
      when ')'
        add_token type: Token::Types::RIGHT_PAREN, text: curr_char
      when '{'
        add_token type: Token::Types::LEFT_BRACE, text: curr_char
      when '}'
        add_token type: Token::Types::RIGHT_BRACE, text: curr_char
      when ';'
        add_token type: Token::Types::SEMI, text: curr_char
        # when '#' # Skip comment lines
        #  @column += if m = @scanner.scan_until(/\n|$/)
        #               m.size
        #             else
        #               1
        #             end
      when ':'
        add_token type: Token::Types::COLON, text: curr_char
      when '-'
        add_token type: Token::Types::HYPHEN, text: curr_char
      when '\n'
        add_token type: Token::Types::NEWLINE, text: curr_char
      when ' ', '\t' # Ignore white space
        log.debug "curr_pos: #{curr_pos}"
      end
      # when "<"
      #  log.info "[lexer] next_char: #{next_char.inspect}"
      #  if m = match(/\<<(?<name>\w+)/)
      #    m = advance!(/\<<(?<name>\w+)/)
      #    name = if m
      #             m[2..]
      #           else
      #             ""
      #           end
      #    add_token type: Token::Types::HEREDOC, text: %(<<#{name})
      #    @column += 2 + name.size
      #  else
      #    add_token type: Token::Types::REDIRECT_LEFT, text: "<"
      #    @column += 1
      #    advance!
      #  end
      # when ">"
      #  log.info "[lexer] next_char: #{next_char.inspect}"
      #  if next_char == ">"
      #    add_token type: Token::Types::DREDIRECT_RIGHT, text: ">>"
      #    @column += 2
      #    advance! 2
      #  else
      #    add_token type: Token::Types::REDIRECT_RIGHT, text: ">"
      #    @column += 1
      #    advance!
      #  end
      # when "!"
      #  log.info "[lexer] next_char: #{next_char.inspect}"
      #  if next_char == "!"
      #    add_token type: Token::Types::BANGBANG, text: "!!"
      #    @column += 2
      #    advance! 2
      #  else
      #    add_token type: Token::Types::BANG, text: "!"
      #    @column += 1
      #    advance!
      #  end
      # when "|"
      #  log.info "[lexer] next_char: #{next_char.inspect}"
      #  if next_char == "|"
      #    add_token type: Token::Types::OR_IF, text: "||"
      #    @column += 2
      #    advance! 2
      #  else
      #    add_token type: Token::Types::PIPE, text: "|"
      #    @column += 1
      #    advance!
      #  end
      # when "&"
      #  log.info "[lexer] next_char: #{next_char.inspect}"
      #  if next_char == "&"
      #    add_token type: Token::Types::AND_IF, text: "&&"
      #    @column += 2
      #    advance! 2
      #  else
      #    add_token type: Token::Types::AND, text: "&"
      #    @column += 1
      #    advance!
      #  end
      # when "\\"
      #  # A backslash either
      #  #
      #  # - "quotes" the next character as a literal
      #  # - serves to break up long lines (a `\`,`\n` pair)
      #  #
      #  # Apparently in Bash, some characters are treated special for the first
      #  # point. https://superuser.com/a/794968/1056015
      #  #
      #  case next_char
      #  when "" # Do nothing, as we ended with a backslash. TODO: error?
      #    @column += 1
      #    advance!
      #  when "\\"
      #    @column += 2
      #    add_token type: Token::Types::WORD, text: next_char
      #    advance! 2
      #  when "\n"
      #    @line += 1
      #    advance! 2
      #  else
      #    # TODO: this is def not right
      #    #
      #    # Need to treat the next character as a literal... what does that
      #    # mean here? Do we just turn this
      #    #
      #    # ```
      #    # echo \$HOME
      #    # ```
      #    #
      #    # into
      #    #
      #    # ```
      #    # WORD: echo
      #    # WORD: $
      #    # WORD: HOME
      #    # ```
      #    #
      #    # Surely not?
      #    @column += 2
      #    add_token type: Token::Types::WORD, text: next_char
      #    advance! 2
      #  end
      # when "'" # single quotes cannot contain single quotes
      #  if m = match(/'[^']+'/)
      #    add_token type: Token::Types::SINGLE_QUOTE_STRING, text: m[1...-1]
      #    @column += m.size
      #    advance! /'[^']+'/
      #  else
      #    raise Lexer::Error.new("unterminated single quote pair at #{curr_pos}")
      #  end
      # when "\""
      #  # TODO: Double quotes have to be parsed recursively - for example
      #  #
      #  # ```
      #  # echo "foo$(echo "bar$(echo "!")")"
      #  # ```
      #  #
      #  # Double quotes allow the following:
      #  #
      #  # - parameter expansion   "${HOME}", "$HOME"
      #  # - command substitution  "$(echo "$HOME")", "ls `echo "$HOME`"
      #  # - arithmetic expansion  "1 == $((2 - 1))"
      #  #
      #  # TODO: make it the lexer's job to determine whether every one of the
      #  # above are properly formatted. We'll just pass DOUBLE_QUOTE_STRING to
      #  # the parser for now, but at least it'll be _validly formatted_. The
      #  # actual subshell creation and command still needs to be ran at
      #  # execution time, where we'll create a new Vodka::Lexer then.
      #  #
      #  # So
      #  #
      #  # ```
      #  # echo "look! 1 + $(echo "1 == $((1 + 1))")"
      #  # ```
      #  #
      #  # will be tokenized as `[WORD, DOUBLE_QUOTE_STRING]`.
      #  #
      #  if m = match(/".*"/)
      #    add_token type: Token::Types::DOUBLE_QUOTE_STRING, text: m[1...-1]
      #    @column += m.size
      #    advance! /".*"/
      #  else
      #    raise Lexer::Error.new("unterminated double pair at #{curr_pos}")
      #  end
      # when "`" # TODO: handle backtick strings, i.e, command substitution
      #  if m = match(/`.*`/)
      #    add_token type: Token::Types::BACKTICK_STRING, text: m[1...-1]
      #    @column += m.size
      #    advance! /`.*`/
      #  else
      #    raise Lexer::Error.new("unterminated backtick pair at #{curr_pos}")
      #  end
      # when "$"
      #  raise Lexer::Error.new("TODO: `$`")
      # else
      #  if m = match(/\d+\>\>/)
      #    add_token type: Token::Types::DREDIRECT_RIGHT, text: m
      #    @column += m.size
      #    advance! /\d+\>\>/
      #  elsif m = match(/\d+\>\|/)
      #    add_token type: Token::Types::REDIRECT_RIGHT_CLOBBER, text: m
      #    @column += m.size
      #    advance! /\d+\>\|/
      #  elsif m = match(/\d+\>/)
      #    add_token type: Token::Types::REDIRECT_RIGHT, text: m
      #    @column += m.size
      #    advance! /\d+\>/
      #  elsif m = match(/\d+\<\</)
      #    add_token type: Token::Types::DREDIRECT_LEFT, text: m
      #    @column += m.size
      #    advance! /\d+\<\</
      #  elsif m = match(/\d+\</)
      #    add_token type: Token::Types::REDIRECT_LEFT, text: m
      #    @column += m.size
      #    advance! /\d+\</
      #  elsif m = match(/(\w|\d)+/)
      #    add_token type: Token::Types::WORD, text: m
      #    @column += m.size
      #    log.warn ">>"
      #    advance! m.size
      #  else
      #    raise Lexer::Error.new("unexpected character: #{next_char}")
      #  end
      # end
    end

    # Advance the scanner head, return the new current character
    private def advance!
      unless c = @io.read_char
        @finished = true
        @input << '\0'
        return c
      end

      case c
      when '\n'
        @line += 1
        @column = 0
      else
        @column += 1
      end

      @input << c

      @current = c
    end

    # Advance the cursor by a specified number of characters, return the
    # new current character
    private def advance!(n : Number)
      n.times { advance! }
    end

    # Advance the scanner by pattern's match result
    # private def advance!(pattern : String | Regex)
    #   @scanner.scan pattern
    # end

    # Show the current position, for error messages and such
    private def curr_pos
      "[#{@line + 1}:#{@column + 1}]"
    end

    private def curr_char
      @current
      # begin
      #   @input[@io.pos] # or just `@current`
      # rescue e : Errno
      #   log.debug "error #{e.class}:#{e.message}"
      # end
    end

    private def next_char
      return @input.last if finished?

      @io.peek.chr
    end

    private def prev_char
      @input[@io.pos - 1]
    end

    # Check if the current input matches a provided regex, without advancing.
    # Returns the match.
    # private def match(pattern)
    #  @scanner.check pattern
    # end

    # Add a new token to our list
    private def add_token(type : Token::Types, text : Int32 | Char | Array)
      log.warn "add_token"
      text = if text.is_a? Int32
               text.chr.to_s
             elsif text.is_a? Array
               text.join
             else
               text.to_s
             end

      line = text == "\n" ? @line - 1 : @line
      token = Token.new line: line, column: @column, type: type, text: text
      log.debug "adding token: #{token.to_s}"
      @tokens << token
    end
  end
end
