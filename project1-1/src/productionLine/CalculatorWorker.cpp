// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "CalculatorWorker.hpp"
#include "Log.hpp"

int CalculatorWorker::run() {
  this->consumeForever();
  Log::append(Log::INFO, "CalculatorWorker", "stop");
  return 0;
}

void CalculatorWorker::consume(Calculator* Calc) {
  int index = Calc->getCalcIndex();
  int number = Calc->getPendingRequest()->getNumber(index);
  Calc->getPendingRequest()->pushResult(index, Calc->calculate(number));
  this->produce(Calc);
}
