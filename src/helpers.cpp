#include "helpers.hpp"

#include <iostream>
#include <sstream>

namespace uofmsh {

/* Splits a string by a single character delimiter into a vector of substrings
 *
 * @param input     the string to split
 * @param delim     the delimiter to split by
 *
 * @return          the substrings from the split
 */
std::vector<std::string> split(const std::string input, const char delim) {
  std::vector<std::string> substrings;
  std::stringstream        sstream(input);
  std::string              substring;

  while (std::getline(sstream, substring, delim))
    if (substring.size() > 0)
      substrings.push_back(substring);

  return substrings;
}

/* Trims leading and trailing occurances of specific characters from a string
 *
 * @param str             the string to trim
 * @param unwanted_chars  the characters to trim from the string
 */
void trim(std::string& str, const std::string unwanted_chars) {
  // Remove any occurences starting from the right
  str.erase(str.find_last_not_of(unwanted_chars) + 1);

  // Remove any occurences starting from the left
  str.erase(0, str.find_first_not_of(unwanted_chars));
}

} // namespace uofmsh
