// Copyright Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0

#pragma once

#include <string>
#include "TcpClient.hpp"
#include "CalcRequest.hpp"


class CalcDispatcherClient : public TcpClient {
 public:
    std::string ip;
    std::string port;
 public:
    CalcDispatcherClient(std::string ip, std::string port);
    ~CalcDispatcherClient();
    void sendNetworkMessage(CalcRequest message);
};


