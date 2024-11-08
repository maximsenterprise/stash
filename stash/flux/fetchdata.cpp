/*
 fetchdata.cpp
 As part of the Stash project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Fetch Data from URL or IP
 Copyright (c) 2024 Maxims Enterprise
*/

#include "flux.hpp"
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 80 // for HTTP

namespace flux {

std::string wait_data(std::string url) {
    struct sockaddr_in server_addr;
    struct hostent *server;
    
    // First, remove the protocol
    if (url.rfind("http://", 0) == 0) {
        url = url.substr(7);
    } else if (url.rfind("https://", 0) == 0) {
        url = url.substr(8);
    }

    // Next, resolve and remove the path 
    std::string path = "/";
    size_t path_start = url.find("/");
    if (path_start != std::string::npos) {
        path = url.substr(path_start);
        url = url.substr(0, path_start);
    }

    // Create the socket and initialize the server to recieve data
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return "";
    }
    
    // Get the host by name
    server = gethostbyname(url.c_str());
    if (server == nullptr) {
        std::cerr << "Error, no such host" << std::endl;
        return "";
    }
    
    // Initialize the server address
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(PORT);
    
    // Connect to the server and request data
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error connecting" << std::endl;
        return "";
    } 
    
    // Create request headers
    std::stringstream request;
    request << "GET " << path <<  " HTTP/1.1\r\n";
    request << "Host: " << url << "\r\n";
    request << "Connection: close\r\n\r\n";
    
    // Send the request headers and read the response
    ssize_t bytes_sent = send(sockfd, request.str().c_str(), request.str().length(), 0);
    if (bytes_sent < 0) {
        std::cerr << "Error writing to socket" << std::endl;
        return "";
    }

    char buffer[1024];
    ssize_t bytes_received;
    std::string response;
    while ((bytes_received = recv(sockfd, buffer, 1024, 0)) > 0) {
        response.append(buffer, bytes_received); 
    }

    if (bytes_received < 0) {
        std::cerr << "Error reading from socket" << std::endl;
        return "";
    }
    
    // Close the socket and return the response
    shutdown(sockfd, SHUT_RDWR);
    return response;
}
std::string get_html(std::string url) {
    // Get data
    std::string server_response = flux::wait_data(url);
    if (server_response == "") {
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

}
