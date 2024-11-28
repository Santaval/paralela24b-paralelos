// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "Assembler.hpp"
#include "Calculator.hpp"


class CalculatorWorker : public Assembler<Calculator*, Calculator*> {
 public:
  CalculatorWorker(Queue<Calculator*>* consumingQueue = nullptr,
      Queue<Calculator*>* producingQueue = nullptr)
    : Assembler(consumingQueue, producingQueue, nullptr) {
  }

  int run() override;
  void consume(Calculator*) override;
};
