/*
 fetchdata.cpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Fetch Data from URL or IP
 Copyright (c) 2024 Maxims Enterprise
*/

#include "flux.hpp"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <string>

namespace flux {

// Helper function to write data to a string
size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *userp) {
    size_t total_size = size * nmemb;
    userp->append((char *)contents, total_size);
    return total_size;
}

std::string wait_data(std::string url) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init(); // Initialize a CURL session
    if (!curl) {
        std::cerr << "Error initializing CURL" << std::endl;
        return "";
    }

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return "";
    }

    // Cleanup
    curl_easy_cleanup(curl);
    return response;
}

std::string get_html(std::string url) {
    // Get data
    std::string server_response = flux::wait_data(url);
    if (server_response.empty()) {
        return "";
    }

    // Find the start and end of the HTML
    ssize_t html_start = server_response.find("<!doctype html>");
    if (html_start == std::string::npos) {
        html_start = server_response.find("<html>");
    }

    if (html_start == std::string::npos) {
        return "";
    }

    size_t html_end = server_response.find("</html>", html_start);
    if (html_end == std::string::npos) {
        return "";
    }

    return server_response.substr(html_start, html_end - html_start + 7);
}

} // namespace flux
