#pragma once 

#include "HttpPendingRequest.hpp"

class FactPendingRequest : public HttpPendingRequest {
    public:
        /**
         * @brief Constructs a new FactPendingRequest object.
         * 
         * @param count The number of results and numbers to initialize.
         * @param response The HttpResponse object associated with this request.
         */
        FactPendingRequest(const int count, HttpResponse response) :
            HttpPendingRequest(count, response) {}

        /**
         * @brief Destroys the FactPendingRequest object.
         */
        ~FactPendingRequest() {}

        /**
         * @brief Builds the response for the fact request.
         * 
         * @return A string representing the built response.
         */
        std::string buildResponse() override;
};