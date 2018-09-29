#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

namespace uofmsh {
namespace helpers {

// Split a string by the delimiters
std::vector<std::string> split(const std::string &input, const std::string &delims);

// Trims delimiters from a string
void trim(std::string &str, const std::string &delims);

} // namespace helpers
} // namespace uofmsh

#endif

