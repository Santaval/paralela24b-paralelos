// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpResponseDispatcher.hpp"
#include "Log.hpp"

int HttpResponseDispatcher::run() {
    this->consumeForever();
    Log::append(Log::INFO, "HttpResponseDispatcher", "stop");
    return 0;
}

void HttpResponseDispatcher::consume(HttpPendingRequest* httpPendingRequest) {
    httpPendingRequest->sendResponse();
    delete httpPendingRequest;
    return;
}
