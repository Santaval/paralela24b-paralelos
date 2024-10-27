// Copyright 2024 Aaron Santana, Isaias Alfaro
#include "HttpFactPendingRequest.hpp"

std::stringstream HttpFactPendingRequest::buildResponse() {
    // Response
    std::stringstream body;
    for (ino64_t i = 0; i <= numbers.size()-1; i++) {
        std::string title = "The factorial of " + this->numbers[i];
        body << "<h1>" << title << "</h1>\n";
        for (ino64_t j = 0; j <= this->results[i].size(); j++) {
            body << "<span >" << this->results[i][j] << "<sup>"
            << this->results[i][j+1] << "</sup></span>";
        }
        body << "<\n>";
    }
    return body;
}
