#ifndef TOKEN_H
#define TOKEN_H

namespace uofmsh {

// A token represents the building blocks of the grammar
class Token {

public:
  // The types of tokens
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
    REDIRECT_RIGHT,   // >
    DREDIRECT_RIGHT,  // >>
    BANG,             // !
    BANGBANG,         // !!
    AND,              // &
    AND_IF,           // &&
    PIPE,             // |
    OR_IF,            // ||

    SINGLE_QUOTED_STR,  // 'a single quoted string'
    DOUBLE_QUOTED_STR,  // "a double quoted string"
    BACKTICK_STR,       // `a double quoted string`

    IO_NUMBER,
    NEWLINE,
    END,       // EOF

    // A generic token, which could be any of the below tokens,
    // depending on the context
    TOKEN,

    WORD,
    ASSIGNMENT_WORD,
    NAME
  };

  /**
   * @param  type    The token's type
   * @param  lexeme  The text of this token
   * @param  line    The line where this token was found
   * @param  start   The starting index of this token
   * @param  end     The ending index of this token
   * @return         A new Token instance
   */
  explicit Token(const Type type, const std::string &lexeme,
                 const int line, const int start, const int end)
    : type(type), lexeme(lexeme), line(line), start(start), end(end) { }

  /**
   * Allows a token instance to be printed using <<
   *
   * @param  output  The output stream to write to
   * @param  t       The token instance to write out
   */
  friend std::ostream &operator<<(std::ostream &output, const Token &t ) {
    output << t.prettyPrint();
    return output;
  }

  /**
   * @return  indention  The amount to indent
   * @return             A pretty representation of this token
   */
  const std::string prettyPrint(const int indention = 0) const {
    std::ostringstream out;
    std::string indent(indention, ' ');

    out << indent << "Token: [\n"
        << indent << "  type:   [" << (int)type << "]\n"
        << indent << "  line:   [" << line      << "]\n"
        << indent << "  start:  [" << start     << "]\n"
        << indent << "  end:    [" << end       << "]\n"
        << indent << "  lexeme: [" << lexeme    << "]\n"
        << indent << "] // Token";

    return out.str();
  }



  /**
   * @param  other  A token instance to compare to this instance
   * @return        Whether this token is the same, member-wise, as other
   */
  bool operator==(const Token &other) {
    return type   == other.type   &&
           lexeme == other.lexeme &&
           line   == other.line   &&
           start  == other.start  &&
           end    == other.end;
  }

  /**
   * @param  t1  A token to compare against t2
   * @param  t2  A token to compare against t1
   * @return     Whether the tokens are the same, member-wise
   */
  friend bool operator==(const Token &t1, const Token &t2) {
    return t1.type   == t2.type   &&
           t1.lexeme == t2.lexeme &&
           t1.line   == t2.line   &&
           t1.start  == t2.start  &&
           t1.end    == t2.end;
  }

  /**
   * @return  This token's type
   */
  Type getType() {
    return type;
  }

  /**
   * This token's text
   */
  const std::string getLexeme() {
    return lexeme;
  }

  /**
   * This token's line
   */
  int getLine() {
    return line;
  }

  /**
   * This token's starting index
   */
  int getStart() {
    return start;
  }

  /**
   * This token's ending index
   */
  int getEnd() {
    return end;
  }

private:
  const Type type;             // The type of this token
  const std::string lexeme;    // The characters that form this token
  const int line,              // The line number of this token
            start,             // The column number of the start of this token
            end;               // The column number of the end of this token
};

} // namespace uofmsh

#endif
