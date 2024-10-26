#include "HttpGolbachPendingRequest.hpp"

std::string HttpGolbachPendingRequest::buildResponse() {
    std::string response = "The Golbach of ";
    response += std::to_string(numbers[0]);
    response += " is ";
    response += std::to_string(results[0][0]);
    response += ".\n";
    return response;
}