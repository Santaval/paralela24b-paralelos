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
  // log request pendingRequest
  std::ostringstream oss;
  oss << request.pendingRequest;
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

    // line format: "type:string,pendingRequest:HttpPendingRequest*,numberIndex:int,number:int"

    std::istringstream lineStream(requestLine);
    std::string type, pendingRequest, numberIndexStr, numberStr;

    std::getline(lineStream, type, ',');
    std::getline(lineStream, pendingRequest, ',');
    std::getline(lineStream, numberIndexStr, ',');
    std::getline(lineStream, numberStr, ',');

    const int numberIndex = std::stoi(numberIndexStr);
    const int number = std::stoi(numberStr);

    // convert the string to a pointer
    std::uintptr_t address = std::stoull(pendingRequest, nullptr, 16);
    HttpPendingRequest* pointer = reinterpret_cast<HttpPendingRequest*>
      (address);
    CalcRequest calcRequest = CalcRequest(type, pointer, numberIndex, number);
    return calcRequest;
  }
  return CalcRequest("", nullptr, -1, -1);
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

