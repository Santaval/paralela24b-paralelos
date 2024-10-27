// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

std::vector<int> FactCalculator::calculate(int number) {
  std::vector<int> factors;
  for (int i = 1; i <= number; i++) {
    if (number % i == 0) {
      factors.push_back(i);
    }
  }
  return factors;
}
