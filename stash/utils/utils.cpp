
#include "utils.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace stash {

std::string trim(const std::string &str) { return trim_start(trim_end(str)); }

std::string trim_start(const std::string &str) {
    size_t start = 0;
    while (start < str.length() && str[start] == ' ') {
        start++;
    }
    return str.substr(start);
}

std::string trim_end(const std::string &str) {
    size_t end = str.length();
    while (end > 0 && str[end - 1] == ' ') {
        end--;
    }
    return str.substr(0, end);
}

std::vector<std::string> split(const std::string &str, char delim) {
    std::vector<std::string> parts;
    std::string part;
    std::istringstream stream(str);
    while (std::getline(stream, part, delim)) {
        parts.push_back(part);
    }
    return parts;
}

} // namespace stash
