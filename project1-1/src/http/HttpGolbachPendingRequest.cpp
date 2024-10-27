// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpGolbachPendingRequest.hpp"

std::stringstream HttpGolbachPendingRequest::buildResponse() {
    // Response
    std::stringstream body;
    for (ino64_t i = 0; i <= numbers.size()-1; i++) {
        std::string title = "The Goldbach of " + this->numbers[i];
        body << "<h1>" << title << "</h1>\n";
        if (this->numbers[i]%2 == 0) {
            for (ino64_t j = 0; j <= this->results[i].size(); j++) {
                body << "<span >" << this->results[i][j] << "+"
                << this->results[i][j+1];
            }
        } else {
            for (ino64_t j = 0; j <= this->results[i].size(); j++) {
                body << "<span >" << this->results[i][j] << "+"
                << this->results[i][j+1] << "+"
                << this->results[i][j+2];
            }
        }
        body << "<\n>";
    }
    return body;
}
