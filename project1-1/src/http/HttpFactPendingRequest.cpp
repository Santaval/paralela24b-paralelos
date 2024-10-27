// Copyright 2024 Aaron Santana, Isaias Alfaro
#include "HttpFactPendingRequest.hpp"
#include "Log.hpp"

void HttpFactPendingRequest::sendResponse() {
    // Verificar si numbers y getResults() tienen el mismo tamaño
    auto results = this->getResults();
    Log::append(Log::INFO, "SR", "Results size: "
        + std::to_string(results.size()));
    Log::append(Log::INFO, "SR", "Numbers size: "
        + std::to_string(this->getNumbers().size()));

    for (size_t i = 0; i < numbers.size(); i++) {
        const std::vector<int64_t>& numero = results[i];
        std::stringstream body;

        // Verificar si el vector está vacío o si el primer
        // elemento indica un número inválido
        if (numero.empty() || numero[0] == 0) {
            body << "  <h2 class=\"err\">" << numbers[i] << "</h2>\n"
                 << "  <p>" << numbers[i] << ": invalid number</p>\n";
        } else {
            std::string title = "Prime factorization of "
            + std::to_string(numbers[i]);
            body << "<h1>" << title << "</h1>\n";

            // Iterar sobre los factores y sus potencias asegurando
            // que hay pares de elementos
            for (size_t j = 0; j + 1 < numero.size(); j += 2) {
                body << "<span>" << numero[j] << "<sup>"
                     << numero[j + 1] << "</sup></span>";
            }
        }

        // Construir el cuerpo de la respuesta
        this->response.body() << "<!DOCTYPE html>\n"
                              << "<html lang=\"en\">\n"
                              << "  <meta charset=\"ascii\"/>\n"
                              << "  <title>Factorization Results</title>\n"
                              << "  <style>body {font-family: monospace}"
                                 ".err {color: red} span {margin-right: 20px}</style>\n"
                              << body.str()
                              << "  <hr><p><a href=\"/\">Back</a></p>\n"
                              << "</html>\n";
    }
    // Enviar la respuesta
    this->response.send();
}

