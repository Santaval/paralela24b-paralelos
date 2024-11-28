// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpPendingRequest.hpp"
#include "Log.hpp"

void HttpPendingRequest::pushNUmber(int index, int number) {
    this->numbers[index] = number;
}

void HttpPendingRequest::pushResult(int index, std::vector<int64_t> result) {
    this->results[index] = result; 
}
