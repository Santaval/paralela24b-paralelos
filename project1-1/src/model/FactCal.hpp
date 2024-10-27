// Copyright 2024 Isaias Alfaro Ugalde

#ifndef _FACTCAL_HPP_
#define _FACTCAL_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * @brief Class that is responsible for calculating the factorial
 */
class FactCal {
 public:
  /// Constructor
  FactCal();
  /// Destructor
  ~FactCal();

  /**
 * @brief Method that is responsible for calculating the factorial
 * @param number Input extracted from the URL
 */
  std::vector<int64_t> Calculator_Factorial(int64_t number);

  /**
  * @brief Formatting method for displaying the result
  * @param factors Vector whit all resulting numbers from Factorial 
  */
  std::vector<int64_t> Format_numbers(std::vector<int64_t> factors);
};

#endif  // _FACTCAL_HPP_
