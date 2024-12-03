// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once
#include "../prodcons/Consumer.hpp"
#include "../http/HttpPendingRequest.hpp"
#include "../network/TcpClient.hpp"

class CalcDispatcher : public Consumer<HttpPendingRequest*>, TcpClient {
 private:
    int webAppsCount;
 public:
    explicit CalcDispatcher(int webAppsCount)
        : Consumer<HttpPendingRequest*>
            (nullptr, nullptr), webAppsCount(webAppsCount) {}
    virtual ~CalcDispatcher() {}

    int run() override;
    void consume(HttpPendingRequest* request) override;
};
