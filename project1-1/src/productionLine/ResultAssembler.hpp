// Copyright Aaron Santana Valdelomar 2024 Universidad de Costa Rica

#pragma once
#include "CalcResult.hpp"
#include "../network/TcpServer.hpp"
#include "../prodcons/Producer.hpp"
#include "../http/HttpPendingRequest.hpp"


class ResultAssembler : public Producer<HttpPendingRequest*>, TcpServer {
 private:
        /* data */
        int slavesNodesCount;
        int stopConditionsCount = 0;
 public:
        explicit ResultAssembler(int slavesNodesCount);
        ~ResultAssembler();
        void handleClientConnection(Socket& client) override;
        CalcResult parseRequestLine(Socket& client);
        int run() override;
};

