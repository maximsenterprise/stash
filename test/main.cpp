
#include "flux.hpp"
#include <iostream>
#include <string>

int main() {
    std::string html = flux::get_html("example.com");
    std::cout << html << std::endl;
    std::cout << "----------" << std::endl;
    std::string response = flux::wait_data("https://httpbin.org/forms/post");
    std::cout << response << std::endl;
    return 0;
}
