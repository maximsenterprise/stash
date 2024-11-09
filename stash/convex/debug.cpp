/*
 debug.cpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Debugging features for developers
 Copyright (c) 2024 Maxims Enterprise
*/

#include "convex.hpp"
#include <iostream>

namespace convex {

void print_node(HTMLNode node, int indent) {
    std::string spaces = "";
    for (int i = 0; i < indent; i++) {
        spaces += "    ";
    }
    std::cout << spaces << "Tag: " << node.tag << std::endl;
    std::cout << spaces << "Content: " << node.content << std::endl;
    std::cout << spaces << "Options: {" << std::endl;
    for (auto option : node.options) {
        std::cout << spaces << "Key: " << option.key
                  << "; Value: " << option.value << std::endl;
    }
    std::cout << spaces << "}" << std::endl;

    std::cout << spaces << "Children: " << node.children.size() << std::endl;
    for (auto child : node.children) {
        print_node(child, indent + 1);
        std::cout << spaces << "    " << "------------" << std::endl;
    }
}

} // namespace convex
