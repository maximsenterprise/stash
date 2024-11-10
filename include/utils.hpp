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

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define GREEN "\033[32m"

std::string trim_start(const std::string &str);
std::string trim_end(const std::string &str);
std::string trim(const std::string &str);
std::vector<std::string> split(const std::string &str, char delim);

void error(const std::string &message);
void warning(const std::string &message);
void log(const std::string &emmiter, const std::string &message);

} // namespace stash

#endif // UTILS_HPP
