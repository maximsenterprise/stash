/*
 parse_html.cpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: HTML parser for Convex
 Copyright (c) 2024 Maxims Enterprise
*/

#include "convex.hpp"
#include "utils.hpp"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace convex {

std::vector<HTMLNode> parse_html(const std::string &original_html) {
    std::string html = "";
    for (auto line : stash::split(original_html, '\n')) {
        html += stash::trim(line);
    }
    size_t pos = 0;
    std::vector<HTMLTag> tags;
    while (pos < html.length()) {
        std::string tag_name;
        size_t tag_start = html.find("<", pos);
        if (tag_start == std::string::npos) {
            break;
        }

        size_t tag_end = html.find(">", tag_start);
        if (tag_end != std::string::npos) {
            tag_name = html.substr(pos + 1, tag_end - tag_start - 1);
        } else {
            break;
        }

        std::string content = "";
        size_t next_tag = html.find("<", tag_end);
        if (next_tag != std::string::npos) {
            content = html.substr(tag_end + 1, next_tag - tag_end - 1);
        } else {
            content = html.substr(tag_end + 1);
        }

        HTMLTag tag;
        if (tag_name[0] == '/') {
            tag.closes = true;
            tag_name = tag_name.substr(1);
        } else {
            tag.closes = false;
        }
        if (tag_name.find(" ") != std::string::npos) {
            std::string options = tag_name.substr(tag_name.find(" ") + 1);
            tag_name = tag_name.substr(0, tag_name.find(" "));
            std::string option;
            std::istringstream stream(options);
            while (std::getline(stream, option, ' ')) {
                std::string key = option.substr(0, option.find("="));
                std::string value = option.substr(option.find("=") + 1);
                tag.options.push_back({key, value});
            }
        }

        tag.value = content;
        tag.name = tag_name;
        pos = next_tag;
        tags.push_back(tag);
    }

    std::vector<HTMLTag> open = {};   // For open tags
    std::vector<HTMLNode> nodes = {}; // For the final nodes
    std::vector<HTMLNode> carry = {}; // For carrying open tags
    HTMLTag *temp = nullptr;

    for (auto &tag : tags) {
        if (temp != nullptr && temp->name == tag.name && tag.closes) {
            HTMLNode node;
            node.tag = tag.name;
            node.options = temp->options;
            node.content = temp->value;
            node.children = {};
            temp = nullptr;
            if (open.size() != 0) {
                carry.push_back(node);
            } else {
                nodes.push_back(node);
            }
        } else if (temp != nullptr) {
            open.push_back(*temp);
            temp = nullptr;
        }

        if (tag.closes) {
            for (int j = open.size() - 1; j >= 0; j--) {
                if (open[j].name == tag.name) {
                    HTMLNode node;
                    node.tag = tag.name;
                    node.options = open[j].options;
                    node.content = open[j].value;
                    node.children = carry;
                    carry = {};
                    open.erase(open.begin() + j);
                    if (open.size() != 0) {
                        carry.push_back(node);
                    } else {
                        nodes.push_back(node);
                    }
                    break;
                }
            }
        } else {
            temp = &tag;
        }
    }
    return nodes;
}

} // namespace convex
