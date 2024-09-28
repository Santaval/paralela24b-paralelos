#include "Consumer.hpp"
#include "Socket.hpp"

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

class HttpConnectionHandler : public Consumer<Socket> {

    DISABLE_COPY(HttpConnectionHandler);

    public:
      /// Constructor
      explicit HttpConnectionHandler();
      int run() override;
      /// Override this method to process any data extracted from the queue
      void consume(Socket data) override;

    

};

#endif