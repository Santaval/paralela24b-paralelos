// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include <vector>
#include "HttpResponse.hpp"


/**
 * @class HttpPendingRequest
 * @brief Represents a pending HTTP request with associated results and response.
 * 
 * This class manages the state of a pending HTTP request, including the results,
 * request numbers, and the response object. It provides an interface for building
 * the response.
 * 
 * @var std::vector<std::vector<int>> HttpPendingRequest::results
 * Vector of vectors to store the results of the request.
 * 
 * @var std::vector<int> HttpPendingRequest::numbers
 * Vector to store the request numbers.
 * 
 * @var int HttpPendingRequest::processedCount
 * Counter to keep track of the number of processed numbers.
 * 
 * @var HttpResponse HttpPendingRequest::response
 * The response object associated with this request.
 * 
 * @fn HttpPendingRequest::HttpPendingRequest(const int count, HttpResponse response)
 * @brief Constructs a new HttpPendingRequest object.
 * 
 * @param count The number of results and numbers to initialize.
 * @param response The HttpResponse object associated with this request.
 * 
 * @fn HttpPendingRequest::~HttpPendingRequest()
 * @brief Destroys the HttpPendingRequest object.
 * 
 * @fn virtual std::string HttpPendingRequest::buildResponse() = 0
 * @brief Pure virtual function to build the response.
 * 
 * @return A string representing the built response.
 */
class HttpPendingRequest {
 protected:
        /// results (vector of vector of int)
        std::vector<std::vector<int64_t>> results;
        /// request numbers
        std::vector<int> numbers;
        /// processed numbers counter
        int processedCount;
        /// response object
        HttpResponse response;

 public:
        /// default constructor
        explicit HttpPendingRequest(HttpResponse response)
                : response(response) {
        }

        /**
         * @brief Constructs a new HttpPendingRequest object.
         * 
         * @param count The number of results and numbers to initialize.
         * @param response The HttpResponse object associated with this request.
         */
        HttpPendingRequest(const int count, HttpResponse response) :
            results(count),
            numbers(count),
            processedCount(0),
            response(response) {
                this->results.clear();
                this->numbers.clear();
        }
        /// destructor
        ~HttpPendingRequest() {
        }

        /**
         * @brief Pure virtual function to build the HTML response.
         * 
         * @return A string representing the built response.
         */
        virtual void sendResponse() = 0;

        /**
         * @brief Pushes a number to the numbers vector.
         * 
         * @param result The result to push.
         */
        void pushNUmber(int number);

        /**
         * @brief Pushes a result to the results vector in the specified index.
         * 
         * @param index The index of the result vector.
         * @param result The result to push.
         */

        void pushResult(int index, std::vector<int64_t> result);

        /// getter for the results vector
        std::vector<std::vector<int64_t>> getResults() {
            return results;
        }

        /// getter for the numbers vector
        std::vector<int> getNumbers() {
            return numbers;
        }

        /// getter for the processedCount
        int getProcessedCount() {
            return processedCount;
        }

        /// getter for the response object
        HttpResponse getResponse() {
            return response;
        }

        /// increases the processedCount by 1
        void increaseProcessedCount() {
            processedCount++;
        }
};
