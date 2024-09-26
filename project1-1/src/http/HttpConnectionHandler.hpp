#include "Consumer.hpp"
#include "Socket.hpp"

class HttpConnectionHandler : public Consumer<Socket*> {

    DISABLE_COPY(HttpConnectionHandler);

    // TODO(you): Make this method concurrent. Store client connections (sockets)
  // // into a collection (e.g thread-safe queue) and stop in web server

  // // TODO(you): Move following loop to a consumer HttpConnectionHandler class

  // // While the same client asks for HTTP requests in the same connection
  // while (true) {
  //   // Create an object that parses the HTTP request from the socket
  //   HttpRequest httpRequest(client);

  //   // If the request is not valid or an error happened
  //   if (!httpRequest.parse()) {
  //     // Non-valid requests are normal after a previous valid request. Do not
  //     // close the connection yet, because the valid request may take time to
  //     // be processed. Just stop waiting for more requests
  //     break;
  //   }

  //   // A complete HTTP client request was received. Create an object for the
  //   // server responds to that client's request
  //   HttpResponse httpResponse(client);

  //   // Give subclass a chance to respond the HTTP request
  //   const bool handled = this->handleHttpRequest(httpRequest, httpResponse);

  //   // If subclass did not handle the request or the client used HTTP/1.0
  //   if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
  //     // The socket will not be more used, close the connection
  //     client.close();
  //     break;
  //   }

  //   // This version handles just one client request per connection
  //   // TODO(you): Remove this break after parallelizing this method
  //   break;
  // }

};