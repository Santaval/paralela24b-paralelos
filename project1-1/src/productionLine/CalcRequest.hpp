// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0

#pragma once

#include <string>

#include "../http/HttpPendingRequest.hpp"


class CalcRequest {
 public:
    std::string type;
    HttpPendingRequest* pendingRequest;
    int numberIndex;
    int number = -1;

 public:
    CalcRequest() : type(""), pendingRequest(nullptr), numberIndex(-1) {}
    CalcRequest(std::string type, HttpPendingRequest* pendingRequest,
      int numberIndex, int number);

    std::string getType();
    HttpPendingRequest* getPendingRequest();
    int getNumberIndex();
    int getNumber();

  friend Socket& operator<< (Socket& socket, const CalcRequest& calcRequest);
  bool operator==(const CalcRequest& calcRequest);
};

