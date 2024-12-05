// Copyright Aaron Santana Valdelomar 2024 Universidad de Costa Rica

#include <vector>

#include "CalcResult.hpp"


CalcResult::CalcResult(HttpPendingRequest* pendingRequest, int numberIndex,
    int resultSize, std::vector<int64_t> result) {
    this->pendingRequest = pendingRequest;
    this->numberIndex = numberIndex;
    this->resultSize = resultSize;
    this->result = result;
}

Socket& operator<< (Socket& socket, const CalcResult& calcResult) {
    socket << calcResult.pendingRequest << ","
    << calcResult.numberIndex << ","
    << calcResult.resultSize << ",";

    for (size_t  i = 0; i < calcResult.result.size(); i++) {
        socket << calcResult.result[i];
        if (i < calcResult.result.size() - 1) {
            socket << ",";
        }
    }
    socket << "\n";
    return socket;
}

bool CalcResult::operator==(const CalcResult& calcResult) {
    return this->pendingRequest == calcResult.pendingRequest &&
    this->numberIndex == calcResult.numberIndex &&
    this->resultSize == calcResult.resultSize &&
    this->result == calcResult.result;
}
