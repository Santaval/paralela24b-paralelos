#include <vector>

#include "ResultDispatcher.hpp"
#include "Log.hpp"


ResultDispatcher::ResultDispatcher() : Consumer<Calculator*>(nullptr, nullptr) {
    this->createOwnQueue();
}

ResultDispatcher::~ResultDispatcher() {
}

int ResultDispatcher::run() {
    this->consumeForever();
    return 0;
}

void ResultDispatcher::consume(Calculator* calculator) {
    Socket socket =  this->connect("192.168.0.113", "8082");
    std::vector<int64_t> result = calculator->getResult();
    socket
    << calculator->getPendingRequest() << ","
    << calculator->getCalcIndex() << ","
    << result.size() << ",";

    for (int i = 0; i < result.size(); i++) {
        Log::append(Log::INFO, "ResultDispatcher", std::to_string(result[i]));
        socket << result[i];
        if (i < result.size() - 1) {
            socket << ",";
        }
    }
    socket << "\n";
    socket.send();
    this->close();
}