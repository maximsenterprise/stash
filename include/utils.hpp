/*
 utils.hpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Utilities for the Stash Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
namespace stash {

std::string trim_start(const std::string &str);
std::string trim_end(const std::string &str);
std::string trim(const std::string &str);
std::vector<std::string> split(const std::string &str, char delim);

} // namespace stash

#endif // UTILS_HPP
