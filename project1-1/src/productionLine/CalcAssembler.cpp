// Copyright 2024 Aaron Santana

#include <string>
#include <vector>
#include <cstdio>


#include "CalcAssembler.hpp"
#include "Socket.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"  // Include the header for NetworkAddress
#include "../webapp/ProductionLineWebApp.hpp"

CalcAssembler::CalcAssembler
  (std::vector<ProductionLineWebApp*> applications) {
    this->applications = applications;
}

void CalcAssembler::consume(Socket socket) {
    this->handleClientConnection(socket);
    return;
}

int CalcAssembler::run() {
    this->consumeForever();
    return 0;
}

void CalcAssembler::handleClientConnection(Socket& client) {
  CalcRequest request = this->parseRequestLine(client);
  if (request.number != -1) {
    Calculator* calculator = this->assembleCalculator(request);
    this->produce(calculator);
  }
}

CalcRequest CalcAssembler::parseRequestLine(Socket& client) {
  while (true) {
    std::string requestLine;
    if (!client.readLine(requestLine, '\n')) {
      Log::append(Log::ERROR, "CalcAssembler", "Failed to read from client");
      break;
    }
    Log::append(Log::INFO, "CalcAssembler", "Received line: " + requestLine);
    CalcRequest calcRequest;
    scanf(requestLine.c_str(), "%s,%p,%d,%d", calcRequest.type.c_str(), &calcRequest.pendingRequest,
      &calcRequest.numberIndex, &calcRequest.number);
    return calcRequest;
  }
  CalcRequest calcRequest;
}

Calculator* CalcAssembler::assembleCalculator(CalcRequest request) {
  for (size_t i = 0; i < this->applications.size(); i++) {
    Calculator* calculator = this->applications[i]->buildCalculator(request);
    if (calculator != nullptr) {
      return calculator;
    }
  }
  return nullptr;
}

