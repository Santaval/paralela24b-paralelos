// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once

#include <string>
#include <vector>

#include "../http/HttpPendingRequest.hpp"


struct CalcResult {
 public:
    HttpPendingRequest* pendingRequest;
    int numberIndex;
    int resultSize;
    std::vector<int64_t> result;

 public:
    CalcResult() : pendingRequest(nullptr), numberIndex(-1), resultSize(0) {}
    CalcResult(HttpPendingRequest* pendingRequest, int numberIndex, int resultSize, std::vector<int64_t> result);
    friend Socket& operator<< (Socket& socket, const CalcResult& calcResult);
    bool operator==(const CalcResult& calcResult);
};
