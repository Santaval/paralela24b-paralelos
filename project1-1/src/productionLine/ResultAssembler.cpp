// Copyright Aaron Santana Valdelomar 2024 Universidad de Costa Rica
#include <string>
#include "ResultAssembler.hpp"
#include "Log.hpp"


ResultAssembler::ResultAssembler(int slavesNodesCount)
: slavesNodesCount(slavesNodesCount) {
}

ResultAssembler::~ResultAssembler() {
}

int ResultAssembler::run() {
    this->listenForConnections("8082");
    this->acceptAllConnections();
    return 0;
}

void ResultAssembler::handleClientConnection(Socket& client) {
    CalcResult result = this->parseRequestLine(client);
    if (result == CalcResult()) {
      if (++this->stopConditionsCount == this->slavesNodesCount) {
      this->produce(nullptr);
      this->stopListening();
      }
      return;
    }
    result.pendingRequest->pushResult(result.numberIndex, result.result);
    this->produce(result.pendingRequest);
}

CalcResult ResultAssembler::parseRequestLine(Socket& client) {
    while (true) {
    std::string requestLine;
    if (!client.readLine(requestLine, '\n')) {
      Log::append(Log::ERROR, "CalcAssembler", "Failed to read from client");
      break;
    }

    // line format: "pendingRequest:HttpPendingRequest*,
    // numberIndex:int,resultSize:int,result:int[]"
    CalcResult calcResult;
    std::istringstream lineStream(requestLine);
    std::string pendingRequest, numberIndex, resultSize;

    std::getline(lineStream, pendingRequest, ',');
    std::getline(lineStream, numberIndex, ',');
    std::getline(lineStream, resultSize, ',');

    calcResult.numberIndex = std::stoi(numberIndex);
    calcResult.resultSize = std::stoi(resultSize);

    // convert the string to a pointer
    std::uintptr_t address = std::stoull(pendingRequest, nullptr, 16);
    calcResult.pendingRequest = reinterpret_cast<HttpPendingRequest*>
      (address);

    // read the result
    calcResult.result.resize(calcResult.resultSize);
    for (int i = 0; i < calcResult.resultSize; i++) {
      std::string result;
      std::getline(lineStream, result, ',');
      calcResult.result[i] = std::stoll(result);
    }

    return calcResult;
  }
  CalcResult emptyCalcResult = {nullptr, -1, -1, {}};
  return emptyCalcResult;
}
