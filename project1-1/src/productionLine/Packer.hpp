// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include "../prodcons/Assembler.hpp"
#include "Calculator.hpp"
#include "../http/HttpPendingRequest.hpp"

class Packer : public Assembler<Calculator*, HttpPendingRequest*> {
  DISABLE_COPY(Packer);

 public:
  explicit Packer(Queue<Calculator*>* calculatorQueue = nullptr
    , Queue<HttpPendingRequest*>* httpPendingRequestQueue = nullptr
    , Calculator* stopCondition = nullptr)
    : Assembler<Calculator*, HttpPendingRequest*>
        (calculatorQueue, httpPendingRequestQueue, stopCondition) {
    this->createOwnQueue();
  }

  virtual ~Packer() {
  }

 protected:
    /// @brief Consume a Calculator and produce a HttpPendingRequest
    /// @param Calculator
    void consume(Calculator* Calculator) override;

    /// @brief Override of run method from Thread
    int run() override;
};
