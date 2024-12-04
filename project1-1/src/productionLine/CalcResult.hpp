// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once

#include <string>
#include <vector>

#include "../http/HttpPendingRequest.hpp"


struct CalcResult {
  HttpPendingRequest* pendingRequest;
  int numberIndex;
  int resultSize;
  std::vector<int64_t> result;
};
