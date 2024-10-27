// Copyright 2024 Isaias Alfaro Ugalde

#include "GoldCal.hpp"

GoldCal::GoldCal() {
}
GoldCal::~GoldCal() {
}
std::vector <int64_t> GoldCal::get_result() {
  return this->result;
}
void GoldCal::Calc(int64_t number) {
  this->result.clear();
  this->exist.clear();
  if ((number%2) == 0 && number > 2) {
    Calc_Goldbach(number);
  } else if (number > 8) {
    Calc_Goldbach_Weak(number);
  } else {
    this->result.push_back(0);
    this->result.push_back(0);
  }
}
void GoldCal::Calc_Goldbach(int64_t number) {
  for (int64_t n1 = 2; n1 <= number / 2; ++n1) {
    int64_t n2 = number - n1;
    if ((Prime(n1) && Prime(n2)) && IsUnique(n1)) {
      this->result.push_back(n1);
      this->result.push_back(n2);
    }
  }
}
void GoldCal::Calc_Goldbach_Weak(int64_t number) {
  for (int64_t n1 = 2; n1 <= number; ++n1) {
    if (Prime(n1)) {
      for (int64_t n2 = 2; n2 <= number; ++n2) {
        if (Prime(n2)) {
          int64_t n3 = number - n1 - n2;
          if ((n3 > 1 && Prime(n3)) && IsUnique(n1)) {
            this->result.push_back(n1);
            this->result.push_back(n2);
            this->result.push_back(n3);
          }
        }
      }
    }
  }
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
bool GoldCal::IsUnique(int64_t number) {
  for (size_t i = 0; i < this->result.size(); i += 2) {
    if (result[i] == number) {
      return false;
    }
  }
  return true;
}

