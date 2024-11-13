/*
 render.cpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Render functions
 Copyright (c) 2024 Maxims Enterprise
*/

#include "convex.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

namespace convex {

std::vector<HTMLComponent *>
get_components(const std::vector<HTMLNode> &nodes_in) {
    std::vector<HTMLComponent *> components;
    for (const auto &node : nodes_in) {
        if (node.tag == "h1") {
            auto *component = new TextHTMLComponent;
            component->text = node.content;
            component->size = 32;
            component->bold = true;
            components.push_back(component);
        } else if (node.tag == "h2") {
            auto *component = new TextHTMLComponent;
            component->text = node.content;
            component->size = 24;
            component->bold = true;
            components.push_back(component);
        } else if (node.tag == "h3") {
            auto *component = new TextHTMLComponent;
            component->text = node.content;
            component->size = 18;
            component->bold = true;
            components.push_back(component);
        } else if (node.tag == "h4") {
            auto *component = new TextHTMLComponent;
            component->text = node.content;
            component->size = 16;
            component->bold = true;
            components.push_back(component);
        } else if (node.tag == "h5") {
            auto *component = new TextHTMLComponent;
            component->text = node.content;
            component->size = 14;
            component->bold = true;
            components.push_back(component);
        } else if (node.tag == "h6") {
            auto *component = new TextHTMLComponent;
            component->text = node.content;
            component->size = 12;
            component->bold = true;
            components.push_back(component);
        } else if (node.tag == "p") {
            auto *component = new TextHTMLComponent;
            component->text = node.content;
            component->size = 16;
            components.push_back(component);
        } else if (node.tag == "html" || node.tag == "body" ||
                   node.tag == "div") {
            auto child_components = get_components(node.children);
            components.insert(components.end(), child_components.begin(),
                              child_components.end());
        } else {
            stash::error("Component " + node.tag +
                         " not supported yet by Convex");
        }
    }
    return components;
}
void render_to_screen(std::vector<HTMLNode> nodes) {
    std::vector<HTMLComponent *> components = get_components(nodes);
    stash::log("convex", "Rendering " + std::to_string(components.size()) +
                             " components");
#ifdef __APPLE__
    open_app(components);
#endif
}

} // namespace convex
