// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once
#include "../prodcons/Assembler.hpp"
#include "../http/HttpPendingRequest.hpp"
#include "Calculator.hpp"
#include "../network/TcpClient.hpp"

class CalcDispatcher : public Assembler<HttpPendingRequest*, Calculator*>, TcpClient {
 private:
    int webAppsCount;
 public:
    explicit CalcDispatcher(int webAppsCount) : Assembler<HttpPendingRequest*,
        Calculator*>(
        nullptr, nullptr, nullptr), webAppsCount(webAppsCount) {}
    virtual ~CalcDispatcher() {}

    int run() override;
    void consume(HttpPendingRequest* request) override;
};
