#include "HttpConnectionHandler.hpp"
#include "Log.hpp"

HttpConnectionHandler::HttpConnectionHandler() {
}

void HttpConnectionHandler::consume(Socket socket) {
    // this->handleClientConnection(socket);
    Log::append(Log::INFO, "webserver", "Listening on");
    return;
}

int HttpConnectionHandler::run () {
    return 0;
}