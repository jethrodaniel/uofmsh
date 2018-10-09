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

    REDIRECT_LEFT,    // <
    DREDIRECT_LEFT,   // <<
    NREDIRECT_LEFT,   // n<
    NDREDIRECT_LEFT,  // n<<
    REDIRECT_RIGHT,   // >
    DREDIRECT_RIGHT,  // >>
    NREDIRECT_RIGHT,  // n>
    NDREDIRECT_RIGHT, // n>>
    BANG,             // !
    BANGBANG,         // !!
    AND,              // &
    AND_IF,           // &&
    PIPE,             // |
    OR_IF,            // ||

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
  Token(const Type type, const std::string lexeme,
        const int line, const int start, const int end)
    : type(type), lexeme(lexeme), line(line), start(start), end(end) { }

  Token(const Token &t)
    : type(t.type), lexeme(t.lexeme), line(t.line), start(t.start), end(t.end) { }

  // Allows a token to be printed using <<
  friend std::ostream &operator<<(std::ostream &output, const Token &t ) {
    output << "Type: " << (int)t.type << " ["
           << t.line << "," << t.start << " - " << std::setw(3) << t.end
           << "]: '" << t.lexeme << "'";
    return output;
  }

  bool operator==(const Token &other) {
    return type   == other.type   &&
           lexeme == other.lexeme &&
           line   == other.line   &&
           start  == other.start  &&
           end    == other.end;
  }

  friend bool operator==(const Token &t1, const Token t2) {
    return t1.type   == t2.type   &&
           t1.lexeme == t2.lexeme &&
           t1.line   == t2.line   &&
           t1.start  == t2.start  &&
           t1.end    == t2.end;
  }

  Type getType() {
    return type;
  }

  const std::string getLexeme() {
    return lexeme;
  }

  int getLine() {
    return line;
  }

  int getStart() {
    return start;
  }

  int getEnd() {
    return end;
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
