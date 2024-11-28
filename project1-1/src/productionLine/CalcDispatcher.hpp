#pragma once
#include "../prodcons/Assembler.hpp"
#include "../http/HttpPendingRequest.hpp"
#include "Calculator.hpp"
class CalcDispatcher : public Assembler<HttpPendingRequest*, Calculator*> {

public:
    CalcDispatcher() : Assembler<HttpPendingRequest*, Calculator*>() {}
    virtual ~CalcDispatcher() {}

    int run() override;
    void consume(HttpPendingRequest* request) override;

};
