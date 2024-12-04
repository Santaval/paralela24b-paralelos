// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once
#include "../prodcons/Consumer.hpp"
#include "../http/HttpPendingRequest.hpp"
#include "../network/TcpClient.hpp"
#include "CalcRequest.hpp"

class CalcDispatcher : public Consumer<HttpPendingRequest*>, TcpClient {
 private:
    int webAppsCount;
 public:
    explicit CalcDispatcher(int webAppsCount)
        : Consumer<HttpPendingRequest*>
            (nullptr, nullptr), webAppsCount(webAppsCount) {
        this->createOwnQueue();
            }
    virtual ~CalcDispatcher() {
        this->createOwnQueue();
    }

    int run() override;
    void consume(HttpPendingRequest* request) override;
    void sendNetworkMessage(CalcRequest message, char* ip, char* port);
};
