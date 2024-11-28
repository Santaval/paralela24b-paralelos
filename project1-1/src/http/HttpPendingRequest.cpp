// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpPendingRequest.hpp"
#include "Log.hpp"

void HttpPendingRequest::pushNUmber(int number) {
    this->numbers.push_back(number);
    this->numbersCount++;
}

void HttpPendingRequest::pushResult(int index, std::vector<int64_t> result) {
    results[index] = result;
}
