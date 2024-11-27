// Copyright 2024 Aaron Santana, Isaias Alfaro

#include "HttpPendingRequest.hpp"
#include "Log.hpp"

void HttpPendingRequest::pushNUmber(int number) {
    this->numbers.push_back(number);
}

void HttpPendingRequest::pushResult(int index, std::vector<int64_t> result) {
    if (index >= 0 && index < results.size()) {
        results[index] = result;  // Asignar en la posición específica
    } else {
        // Si el índice es inválido, puedes manejar el error
        // o simplemente usar push_back para agregar al final.
        results.push_back(result);
    }
}
