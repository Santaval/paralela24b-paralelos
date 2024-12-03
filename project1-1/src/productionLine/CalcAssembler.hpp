// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#pragma once

#include <vector>
#include <string>
#include "../prodcons/Assembler.hpp"
#include "Calculator.hpp"
#include "Socket.hpp"
#include "../webapp/ProductionLineWebApp.hpp"
#include "CalcRequest.hpp"


class CalcAssembler : public Assembler<Socket, Calculator*> {
 private:
    std::vector<ProductionLineWebApp*> applications;
 public:
    /// Constructor
    explicit CalcAssembler(std::vector<ProductionLineWebApp*> applications);
    int run() override;
    /// Consume
    /// Get requests from the stack
    /// @param data Queue whit requests
    void consume(Socket data) override;
    /// @brief handle Client Connection.
    /// Create the new http whit the request
    /// @param client Specific request from user
    void handleClientConnection(Socket& client);
    /// @brief parse the request line.
      /// Parse the request line from the socket
      /// @return true on success, false on error or connection closed by peer
    CalcRequest parseRequestLine(Socket& client);

    /// Ask to webapps to build a calculator
    /// @param request Request to calculate
    /// @return Calculator
    Calculator* assembleCalculator(CalcRequest request);
};
