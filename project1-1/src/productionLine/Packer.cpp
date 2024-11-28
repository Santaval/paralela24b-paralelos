// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "Packer.hpp"
#include "Log.hpp"

void Packer::consume(Calculator* calculator) {
  HttpPendingRequest* pendingRequest = calculator->getPendingRequest();

  pendingRequest->increaseProcessedCount();


if (pendingRequest->getProcessedCount()
      == pendingRequest->getNumbersCount()) {
    this->produce(pendingRequest);
  }
  delete calculator;
}

int Packer::run() {
  this->consumeForever();
  return 0;
}
