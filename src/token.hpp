#ifndef TOKEN_H
#define TOKEN_H

namespace uofmsh {

// A token represents the building blocks of the grammar
class Token {

public:
  enum class Type {
    LEFT_PAREN,    // (
    RIGHT_PAREN,   // )
    LEFT_BRACE,    // {
    RIGHT_BRACE,   // }
    SEMI,          // ;
    POUND,         // #
    COLON,         // :
    HYPHEN,        // -
    BACKSLASH,     // '\'

    REDIRECT_LEFT,   // <
    DREDIRECT_RIGHT, // <<
    DREDIRECT_LEFT,  // >
    REDIRECT_RIGHT,  // >>
    BANG,            // !
    BANGBANG,        // !!
    AND,             // &
    AND_IF,          // &&
    PIPE,            // |
    OR_IF,           // ||

    SINGLE_QUOTED_STR,  // 'a single quoted string'
    DOUBLE_QUOTED_STR,  // "a double quoted string"
    BACKTICK_STR,       // `a double quoted string`

    // A generic token, which could be any of the below tokens,
    // depending on the context
    TOKEN,

    WORD,
    ASSIGNMENT_WORD,
    NAME,
    NEWLINE,
    IO_NUMBER,

    END // EOF
  };

  // @return  A new Token instance
  Token(Type type, std::string lexeme,
        const int line, const int start, const int end)
  : type(type), lexeme(lexeme), line(line), start(start), end(end) { }

  // Allows a token to be printed using <<
  friend std::ostream &operator<<(std::ostream &output, const Token &t ) {
    output << "Type: " << (int)t.type << " ["
           << t.line << "," << t.start << " - " << std::setw(3) << t.end
           << "]: '" << t.lexeme << "'";
    return output;
  }

  Type getType() {
    return type;
  }

  std::string getLexeme() {
    return lexeme;
  }

private:
 const Type type;
  const std::string lexeme;    // The characters that form this token
  const int line,              // The line number of this token
            start,             // The column number of the start of this token
            end;               // The column number of the end of this token
};

} // namespace uofmsh

#endif
