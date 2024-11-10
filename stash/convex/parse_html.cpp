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
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace convex {

std::vector<HTMLNode> parse_html(const std::string &original_html) {
    started_render = std::chrono::high_resolution_clock::now();
    std::string html = "";
    for (auto line : stash::split(original_html, '\n')) {
        html += stash::trim(line);
    }
    std::cout << html << std::endl;
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
        HTMLTag *raw_tag = nullptr;
        if (tag_name[0] == '/') {
            tag.closes = true;
            tag_name = tag_name.substr(1);
            if (content != "") {
                raw_tag = new HTMLTag();
                raw_tag->name = "rawincrustedtext";
                raw_tag->value = content;
                raw_tag->closes = true;
                content = "";
            }
        } else {
            tag.closes = false;
        }

        if (tag_name.ends_with("/")) {
            tag.closes = true;
            tag_name = tag_name.substr(0, tag_name.length() - 1);
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
        if (raw_tag != nullptr) {
            tags.push_back(*raw_tag);
        }
    }

    std::vector<HTMLNode> nodes;
    std::vector<std::pair<HTMLTag, int>> open;
    std::vector<std::pair<HTMLNode, int>> carry;

    for (int i = 0; i < tags.size(); i++) {
        HTMLTag tag = tags[i];
        if (tag.name == "!doctype")
            continue;

        if (!tag.closes) {
            // Guardar el tag abierto junto con su índice en `open`
            open.push_back({tag, i});
        } else {
            bool found = false;
            for (int j = open.size() - 1; j >= 0; j--) {
                if (open[j].first.name == tag.name) {
                    HTMLNode node;
                    node.tag = open[j].first.name;
                    node.options = open[j].first.options;
                    node.content = open[j].first.value;
                    node.children = {};

                    // Transferir nodos hijos de carry a este nodo
                    for (auto it = carry.begin(); it != carry.end();) {
                        if (it->second > open[j].second && it->second < i) {
                            node.children.push_back(it->first);
                            it = carry.erase(it); // Usar iterador para eliminar
                                                  // sin problema de índice
                        } else {
                            ++it;
                        }
                    }

                    carry.push_back({node, i});
                    open.erase(open.begin() + j); // Eliminar el tag abierto
                    found = true;
                    break;
                }
            }

            // Manejo de autoClosingTags si no se encontró un tag que cierre
            if (!found &&
                autoClosingTags.find(tag.name) != autoClosingTags.end()) {
                HTMLNode node;
                node.tag = tag.name;
                node.options = tag.options;
                node.content = tag.value;
                node.children = {};
                carry.push_back({node, i});
            }
        }
    }
    for (auto pair : carry) {
        nodes.push_back(pair.first);
    }

    return nodes;
    std::cout << nodes.size() << std::endl;
    return nodes;
}

} // namespace convex
