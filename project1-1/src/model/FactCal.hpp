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
 private:
  /// attributes
  std::vector <int64_t> Factorial;

 public:
  /// Constructor
  FactCal();
  /// Destructor
  ~FactCal();

  /**
 * @brief Method that is responsible for calculating the factorial
 * @param number Input extracted from the URL
 */
  void Calculator_Factorial(int64_t number);

  /**
 * @brief Method that returnal factorial
 */
  std::vector <int64_t> get_Factorial();

  /**
  * @brief Formatting method for displaying the result
  * @param factors Vector whit all resulting numbers from Factorial 
  */
  void Format_numbers(std::vector<int64_t> factors);
};

#endif  // _FACTCAL_HPP_
