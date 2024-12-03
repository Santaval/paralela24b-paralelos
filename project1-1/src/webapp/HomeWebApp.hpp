// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HOMEWEBAPP_HPP
#define HOMEWEBAPP_HPP

#include "HttpApp.hpp"

/**
@brief A web application that calculates prime factors
*/
class HomeWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(HomeWebApp);

 public:
  /// Constructor
  HomeWebApp();
  /// Destructor
  ~HomeWebApp();
  /// Called by the web server when the web server is started
  void start() override;
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  /// @return true If this application handled the request, false otherwise
  /// and another chained application should handle it
  AppResponse handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  void stop() override;

 protected:
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // FACTWEBAPP_HPP
