#pragma once 

#include "HttpPendingRequest.hpp"

class HttpFactPendingRequest : public HttpPendingRequest {
    public:
        /**
         * @brief Constructs a new HttpFactPendingRequest object.
         * 
         * @param count The number of results and numbers to initialize.
         * @param response The HttpResponse object associated with this request.
         */
        HttpFactPendingRequest(const int count, HttpResponse response) :
            HttpPendingRequest(count, response) {}

        /**
         * @brief Destroys the HttpFactPendingRequest object.
         */
        ~HttpFactPendingRequest() {}

        /**
         * @brief Builds the response for the fact request.
         * 
         * @return A string representing the built response.
         */
        std::string buildResponse() override;
};