// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0

#include <string>
#include "CalcRequest.hpp"

CalcRequest::CalcRequest(std::string type, HttpPendingRequest* pendingRequest,
    int numberIndex, int number)
    : type(type), pendingRequest(pendingRequest), numberIndex(numberIndex),
        number(number) {
}

std::string CalcRequest::getType() {
    return this->type;
}

HttpPendingRequest* CalcRequest::getPendingRequest() {
    return this->pendingRequest;
}

int CalcRequest::getNumberIndex() {
    return this->numberIndex;
}

int CalcRequest::getNumber() {
    return this->number;
}

Socket& operator<< (Socket& socket, const CalcRequest& calcRequest) {
    socket << calcRequest.type << ","
           << calcRequest.pendingRequest << ","
           << calcRequest.numberIndex << ","
           << calcRequest.number;
    return socket;
}

bool CalcRequest::operator==(const CalcRequest& calcRequest) {
    return this->type == calcRequest.type &&
           this->pendingRequest == calcRequest.pendingRequest &&
           this->numberIndex == calcRequest.numberIndex &&
           this->number == calcRequest.number;
}
