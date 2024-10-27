// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "CalculatorWorker.hpp"

void CalculatorWorker::consume(Calculator* Calc) {
  int index = Calc->getCalcIndex();
  int number = Calc->getPendingRequest()->getNumbers()[index];
  Calc->getPendingRequest()->pushResult(index, Calc->calculate(number));
  this->produce(Calc);
}
