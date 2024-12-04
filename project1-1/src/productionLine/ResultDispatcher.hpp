// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once
#include "../prodcons/Consumer.hpp"
#include "../productionLine/Calculator.hpp"
#include "../network/TcpClient.hpp"

class ResultDispatcher : public Consumer<Calculator*>, TcpClient{
 private:
    /* data */
 public:
    ResultDispatcher(/* args */);
    ~ResultDispatcher();
    int run() override;
    void consume(Calculator* calculator) override;
};
