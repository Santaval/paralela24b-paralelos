// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpResponseDispatcher.hpp"

int HttpResponseDispatcher::run() {
    this->consumeForever();
    return 0;
}

void HttpResponseDispatcher::consume(HttpPendingRequest* httpPendingRequest) {
    httpPendingRequest->sendResponse();
    delete httpPendingRequest;
    return;
}
