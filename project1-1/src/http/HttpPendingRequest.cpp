
#include "HttpPendingRequest.hpp"

void HttpPendingRequest::pushNUmber(int number) {
    this->numbers.push_back(number);
}

void HttpPendingRequest::pushResult(int index, std::vector<int> result) {
    results[index] = result;
}