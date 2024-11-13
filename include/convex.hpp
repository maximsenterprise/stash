/*
 convex.hpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Convex functions and data
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef CONVEX_HPP
#define CONVEX_HPP

#include <chrono>
#include <cstddef>
#include <ctime>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
namespace convex {

enum class HTMLType {
    H1,
};

struct HTMLOption {
    std::string key;
    std::string value;
};

struct HTMLTag {
    std::string name;
    std::vector<HTMLOption> options;
    bool closes;
    std::string value;
};

struct HTMLNode {
    std::string tag;
    HTMLType type;
    std::string content;
    std::vector<HTMLOption> options;
    std::vector<HTMLNode> children;
};

void render_html(std::string html);

static std::chrono::time_point started_render =
    std::chrono::high_resolution_clock::now();

// Parse the HTML string into a vector of HTMLNode objects
std::vector<HTMLNode> parse_html(const std::string &original_html);
std::string get_next_tag(const std::string &html, size_t &pos);
std::string get_text_content(const std::string &html, size_t &pos);
std::pair<std::string, std::vector<HTMLOption>>
parse_tag(const std::string &options);
void render_to_screen(std::vector<HTMLNode> nodes_in);

static std::unordered_set<std::string> autoClosingTags = {
    "area",  "base", "br",   "col",    "embed", "hr",  "img",
    "input", "link", "meta", "source", "track", "wbr", "rawincrustedtext"};

// Debugging purposes
void print_node(HTMLNode node, int indent = 0);

struct HTMLComponent {
    virtual ~HTMLComponent() = default;
};

struct TextHTMLComponent : public HTMLComponent {
    std::string text;
    std::string font = "Times New Roman";
    int size;
    bool bold = false;
};

std::vector<HTMLComponent *> get_components(const std::vector<HTMLNode> &nodes);

#ifdef __APPLE__
void open_app(std::vector<HTMLComponent *> nodes);
void render_text(TextHTMLComponent component);
#endif

} // namespace convex

#endif
