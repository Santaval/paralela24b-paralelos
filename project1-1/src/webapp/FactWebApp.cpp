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

#include "FactWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "FactCal.hpp"

FactWebApp::FactWebApp() {
}

FactWebApp::~FactWebApp() {
}

void FactWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void FactWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

bool FactWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the request starts with "fact/" is for this web app
  if (httpRequest.getURI().rfind("/fact", 0) == 0) {
    return this->serveFactorization(httpRequest, httpResponse);
  }

  // Unrecognized request
  return false;
}


bool FactWebApp::serveFactorization(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // If a number was asked in the form "/fact/1223"
  // or "/fact?number=1223"
  // TODO(you): Modularize this method
  FactCal Calculator;
  std::smatch matches;
  std::regex inQuery("^/fact(/|\\?number=)([\\d%2C,-]+)$");
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
      Calculator.Calculator_Factorial(std::stoll(numbers[i]));
      std::vector <int64_t> numero = Calculator.get_Factorial();
      if (numero[0] == 0) {
        body << "  <h2 class=\"err\">" << numbers[i] << "</h2>\n"
        << "  <p>" << numbers[i] << ": invalid number</p>\n";
      } else {
        std::string title = "Prime factorization of " + numbers[i];
        body << "<h1>" << title << "</h1>\n";
        for (ino64_t j = 0; j < numero.size(); j+=2) {
          body << "<span >" << numero[j] << "<sup>"
          << numero[j+1] << "</sup></span>";
        }
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
      << "  <p>Invalid request for factorization</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }

  // Send the response to the client (user agent)
  return httpResponse.send();
}
