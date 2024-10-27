#pragma once 
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
        Calculator(int64_t calcIndex, HttpPendingRequest* pendingRequest) : calcIndex(calcIndex), pendingRequest(pendingRequest) {}
        // Destructor
        virtual ~Calculator() {}

        // Calculate the number
        virtual std::vector<int> calculate() = 0;
};

