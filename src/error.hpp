#ifndef ERROR_H
#define ERROR_H

namespace vodka {

// A error specifies a message and where the error occured
class Error : public std::exception {
  std::string msg;  // The error message
  int line, column; // The line and column where the error occured

public:
  // @param  msg     The error message
  // @param  line    The line where the error occured
  // @param  column  The column where the error occured
  // @return         A new error instance
  explicit Error(std::string msg, int line, int column)
    : msg(msg), line(line), column(column) { }

  // @return  The error message
  std::string getMsg() const {
    return msg;
  }

  // @return  The line the error occured on
  int getLine() const {
    return line;
  }

  // @return  The column the error occured on
  int getColumn() const {
    return column;
  }
};

} // namespace vodka

#endif
