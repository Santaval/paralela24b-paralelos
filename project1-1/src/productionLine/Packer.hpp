// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include "../prodcons/Assembler.hpp"
#include "../http/HttpPendingRequest.hpp"

class Packer : public Assembler<HttpPendingRequest*, HttpPendingRequest*> {
  DISABLE_COPY(Packer);

 public:
  explicit Packer(Queue<HttpPendingRequest*>* calculatorQueue = nullptr
    , Queue<HttpPendingRequest*>* httpPendingRequestQueue = nullptr
    , HttpPendingRequest* stopCondition = nullptr)
    : Assembler<HttpPendingRequest*, HttpPendingRequest*>
        (calculatorQueue, httpPendingRequestQueue, stopCondition) {
    this->createOwnQueue();
  }

  virtual ~Packer() {
  }

 protected:
    /// @brief Consume a Calculator and produce a HttpPendingRequest
    /// @param Calculator
    void consume(HttpPendingRequest* Calculator) override;

    /// @brief Override of run method from Thread
    int run() override;
};
