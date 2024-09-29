// Copyright 2024 Aaron Santana, Isaias Alfaro

#include <vector>
#include <string>

#include "Consumer.hpp"
#include "Socket.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

/**
@brief class Threads that handle the request of the users.
*/
class HttpConnectionHandler : public Consumer<Socket> {
    /// Desactivar copias de la clase
    DISABLE_COPY(HttpConnectionHandler);

 protected:
      /// Matrix whit applications
      std::vector<HttpApp*> applications;

 public:
      /// Constructor
      explicit HttpConnectionHandler(std::vector<HttpApp*> applications);
      int run() override;
      /// Consume
      /// Get requests from the stack
      /// @param data Queue whit requests
      void consume(Socket data) override;
      /// @brief handle Client Connection.
      /// Create the new http whit the request
      /// @param client Specific request from user
      void handleClientConnection(Socket& client);
      /// @brief handle Http Request.
      /// Show IP and Request and retunr rute
      /// @param httpRequest Request from user
      /// @param httpResponse Response from Web
      bool handleHttpRequest(HttpRequest& httpRequest,
      HttpResponse& httpResponse);
      /// @brief route.
      /// Give the route from the applications
      /// @param httpRequest Request from user
      /// @param httpResponse Response from Web
      bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
      /// @brief serveNotFound.
      /// Show page if there isn't an applications
      /// @param httpRequest Request from user
      /// @param httpResponse Response from Web
      bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // _HTTP_HTTPCONNECTIONHANDLER_HPP_
