// Copyright 2024 Isaias Alfaro Ugalde

// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <Util.hpp>

#include "GoldWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../productionLine/GoldCalculator.hpp"
#include "HttpGolbachPendingRequest.hpp"

GoldWebApp::GoldWebApp() {
}

GoldWebApp::~GoldWebApp() {
}

int GoldWebApp::run() {
  return 0;
}

void GoldWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void GoldWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

bool GoldWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the request starts with "golbach/" is for this web app
  if (httpRequest.getURI().rfind("/golbach", 0) == 0) {
    // Set HTTP response metadata (headers)
    httpResponse.setHeader("Server", "AttoServer v1.0");
    httpResponse.setHeader("Content-type", "text/html; charset=ascii");
    std::smatch matches;
    std::regex inQuery("^/golbach(/|\\?number=)([\\d%2C,-]+)$");
    if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
      assert(matches.length() >= 3);
      std::string number = matches[2];
      // Replace all % with ,
      std::replace(number.begin(), number.end(), '%', ',');
      // Eliminate al 2C
      size_t position = 0;
      while ((position = number.find("2C", position)) != std::string::npos) {
        number.replace(position, 2, "");
      }
      // URI only with numbers
      std::vector<std::string> numbers = Util::split(number, ",");
      HttpGolbachPendingRequest* pendingRequest =
          new HttpGolbachPendingRequest(number.size(), httpResponse);
      for (ino64_t i = 0; i <= numbers.size()-1; i++) {
        GoldCalculator* calculator = new GoldCalculator(i, pendingRequest);
        pendingRequest->pushNUmber(std::stoll(numbers[i]));
        this->produce(calculator);
        return true;
      }
    }
  }
  // Unrecognized request
  return false;
}


/*bool GoldWebApp::serveGoldbach(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");


  std::smatch matches;
  std::regex inQuery("^/golbach(/|\\?number=)([\\d%2C,-]+)$");
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);
    std::string number = matches[2];
    // Response
    std::stringstream body;
    // Replace all % with ,
    std::replace(number.begin(), number.end(), '%', ',');
    // Eliminate al 2C
    size_t position = 0;
    while ((position = number.find("2C", position)) != std::string::npos) {
    number.replace(position, 2, "");
    }
    // URI only with numbers
    std::vector<std::string> numbers = Util::split(number, ",");
    // Construccion Respuesta
    for (ino64_t i = 0; i <= numbers.size()-1; i++) {
      std::vector <int64_t> numero;
      Calculator.Calc(std::stoll(numbers[i]));
      numero = Calculator.get_result();
      if (numero[0] == 0) {
        body << "  <h2 class=\"err\">" << numbers[i] << "</h2>\n"
             << "  <p>" << numbers[i] << ": invalid number</p>\n";
      } else {
        std::string title = "Goldbach of " + (numbers[i]);
        body << "<h1>" << title << "</h1>\n";
        // Show the answer
        for (ino64_t j = 0; j < numero.size(); j++) {
          body << "<span >" <<numero[j];
          if (j < numero.size() - 1) {
            body << " +";
          }
          body << "</span>";
        }
        body << "<br>\n";
      }
    }
    // TODO(you): Factorization must not be done by factorization threads
    // Build the body of the response
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>Factorization Results</title>\n"
      << "  <style>body {font-family: monospace}"
          ".err {color: red} span {margin-right: 20px}</style>\n"
      << body.str()
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  } else {
    // Build the body for an invalid request
    std::string title = "Invalid request";
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>" << title << "</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red} </style>\n"
      << "  <h1 class=\"err\">" << title << "</h1>\n"
      << "  <p>Invalid request for Goldbach</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }

  // Send the response to the client (user agent)
  return httpResponse.send();
}*/
