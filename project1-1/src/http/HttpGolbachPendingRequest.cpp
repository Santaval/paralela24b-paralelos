// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpGolbachPendingRequest.hpp"
#include "Log.hpp"

void HttpGolbachPendingRequest::sendResponse()
{
    auto results = this->getResults();
    

    for (size_t i = 0; i < numbers.size(); i++)
    {
        const std::vector<int64_t>& numero = results[i];
        std::stringstream body;

        // Verificar si el vector está vacío o si el primer elemento indica un número inválido
        if (numero.empty() || numero[0] == 0)
        {
            body << "  <h2 class=\"err\">" << numbers[i] << "</h2>\n"
                 << "  <p>" << numbers[i] << ": invalid number</p>\n";
        }
        else if (numbers[i] % 2 == 0 && numbers[i] > 2)
        {
            // Generar título para sumas de Goldbach
            std::string title = "Goldbach's sums for " + std::to_string(numbers[i]);
            body << "<h1>" << title << "</h1>\n";

            // Iterar sobre los pares de números primos en `numero`
            for (size_t j = 0; j + 1 < numero.size(); j += 2)
            {
                body << "<p>" << numbers[i] << " = " << numero[j] << " + " << numero[j + 1] << "</p>\n";
            }
        }
        else
        {
            body << "<h2 class=\"err\">" << numbers[i] << "</h2>\n"
                 << "<p>" << numbers[i] << " is not an even number greater than 2.</p>\n";
        }

        // Construir el cuerpo de la respuesta
        this->response.body() << "<!DOCTYPE html>\n"
                              << "<html lang=\"en\">\n"
                              << "  <meta charset=\"ascii\"/>\n"
                              << "  <title>Goldbach's Sums Results</title>\n"
                              << "  <style>body {font-family: monospace}"
                                 ".err {color: red} span {margin-right: 20px}</style>\n"
                              << body.str()
                              << "  <hr><p><a href=\"/\">Back</a></p>\n"
                              << "</html>\n";

    }
    // Enviar la respuest
    this->response.send();
}

