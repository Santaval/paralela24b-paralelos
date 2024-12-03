// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once

#include "Producer.hpp"
#include "HttpApp.hpp"
#include "HttpPendingRequest.hpp"

class ProductionLineWebApp : public Producer<HttpPendingRequest*>,
    public HttpApp {
 public:
    ProductionLineWebApp() : Producer<HttpPendingRequest*>() {
    }

    ~ProductionLineWebApp() {
    }

    virtual void stop() = 0;
};
