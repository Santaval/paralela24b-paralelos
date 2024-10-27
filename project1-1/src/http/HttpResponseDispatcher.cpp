#include "HttpResponseDispatcher.hpp"

int HttpResponseDispatcher::run() {
   this->consumeForever();
    return 0;
}

void HttpResponseDispatcher::consume(HttpPendingRequest* httpPendingRequest) {
    std::string html = httpPendingRequest->buildResponse();
    HttpResponse httpResponse = httpPendingRequest->getResponse();
    httpResponse.body() << html;
    httpResponse.send();
    delete httpPendingRequest;
    return;
}