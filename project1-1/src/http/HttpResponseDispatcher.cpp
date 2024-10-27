// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpResponseDispatcher.hpp"

int HttpResponseDispatcher::run() {
    this->consumeForever();
    return 0;
}

void HttpResponseDispatcher::consume(HttpPendingRequest* httpPendingRequest) {
    std::stringstream html = httpPendingRequest->buildResponse();
    HttpResponse httpResponse = httpPendingRequest->getResponse();
    httpResponse.body() << html.str();
    httpResponse.send();
    delete httpPendingRequest;
    return;
}
