// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

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
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // If the request starts with "fact/" is for this web app
  if (httpRequest.getURI().rfind("/fact", 0) == 0) {
    return this->serveFactorization(httpRequest, httpResponse);
  }

  // Unrecognized request
  return false;
}

// TODO(you): Fix code redundancy in the following methods

bool FactWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Prime factorization";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/fact\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"number\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Factorize</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool FactWebApp::serveFactorization(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // If a number was asked in the form "/fact/1223"
  // or "/fact?number=1223"
  // TODO(you): URI can be a multi-value list, e.g: 100,2784,-53,200771728
  // TODO(you): Use arbitrary precision for numbers larger than int64_t
  // TODO(you): Modularize this method
  FactCal Calculator;
  std::smatch matches;
  std::regex inQuery("^/fact(/|\\?number=)([\\d,]+)$");
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);

    const int64_t number = std::stoll(matches[2]);
    std::vector<int64_t> numbers;
    std::stringstream ss(std::to_string(number));
    std::string auxiliar = "";
    std::stringstream body;

    while (std::getline(ss, auxiliar, ',')) {
        numbers.push_back(std::stoi(auxiliar));
    }

    // Construccion Respuesta
    std::string title = "Prime factorization of " + std::to_string(number);
    body << "<h1>" << title << "</h1>\n";
    for (int64_t i = 0; i <= numbers.size(); i++) {
      Calculator.Calculator_Factorial(numbers[i]);
      if (Calculator.get_Factorial() == "false") {
        body << "  <h2 class=\"err\">" << numbers[i] << "</h2>\n"
             << "  <p>" << numbers[i] << ": invalid number</p>\n";
      } else {

        int64_t startPos = 0;
        int64_t spacePos;
        std::string numero, potency;

        while ((spacePos = Calculator.get_Factorial().
            find(" ", startPos)) != std::string::npos) {
            // Extraer el primer número (number)
            numero = Calculator.get_Factorial().
                substr(startPos, spacePos - startPos);

            // Actualizar startPos para apuntar a la siguiente posición
            startPos = spacePos + 1;

            // Encontrar la siguiente posición de espacio para extraer "potency"
            spacePos = Calculator.get_Factorial().find(" ", startPos);

            // Verificar si se encontró otro espacio (si no, es la última parte)
            if (spacePos != std::string::npos) {
                // Extraer la potencia (potency)
                potency = Calculator.get_Factorial().
                    substr(startPos, spacePos - startPos);

                // Actualizar startPos nuevamente para continuar
                startPos = spacePos + 1;
            } else {
                // extraer el último valor como "potency"
                potency = Calculator.get_Factorial().substr(startPos);
                startPos = Calculator.get_Factorial().length();
            }

            // Imprimir o procesar la pareja number y potency
            httpResponse.body() << "<p>" << numero << "<sup>"
                << potency << "</sup></p>";
        }
      }
    }

    // TODO(you): Factorization must not be done by factorization threads
    // Build the body of the response
    httpResponse.body() << "<!DOCTYPE html>\n"
      << "<html lang=\"en\">\n"
      << "  <meta charset=\"ascii\"/>\n"
      << "  <title>Factorization Results</title>\n"
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
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
      << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
      << "  <h1 class=\"err\">" << title << "</h1>\n"
      << "  <p>Invalid request for factorization</p>\n"
      << "  <hr><p><a href=\"/\">Back</a></p>\n"
      << "</html>\n";
  }

  // Send the response to the client (user agent)
  return httpResponse.send();
}
