// Copyright 2024 Isaias Alfaro Ugalde

#ifndef _ROOT_FACTCAL_HPP_
#define _ROOT_FACTCAL_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class FactCal {
 public:
  /// attributes
  std::string Factorial;
  /// Constructor
  FactCal();
  /// Destructor
  ~FactCal();

  void Calculator_Factorial(int64_t number);

  std::string get_Factorial();

  void Format_numbers(std::vector<std::string> factors);
};

#endif  // _ROOT_FACTCAL_HPP_
