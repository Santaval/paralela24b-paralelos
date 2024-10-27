#include "Packer.hpp"

void Packer::consume(Calculator* calculator) {
  HttpPendingRequest* pendingRequest = calculator->getPendingRequest();
  pendingRequest->increaseProcessedCount();

  if (pendingRequest->getProcessedCount() == pendingRequest->getNumbers().size()) {
    this->produce(pendingRequest);
  }
  delete calculator;
}

int Packer::run() {
  this->consumeForever();
  return 0;
}