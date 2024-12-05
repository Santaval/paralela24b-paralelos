// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once
#include "../prodcons/Consumer.hpp"
#include "../productionLine/Calculator.hpp"
#include "../network/TcpClient.hpp"
#include "CalcResult.hpp"

#define DEFAULT_RESULTS_PORT "4321"

class ResultDispatcher : public Consumer<Calculator*>, TcpClient{
 private:
    char* masterServerPort = DEFAULT_RESULTS_PORT;
    char* masterServerIp = "127.0.0.1";
 public:
    ResultDispatcher(/* args */);
    ~ResultDispatcher();
    int run() override;
    void consume(Calculator* calculator) override;
    void sendNetworkMessage(CalcResult message, char* ip, char* port);
};
