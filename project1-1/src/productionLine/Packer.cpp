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
  int calcWorkersCount = std::thread::hardware_concurrency();
  for (int i = 0; i < calcWorkersCount; i++) {
    this->consumeForever();
  }
  Log::append(Log::INFO, "Packer", "stop");
  this->produce(nullptr);
  return 0;
}
