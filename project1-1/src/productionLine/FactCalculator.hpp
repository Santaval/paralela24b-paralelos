#pragma once

#include <vector>

#include "Calculator.hpp"
#include "../model/FactCal.hpp"



class FactCalculator : public Calculator {
 public:
    FactCalculator() : Calculator() {}
    FactCalculator(int64_t calcIndex, HttpPendingRequest* pendingRequest) :
            Calculator(calcIndex, pendingRequest) {}
    ~FactCalculator() {}

    std::vector<int64_t> calculate(int number) override;
};

