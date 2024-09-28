#include "Consumer.hpp"
#include "Socket.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

class HttpConnectionHandler : public Consumer<Socket> {

    DISABLE_COPY(HttpConnectionHandler);

    protected:
      std::vector<HttpApp*> applications;

    public:
      /// Constructor
      explicit HttpConnectionHandler(std::vector<HttpApp*> applications);
      int run() override;
      /// Override this method to process any data extracted from the queue
      void consume(Socket data) override;
      void handleClientConnection(Socket& client);
      bool handleHttpRequest(HttpRequest& httpRequest,
      HttpResponse& httpResponse);
      bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);

  
};

#endif