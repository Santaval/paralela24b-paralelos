// Copyright 2024 Isaias Alfaro Ugalde

#ifndef _GOLDWEBAPP_HPP_
#define _GOLDWEBAPPL_HPP_

#include "HttpApp.hpp"
#include "../prodcons/Producer.hpp"
#include "../http/HttpPendingRequest.hpp"

/**
@brief A web application that calculates Goldbach
*/
class GoldWebApp : public HttpApp, public Producer<HttpPendingRequest*> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldWebApp);

 public:
  /// Constructor
  GoldWebApp();
  /// Destructor
  ~GoldWebApp();
  /// Called by the web server when the web server is started
  void start() override;
  /// run
  int run() override;
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;

 protected:
  /// Handle a HTTP request that starts with "/gold"
  /// @return true if the Goldbach was handled, false if it must be
  /// handled by another application
  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);
};



#endif  // _GOLDWEBAPP_HPP_
