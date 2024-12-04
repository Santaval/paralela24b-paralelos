// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include <vector>
#include "Calculator.hpp"
#include "../model/GoldCal.hpp"

class GoldCalculator : public Calculator {
 public:
  GoldCalculator() {}

  explicit GoldCalculator(CalcRequest request) :
      Calculator(request) {}
  ~GoldCalculator() {}

  void calculate() override;
};
