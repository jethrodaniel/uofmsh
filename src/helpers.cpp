#include "helpers.hpp"

#include <iostream>
#include <sstream>

namespace uofmsh {

/* Splits a string by a single character delimiter into a vector
 *
 * @param input     the string to split
 * @return          the substrings from the split
 */
std::vector<std::string> split(const std::string input, const char delim) {

  std::vector<std::string> substrings;
  std::stringstream sstream(input);
  std::string substring;

  while (std::getline(sstream, substring, delim))
    if (substring.size() > 0)
      substrings.push_back(substring);

  return substrings;
}


} // namespace uofmsh
