#include "HttpFactPendingRequest.hpp"

std::string HttpFactPendingRequest::buildResponse() {
    std::string response = "The factorial of ";
    response += std::to_string(numbers[0]);
    response += " is ";
    response += std::to_string(results[0][0]);
    response += ".\n";
    return response;
}