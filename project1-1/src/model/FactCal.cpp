// Copyright 2024 Isaias Alfaro Ugalde

#include "FactCal.hpp"

FactCal::FactCal() {
}

FactCal::~FactCal() {
}

std::vector <int64_t> FactCal::get_Factorial() {
  return this->Factorial;
}

void FactCal::Calculator_Factorial(int64_t number) {
  int64_t first = number;
  std::vector<int64_t> factors;
  this->Factorial.clear();
  if (number < 2) {
    this->Factorial.push_back(0);
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
    FactCal::Format_numbers(factors);
  }
}

void FactCal::Format_numbers(std::vector<int64_t> factors) {
  while (!factors.empty()) {
    int64_t current_factor = factors[0];
    this->Factorial.push_back(current_factor);
    int count = std::count(factors.begin(), factors.end(), current_factor);
    this->Factorial.push_back(count);
    factors.erase(std::remove(factors.begin(),
        factors.end(), current_factor), factors.end());
  }
}

