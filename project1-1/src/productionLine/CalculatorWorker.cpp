// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "CalculatorWorker.hpp"
#include "Log.hpp"

int CalculatorWorker::run() {
  this->consumeForever();
  Log::append(Log::INFO, "CalculatorWorker", "stop");

  this->produce(nullptr);
  return 0;
}

void CalculatorWorker::consume(Calculator* calculator) {
  Log::append(Log::INFO, "CalculatorWorker", "consume");
  calculator->calculate();
  this->produce(calculator);
}
