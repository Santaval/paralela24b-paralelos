#include "HttpConnectionHandler.hpp"
#include "Log.hpp"

HttpConnectionHandler::HttpConnectionHandler() {
}

void HttpConnectionHandler::consume(Socket socket) {
    // this->handleClientConnection(socket);
    std::cout  << "Hola" << "\n";
    return;
}

int HttpConnectionHandler::run () {
    return 0;
}