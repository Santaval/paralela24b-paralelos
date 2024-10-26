
#include "HttpPendingRequest.hpp"

void HttpPendingRequest::pushNUmber(int number) {
    this->numbers.push_back(number);
}

void HttpPendingRequest::pushResult(int index, int result) {
    results[index].push_back(result);
}