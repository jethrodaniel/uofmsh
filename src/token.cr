require "./log"

module Ometa
  class Token
    include Ometa::Log

    getter line, column, type, text

    def initialize(@line : Int32,
                   @column : Int32,
                   @type : Types,
                   @text : String)
    end

    def to_s
      t = @text == '\n' ? "\\n" : @text
      "[#{@line}:#{@column}-#{@column - 1 + @text.size}] #{@type} `#{t}`"
    end

    def ==(other)
      @line == other.line && \
         @column == other.column && \
         @type == other.type && \
         @text == other.text
    end

    enum Types
      # parameterized rules:
      #
      # ```
      # charRange :x :y = char:c ?(x <= c && c <= y) -> c
      # ```
      #
      # semantic predicates:
      #
      # ```
      # digit = char:d ?(d >= ’0’ && d <= ’9’) -> d
      # ```
      #
      # grouping:
      #
      # ```
      # foo = (bar | baz)*
      # ```
      LEFT_PAREN  # (
      RIGHT_PAREN # )

      # grouping of semantic actions:
      #
      # ```
      # exp = exp:x ’+’ fac:y -> { [’add’, x, y] };
      # ```
      #
      # This is a derivation of the '08 syntax.
      #
      # TODO: is this really needed?
      # TODO: might use _semantic actions must be on one line_ for now
      LEFT_BRACE  # {
      RIGHT_BRACE # }

      # match lists:
      #
      # ```
      # eval = [’num’ anything:x] -> x.to_i
      # ```
      LEFT_BRACKET  # [
      RIGHT_BRACKET # ]

      LOOK_AHEAD     # &
      SEMI           # ;
      COLON          # :
      EQUALS         # =
      SEMANTIC_START # ->
      LITERAL        # '...'
      ZERO_OR_MORE   # *
      ONE_OR_MORE    # +
      ONE_OR_ZERO    # ?

      # negation:
      #
      # ```
      # end = ~anything
      # ```
      NOT

      SUPER # ^
      OR    # |

      NEWLINE # \n

      RULE

      # foreign
      # anything

      NAME
      ASSIGNMENT_WORD
    end
  end
end
