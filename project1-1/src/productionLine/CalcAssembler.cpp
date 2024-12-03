// Copyright 2024 Aaron Santana

#include "CalcAssembler.hpp"
#include "Socket.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"  // Include the header for NetworkAddress
#include "../webapp/ProductionLineWebApp.hpp"

CalcAssembler::CalcAssembler
  (std::vector<ProductionLineWebApp*> applications) {
    this->applications = applications;
}

void CalcAssembler::consume(Socket socket) {
    this->handleClientConnection(socket);
    return;
}

int CalcAssembler::run() {
    this->consumeForever();
    return 0;
}

void CalcAssembler::handleClientConnection(Socket& client) {
    while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);

    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client);

    // Give subclass a chance to respond the HTTP request
    const bool handled = this->handleHttpRequest(httpRequest, httpResponse);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      client.close();
      break;
    }
    break;
  }
}

bool CalcAssembler::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // Print IP and port from client
  const NetworkAddress& address = httpRequest.getNetworkAddress();
  Log::append(Log::INFO, "connection",
    std::string("connection established with client ") + address.getIP()
    + " port " + std::to_string(address.getPort()));

  // Print HTTP request
  Log::append(Log::INFO, "request", httpRequest.getMethod()
    + ' ' + httpRequest.getURI()
    + ' ' + httpRequest.getHttpVersion());

  return this->route(httpRequest, httpResponse);
}


bool CalcAssembler::route(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // Traverse the chain of applications
  for (size_t index = 0; index < this->applications.size(); ++index) {
    // If this application handles the request
    ProductionLineWebApp* app = this->applications[index];
    Calculator* calculator = app->buildCalculator();
    if (calculator != nullptr) {
        this->produce(calculator);
      return true;
    }
  }
}