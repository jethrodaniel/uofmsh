#include "helpers.hpp"

namespace uofmsh {
namespace helpers {

/* Splits a string by a string of delimiters into a vector of substrings
 *
 * @param input     the string to split
 * @param delim     the delimiters to split by
 *
 * @return          the substrings from the split
 */
std::vector<std::string> split(const std::string input, const std::string delims) {
  std::vector<std::string> substrings;
  std::string substring;
  std::size_t current, previous = 0;

  current = input.find_first_of(delims);
  while (current != std::string::npos) {
    substring = input.substr(previous, current - previous);

    if (substring.size() > 0)
      substrings.push_back(substring);

    previous = current + 1;
    current = input.find_first_of(delims, previous);
  }

  substring = input.substr(previous, current - previous);

  if (substring.size() > 0)
    substrings.push_back(substring);

  return substrings;
}

/* Trims leading and trailing occurances of characters from a string
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

} // namespace helpers
} // namespace uofmsh
