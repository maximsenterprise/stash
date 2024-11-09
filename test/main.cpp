
#include "convex.hpp"
#include "flux.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string path = "test/test.html";
    std::ifstream file(path);
    std::string html;
    std::string line;
    while (std::getline(file, line)) {
        html += line + "\n";
    }
    file.close();

    std::vector<convex::HTMLNode> nodes = convex::parse_html(html);
    for (auto node : nodes) {
        convex::print_node(node);
    }
}
