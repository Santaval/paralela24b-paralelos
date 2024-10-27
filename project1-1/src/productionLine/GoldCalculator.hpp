// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include "Calculator.hpp"

class GoldCalculator : public Calculator {
 public:
  GoldCalculator(int64_t calcIndex, HttpPendingRequest* pendingRequest) :
      Calculator(calcIndex, pendingRequest) {}
  ~GoldCalculator();

  std::vector<int> calculate(int number) override;
};
