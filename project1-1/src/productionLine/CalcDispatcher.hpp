#pragma once
#include "../prodcons/Assembler.hpp"
#include "../http/HttpPendingRequest.hpp"
#include "Calculator.hpp"

class CalcDispatcher : public Assembler<HttpPendingRequest*, Calculator*> {
 private:
    int webAppsCount;
 public:
    explicit CalcDispatcher(int webAppsCount) : Assembler<HttpPendingRequest*, Calculator*>(
        nullptr, nullptr, nullptr), webAppsCount(webAppsCount) {}
    virtual ~CalcDispatcher() {}

    int run() override;
    void consume(HttpPendingRequest* request) override;
};
