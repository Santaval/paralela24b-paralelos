// Copyright 2024 Aaron Santana, Isaias Alfaro
#include "HttpFactPendingRequest.hpp"

void HttpFactPendingRequest::sendResponse() {
    // Response
    for (ino64_t i = 0; i <= numbers.size()-1; i++) {
        this->response.body() << "The factorial of " << this->numbers[i] + " \n";
        for (ino64_t j = 0; j <= this->results[i].size(); j++) {
            this->response.body() << "<span >" << this->results[i][j] << "<sup>"
            << this->results[i][j+1] << "</sup></span>";
        }
        this->response.body() << "<\n>";
    }
    this->response.send();
}
