require "./log"

module Vodka
  class Token
    include Vodka::Log

    getter line, column, type, text

    def initialize(@line : Int32,
                   @column : Int32,
                   @type : Types,
                   @text : String)
    end

    def to_s
      "[#{@line + 1}:#{@column + 1}] #{@type} \`#{@text}`"
    end

    def ==(other)
      @line == other.line && \
         @column == other.column && \
         @type == other.type && \
         @text == other.text
    end

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

      REDIRECT_LEFT          # <
      DREDIRECT_LEFT         # <<
      REDIRECT_RIGHT         # >
      REDIRECT_RIGHT_CLOBBER # >|
      DREDIRECT_RIGHT        # >>
      BANG                   # !
      BANGBANG               # !!
      AND                    # &
      AND_IF                 # &&
      PIPE                   # |
      OR_IF                  # ||

      SINGLE_QUOTE_STRING # 'a single quoted string'
      DOUBLE_QUOTE_STRING # "a double quoted string"
      BACKTICK_STRING     # `a backtick quoted string`

      HEREDOC # <<here

      NEWLINE

      WORD
      NAME
      ASSIGNMENT_WORD
    end
  end
end
