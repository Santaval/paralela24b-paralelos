// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0

#pragma once

#include <string>

#include "../http/HttpPendingRequest.hpp"


struct CalcRequest {
  std::string type;
  HttpPendingRequest* pendingRequest;
  int numberIndex;
  int number = -1;
};
