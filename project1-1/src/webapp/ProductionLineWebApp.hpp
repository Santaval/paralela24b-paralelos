#pragma once

#include "Producer.hpp"
#include "HttpApp.hpp"
#include "../productionLine/Calculator.hpp"

class ProductionLineWebApp : public Producer<Calculator*>, public HttpApp {

    public:
    ProductionLineWebApp() : Producer<Calculator*>() {
    }

    ~ProductionLineWebApp() {
    }

    virtual void stop() = 0;
};
