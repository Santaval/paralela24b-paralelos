// Copyright 2024 Isaias Alfaro Ugalde

#ifndef _GOLDWEBAPP_HPP_
#define _GOLDWEBAPPL_HPP_

#include <string>

#include "HttpApp.hpp"
#include "ProductionLineWebApp.hpp"


/**
@brief A web application that calculates Goldbach
*/
class GoldWebApp : public ProductionLineWebApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldWebApp);

 public:
  /// Constructor
  GoldWebApp();
  /// Destructor
  ~GoldWebApp();
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
  /// build calculator
  Calculator* buildCalculator(CalcRequest request) override;

 protected:
  /// Handle a HTTP request that starts with "/gold"
  /// @return true if the Goldbach was handled, false if it must be
  /// handled by another application
  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);
};



#endif  // _GOLDWEBAPP_HPP_
