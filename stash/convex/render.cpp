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

namespace convex {

void render_to_screen(std::vector<HTMLNode> nodes) {
    std::vector<HTMLComponent *> components;
    for (auto node : nodes) {
        if (node.tag == "h1") {
            TextHTMLComponent component;
            component.text = node.content;
            component.size = 32;
            component.bold = true;
            components.push_back(&component);
        } else if (node.tag == "h2") {
            TextHTMLComponent component;
            component.text = node.content;
            component.size = 24;
            component.bold = true;
            components.push_back(&component);
        } else if (node.tag == "h3") {
            TextHTMLComponent component;
            component.text = node.content;
            component.size = 18;
            component.bold = true;
            components.push_back(&component);
        } else if (node.tag == "h4") {
            TextHTMLComponent component;
            component.text = node.content;
            component.size = 16;
            component.bold = true;
            components.push_back(&component);
        } else if (node.tag == "h5") {
            TextHTMLComponent component;
            component.text = node.content;
            component.size = 14;
            component.bold = true;
            components.push_back(&component);
        } else if (node.tag == "h6") {
            TextHTMLComponent component;
            component.text = node.content;
            component.size = 12;
            component.bold = true;
            components.push_back(&component);
        } else if (node.tag == "p") {
            TextHTMLComponent component;
            component.text = node.content;
            component.size = 16;
            components.push_back(&component);
        } else {
            stash::error("Component " + node.tag +
                         " not supported yet by Convex");
        }
    }
    stash::log("convex", "Rendering " + std::to_string(components.size()) +
                             " components");
#ifdef __APPLE__
    open_app(components);
#endif
}

} // namespace convex
