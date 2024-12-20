// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include <string>
#include "HttpPendingRequest.hpp"

class HttpGolbachPendingRequest : public HttpPendingRequest {
 public:
    HttpGolbachPendingRequest() {}
    /**
     * @brief Constructs a new HttpGolbachPendingRequest object.
     * 
     * @param count The number of results and numbers to initialize.
     * @param response The HttpResponse object associated with this request.
     */
    HttpGolbachPendingRequest(const int count, HttpResponse response) :
            HttpPendingRequest(count, response) {}

    /**
     * @brief Destroys the HttpGolbachPendingRequest object.
     */
    ~HttpGolbachPendingRequest() {}

    std::string getType() override {
        return "goldbach";
    }

    /**
     * @brief Builds the response for the fact request.
     * 
     * @return A string representing the built response.
     */
    void sendResponse() override;
};
