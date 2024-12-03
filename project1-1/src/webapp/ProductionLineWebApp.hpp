// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once

#include <string>

#include "Producer.hpp"
#include "HttpApp.hpp"
#include "HttpPendingRequest.hpp"

class ProductionLineWebApp : public HttpApp {
 public:
    ProductionLineWebApp() {
    }

    ~ProductionLineWebApp() {
    }

    virtual void stop() = 0;
    virtual Calculator* buildCalculator(CalcRequest request) = 0;
};
