// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include <vector>

#include "../http/HttpPendingRequest.hpp"


class Calculator {
 protected:
        // Number to calculate
        int64_t calcIndex;
        // Pending request to calculate
        HttpPendingRequest* pendingRequest;

 public:
        // default constructor
        Calculator() {}

        // Constructor
        Calculator(int64_t calcIndex, HttpPendingRequest* pendingRequest)
            : calcIndex(calcIndex), pendingRequest(pendingRequest) {}
        // Destructor
        virtual ~Calculator() {}

        // Calculate the number
        virtual std::vector<int64_t> calculate(int number) = 0;

        /// Get calcIndex
        int64_t getCalcIndex() const {
            return calcIndex;
        }
        /// Get pendingRequest
        HttpPendingRequest* getPendingRequest() const {
            return pendingRequest;
        }
};

