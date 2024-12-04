// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#include <string>

#include "CalcDispatcher.hpp"
#include "FactCalculator.hpp"
#include "GoldCalculator.hpp"
#include "Calculator.hpp"


int CalcDispatcher::run() {
    for (int i = 0; i < this->webAppsCount; i++) {
        this->consumeForever();
    }
    Log::append(Log::INFO, "CalcDispatcher", "stop");
    return 0;
}

void CalcDispatcher::consume(HttpPendingRequest* request) {

    // Create a new calculator
    for (int i = 0; i < request->getNumbersCount(); i++) {
    Socket socket =  this->connect("192.168.0.113", "8081");
        socket
        << request->getType() << ","
        << request << ","
        << i << ","
        << request->getNumber(i) << "\n";
        socket.send();
        this->close();
    }

}

