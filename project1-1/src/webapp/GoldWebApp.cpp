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
#include "Log.hpp"


GoldWebApp::GoldWebApp() {
}

GoldWebApp::~GoldWebApp() {
}

void GoldWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void GoldWebApp::stop() {
}

AppResponse GoldWebApp::handleHttpRequest(HttpRequest& httpRequest,
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
      for (ino64_t i = 0; i < numbers.size(); i++) {
        pendingRequest->pushNUmber(i, std::stoll(numbers[i]));
      }
      return {PRODUCTION_LINE_APP, pendingRequest, true};
    }
  }
  // Unrecognized request
  return {PRODUCTION_LINE_APP, nullptr, false};
}


Calculator* GoldWebApp::buildCalculator(CalcRequest request) {
  if (request.type == "goldbach") {
    return new GoldCalculator(request);
  } else {
    return nullptr;
  }
}
