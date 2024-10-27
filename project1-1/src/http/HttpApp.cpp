// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include "HttpApp.hpp"

// Create treads apps
void HttpApp::start() {
  this->startThread();
}

// Finish treads apps
void HttpApp::stop() {
  this->waitToFinish();
}
