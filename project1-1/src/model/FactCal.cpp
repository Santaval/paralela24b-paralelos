// Copyright 2024 Isaias Alfaro Ugalde

#include "FactCal.hpp"

FactCal::FactCal() {
}

FactCal::~FactCal() {
}

std::string FactCal::get_Factorial() {
  return this->Factorial;
}

void FactCal::Calculator_Factorial(int64_t number) {
  int64_t first = number;
  std::vector<std::string> factors;
  this->Factorial = "";
  if (number < 2) {
    Factorial = "false";
  } else {
    while (first > 1) {
      for (int64_t i = 2; i <= first; i++) {
        if ((first % i) == 0) {
          factors.push_back(std::to_string(i));
          first = first/i;
          break;
        }
      }
    }
    FactCal::Format_numbers(factors);
  }
}

void FactCal::Format_numbers(std::vector<std::string> factors) {
  while (!factors.empty()) {
    std::string current_factor = factors[0];
    this->Factorial += current_factor + " ";
    int count = std::count(factors.begin(), factors.end(), current_factor);
    this->Factorial += std::to_string(count) + " ";
    factors.erase(std::remove_if(factors.begin(), factors.end(),
        [current_factor](const std::string& x)
        { return x == current_factor; }),
        factors.end());
  }
}

