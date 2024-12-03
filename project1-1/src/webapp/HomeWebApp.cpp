// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <iostream>
#include <string>

#include "HomeWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"



HomeWebApp::HomeWebApp() {
}

HomeWebApp::~HomeWebApp() {
}

void HomeWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void HomeWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

AppResponse HomeWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    this->serveHomepage(httpRequest, httpResponse);
    return {NO_PRODUCTION_LINE_APP, nullptr, true};
  }

  // Unrecognized request
  return {NO_PRODUCTION_LINE_APP, nullptr, false};
}

// TODO(you): Fix code redundancy in the following methods

bool HomeWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

//     <style>
//     body {
//       font-family: monospace;
//     }

//     form {
//       margin-bottom: 20px;
//       padding-bottom: 20px;
//       border-bottom: 1px solid #ccc;
//     }

//     input[type="text"] {
//       outline: none;
//       border-radius: 20px;
//       border: 1px solid #ccc;
//       padding: 5px;
//     }

//     label {
//       margin-right: 10px;
//       color: gray;
//     }

//     button {
//       padding: 5px 10px;
//       background-color: #007bff;
//       color: white;
//       border: none;
//       cursor: pointer;
//       border-radius: 10px;
//     }
//   </style>
  // Build the body of the response
  std::string title = "Prime factorization";
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red} \n"
    << "  form {margin-bottom: 20px; padding-bottom:"
        "20px; border-bottom: 1px solid #ccc;}\n"
    << "  input[type=\"text\"] {outline: none; border-radius:"
        " 20px; border: 1px solid #ccc; padding: 5px;}\n"
    << "  label {margin-right: 10px; color: gray;}\n"
    << "  button {padding: 5px 10px; background-color: #007bff;"
        "color: white; border: none; cursor: pointer; border-radius: 10px;}\n"
    << "  </style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/fact\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"text\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Factorize</button>\n"
    << "  </form>\n"
    << "</html>\n";

    std::string title2 = "Golbach";
  httpResponse.body() << "  <h1>" << title2 << "</h1>\n"
    << "  <form method=\"get\" action=\"/golbach\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"text\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Calculate</button>\n"
    << "  </form>\n";


  // Send the response to the client (user agent)
  return httpResponse.send();
}
