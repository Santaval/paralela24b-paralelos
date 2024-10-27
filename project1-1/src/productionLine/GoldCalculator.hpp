// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include <vector>
#include "Calculator.hpp"
#include "../model/GoldCal.hpp"

class GoldCalculator : public Calculator {
 public:
  GoldCalculator(int64_t calcIndex, HttpPendingRequest* pendingRequest) :
      Calculator(calcIndex, pendingRequest) {}
  ~GoldCalculator() {}

  std::vector<int64_t> calculate(int number) override;
};
