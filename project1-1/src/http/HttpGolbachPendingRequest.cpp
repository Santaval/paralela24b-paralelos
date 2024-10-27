// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpGolbachPendingRequest.hpp"

void HttpGolbachPendingRequest::sendResponse() {
    // Response
    for (ino64_t i = 0; i <= numbers.size()-1; i++) {
        this->response.body() << "The Goldbach of " << this->numbers[i] + " \n";
        if (this->numbers[i]%2 == 0) {
            for (ino64_t j = 0; j <= this->results[i].size(); j++) {
                this->response.body() << "<span >" << this->results[i][j] << "+"
                << this->results[i][j+1];
            }
        } else {
            for (ino64_t j = 0; j <= this->results[i].size(); j++) {
                this->response.body() << "<span >" << this->results[i][j] << "+"
                << this->results[i][j+1] << "+"
                << this->results[i][j+2];
            }
        }
        this->response.body() << "<\n>";
    }

    this->response.send();
}
