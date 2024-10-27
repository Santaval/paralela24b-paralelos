// Copyright 2024 Isaias Alfaro Ugalde

#include "GoldCal.hpp"

GoldCal::GoldCal() {
}
GoldCal::~GoldCal() {
}

std::vector <int64_t> GoldCal::Calc(int64_t number) {
  std::vector <int64_t> result;
  this->exist.clear();
  if ((number%2) == 0 && number > 2) {
    return (Calc_Goldbach(number));
  } else if (number > 8) {
    return (Calc_Goldbach_Weak(number));
  } else {
    result.push_back(0);
    result.push_back(0);
  }
  return result;
}
std::vector <int64_t> GoldCal::Calc_Goldbach(int64_t number) {
  std::vector <int64_t> result;
  for (int64_t n1 = 2; n1 <= number / 2; ++n1) {
    int64_t n2 = number - n1;
    if ((Prime(n1) && Prime(n2)) && IsUnique(n1, result)) {
      result.push_back(n1);
      result.push_back(n2);
    }
  }
  return result;
}
std::vector <int64_t> GoldCal::Calc_Goldbach_Weak(int64_t number) {
  std::vector <int64_t> result;
  for (int64_t n1 = 2; n1 <= number; ++n1) {
    if (Prime(n1)) {
      for (int64_t n2 = 2; n2 <= number; ++n2) {
        if (Prime(n2)) {
          int64_t n3 = number - n1 - n2;
          if ((n3 > 1 && Prime(n3)) && IsUnique(n1, result)) {
            result.push_back(n1);
            result.push_back(n2);
            result.push_back(n3);
          }
        }
      }
    }
  }
  return result;
}
bool GoldCal::Prime(int64_t number) {
  if (number <= 1) {
    return false;
  }
  for (int64_t i = 2; i <= std::sqrt(number); ++i) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}
bool GoldCal::IsUnique(int64_t number, std::vector <int64_t> result) {
  for (size_t i = 0; i < result.size(); i += 2) {
    if (result[i] == number) {
      return false;
    }
  }
  return true;
}

