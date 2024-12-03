// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include <vector>

#include "Calculator.hpp"
#include "../model/FactCal.hpp"



class FactCalculator : public Calculator {
 public:
    FactCalculator() : Calculator() {}
    explicit FactCalculator(CalcRequest request) :
            Calculator(request) {}
    ~FactCalculator() {}

    std::vector<int64_t> calculate(int number) override;
};

