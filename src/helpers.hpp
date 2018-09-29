#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

namespace uofmsh {

std::vector<std::string> split(const std::string input, const std::string delims);

void trim(std::string &str, std::string delims);

} // namespace uofmsh

#endif

