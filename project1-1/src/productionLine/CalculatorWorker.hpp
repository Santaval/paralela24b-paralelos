// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "Consumer.hpp"
#include "Calculator.hpp"
#include "Producer.hpp"


class CalculatorWorker : public Consumer<Calculator*>,
    public Producer<Calculator*> {
  int run() override;
  void consume(Calculator*) override;
};