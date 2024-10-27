#pragma once

#include "Calculator.hpp"
#include <vector>

class FactCalculator : public Calculator {
 public:
    FactCalculator() : Calculator() {}
    FactCalculator(int64_t calcIndex, HttpPendingRequest* pendingRequest) :
            Calculator(calcIndex, pendingRequest) {}
    ~FactCalculator() {}

    std::vector<int> calculate(int number) override;
};

