// Copyright 2024 Aaron Santana Valdelomar. Universidad de Costa Rica. CC BY 4.0
#include <string>

#include "CalcDispatcher.hpp"
#include "FactCalculator.hpp"
#include "GoldCalculator.hpp"
#include "Calculator.hpp"

#define seed 24234325


int CalcDispatcher::run() {
    for (int i = 0; i < this->connectionsHandlersCount; i++) {
        this->consumeForever();
    }
    Log::append(Log::INFO, "CalcDispatcher", "stop");
    CalcRequest emptyCalcRequest;
    for (int i = 0; i < this->connectionsHandlersCount; i++) {
        //this->
    }
    return 0;
}

void CalcDispatcher::consume(HttpPendingRequest* request) {
    // Create a new calculator
    for (int i = 0; i < request->getNumbersCount(); i++) {
        CalcRequest calcRequest(request->getType(), request, i, request->getNumber(i));
        // gen uniform random number
        int random = this->generateRandomNumber();
        CalcDispatcherClient* client = this->clients[random];
        client->sendNetworkMessage(calcRequest);
    }
}

void CalcDispatcher::chargeSlavesConfig() {
    std::ifstream file(this->slavesConfigFile);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de configuración");
    }

    std::string line;
    int n = 0;
    if (std::getline(file, line)) {
        n = std::stoi(line);
    } else {
        throw std::runtime_error("Archivo de configuración vacío o con formato inválido");
    }

    this->clients.resize(n);

    for (int i = 0; i < n; i++) {
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string ip;
            std::string port;

            if (iss >> ip >> port) {
                this->clients[i] = new CalcDispatcherClient(ip, port);
            } else {
                throw std::runtime_error("Error al leer la configuración del esclavo " + std::to_string(i));
            }
        } else {
            throw std::runtime_error("Archivo de configuración incompleto");
        }
    }

    file.close();
}


int CalcDispatcher::generateRandomNumber() {
        // Inicializar la semilla para srand
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Generar un número aleatorio entre 0 y RAND_MAX
    int randomInt = std::rand();

    // Generar un número aleatorio entre un rango específico
    int min = 0, max = this->clients.size();
    int randomInRange = min + (randomInt % (max - min + 1));
    return randomInRange;
}
