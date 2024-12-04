// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once
#include <string>
#include <vector>

#include "../prodcons/Consumer.hpp"
#include "../http/HttpPendingRequest.hpp"
#include "../network/TcpClient.hpp"
#include "CalcDispatcherClient.hpp"
#include "Socket.hpp"

class CalcDispatcher : public Consumer<HttpPendingRequest*>, TcpClient {
 private:
    int connectionsHandlersCount = 0;
    std::string slavesConfigFile = "slaves.txt";
    std::vector<CalcDispatcherClient*> clients = std::vector<CalcDispatcherClient*>();
 public:
    explicit CalcDispatcher(int connectionsHandlersCount, std::string slavesConfigFile)
        : Consumer<HttpPendingRequest*>(nullptr, nullptr),
        connectionsHandlersCount(connectionsHandlersCount),
        slavesConfigFile(slavesConfigFile) {
            this->createOwnQueue();
            this->chargeSlavesConfig();
        }
    virtual ~CalcDispatcher() {
        this->createOwnQueue();
    }

    int run() override;
    void consume(HttpPendingRequest* request) override;
    void chargeSlavesConfig();
    int generateRandomNumber();
};
