// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#pragma once

#include "HttpApp.hpp"
#include "ProductionLineWebApp.hpp"


/**
@brief A web application that calculates prime factors
*/
class FactWebApp : public ProductionLineWebApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(FactWebApp);

 public:
  /// Constructor
  FactWebApp();
  /// Destructor
  ~FactWebApp();
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
  // build calculator
  Calculator* buildCalculator(CalcRequest request) override;
};
