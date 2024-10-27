// Copyright 2024 Isaias Alfaro Ugalde

#ifndef _GOLDCAL_HPP_
#define _GOLDCAL_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

 /**
 * @brief Class that is responsible for calculating Goldbach
 */
class GoldCal {
 private:
  std::set <int64_t> exist;

 public:
  /// Constructor
  GoldCal();
  /// Destructor
  ~GoldCal();
  /**
  * @brief Method that is responsible for calculating Goldbach
  * @param number Input extracted from the URL
  */
  std::vector <int64_t> Calc(int64_t number);
  /**
  * @brief Method that is responsible for calculating Goldbach base
  * @param number Number to calculate 
  */
  std::vector <int64_t> Calc_Goldbach(int64_t number);
  /**
  * @brief Method that is responsible for calculating Goldbach weak
  * @param number Number to calculate
  */
  std::vector <int64_t> Calc_Goldbach_Weak(int64_t number);
  /**
  * @brief Method that is responsible for calculating Goldbach weak
  * @param number Number to see if is prime
  */
  bool Prime(int64_t number);
  /**
  * @brief Method that see if a number is Unique
  */
  bool IsUnique(int64_t number, std::vector <int64_t>);
};





#endif  // _GOLDCAL_HPP_
