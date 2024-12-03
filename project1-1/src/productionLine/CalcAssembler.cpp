// Copyright 2024 Aaron Santana

#include <string>

#include "CalcAssembler.hpp"
#include "Socket.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"  // Include the header for NetworkAddress
#include "../webapp/ProductionLineWebApp.hpp"

CalcAssembler::CalcAssembler
  (std::vector<ProductionLineWebApp*> applications) {
    this->applications = applications;
}

void CalcAssembler::consume(Socket socket) {
    this->handleClientConnection(socket);
    return;
}

int CalcAssembler::run() {
    this->consumeForever();
    return 0;
}

void CalcAssembler::handleClientConnection(Socket& client) {
  while (true) {
    std::string requestLine;
    // Leer una línea completa desde el socket
    if (!client.readLine(requestLine, '\n')) {
      Log::append(Log::ERROR, "CalcAssembler", "Failed to read from client");
      break; // Salir del bucle si no hay más datos
    }

    Log::append(Log::INFO, "CalcAssembler", "Received line: " + requestLine);

    // Procesar la línea recibida para extraer los números
    std::istringstream lineStream(requestLine);
    std::string number;
    std::vector<int> numbers;

    while (std::getline(lineStream, number, ',')) {
      try {
        numbers.push_back(std::stoi(number)); // Convertir a entero
      } catch (const std::invalid_argument& e) {
        Log::append(Log::ERROR, "CalcAssembler", "Invalid number: " + number);
      }
    }

    // Loguear los números obtenidos
    for (int num : numbers) {
      Log::append(Log::INFO, "CalcAssembler", "Number: " + std::to_string(num));
    }

    // Aquí puedes continuar procesando los números como desees
  }
}

