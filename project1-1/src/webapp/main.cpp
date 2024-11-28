// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER
#include <csignal>

#include "HttpServer.hpp"
#include "FactWebApp.hpp"
#include "GoldWebApp.hpp"
#include "HomeWebApp.hpp"

// TODO(you): Register a signal handler for Ctrl+C and kill, and stop the server
// TODO(you): Make your signal handler to print the thread id running it

/// Start the web server
int main(int argc, char* argv[]) {
  signal(SIGINT, HttpServer::handleSignal);
  // Create the web server
  HttpServer* httpServer = HttpServer::getInstance();
  // Create home web application
  HomeWebApp homeWebApp;
  // Create a factorization web application, and other apps if you want
  FactWebApp factWebApp;
  // GoldWebApp goldWebApp;

  // Register the web application(s) with the web server
  httpServer->chainProductionLineApp(&factWebApp);
  httpServer->chainWebApp(&homeWebApp);
  //httpServer->chainProductionLineApp(&goldWebApp);
  // Run the web server
  return httpServer->run(argc, argv);
}

#endif  // WEBSERVER
