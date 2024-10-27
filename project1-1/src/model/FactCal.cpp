// Copyright 2024 Isaias Alfaro Ugalde

#include "FactCal.hpp"

FactCal::FactCal() {
}

FactCal::~FactCal() {
}


std::vector<int64_t> FactCal::Calculator_Factorial(int64_t number) {
  int64_t first = number;
  std::vector<int64_t> factors;
  if (number < 2) {
    factors.push_back(0);
    return factors;
  } else {
    while (first > 1) {
      for (int64_t i = 2; i <= first; i++) {
        if ((first % i) == 0) {
          factors.push_back(i);
          first = first/i;
          break;
        }
      }
    }
    return (FactCal::Format_numbers(factors));
  }
}

std::vector<int64_t> FactCal::Format_numbers(std::vector<int64_t> factors) {
  std::vector<int64_t> Factorial;
  while (!factors.empty()) {
    int64_t current_factor = factors[0];
    Factorial.push_back(current_factor);
    int count = std::count(factors.begin(), factors.end(), current_factor);
    Factorial.push_back(count);
    factors.erase(std::remove(factors.begin(),
        factors.end(), current_factor), factors.end());
  }
  return Factorial;
}

