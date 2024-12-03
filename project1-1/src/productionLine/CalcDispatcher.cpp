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

    // stop calculator workers
    int calcWorkersCount = std::thread::hardware_concurrency();

    for (int i = 0; i < calcWorkersCount; i++) {
        this->produce(nullptr);
    }
    return 0;
}

void CalcDispatcher::consume(HttpPendingRequest* request) {
    Socket socket =  this->connect("192.168.0.113", "8081");
    socket << "4,5,4,9,6\n";
    socket.send();
    socket << "4,5,4,9,6\n";
    socket.send();
    // Create a new calculator
    Calculator* calculator = nullptr;
    std::string type = request->getType();
    for (int i = 0; i < request->getNumbersCount(); i++) {
        if (type == "fact") {
            calculator = new FactCalculator(i, request);
        } else if (type == "goldbach") {
            calculator = new GoldCalculator(i, request);
        }
    }

    this->close();

    // Produce the calculator
    this->produce(calculator);
}

