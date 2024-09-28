#include "HttpConnectionHandler.hpp"
#include "Log.hpp"

HttpConnectionHandler::HttpConnectionHandler() {
}

void HttpConnectionHandler::consume(Socket socket) {
    // this->handleClientConnection(socket);
    Log::append(Log::INFO, "webserver", "Hola Socket");

    return;
}

int HttpConnectionHandler::run () {
    this->consumeForever();
    return 0;
}