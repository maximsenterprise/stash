/*
 flux.hpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Flux header and functions
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef FLUX_HPP
#define FLUX_HPP

#include <cstddef>
#include <string>
namespace flux {

std::string wait_data(std::string url);
std::string get_html(std::string url);

} // namespace flux

#endif
