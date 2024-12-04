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
    this->sendNetworkMessage(CalcResult(), "192.168.0.113", "8082");
    Log::append(Log::INFO, "ResultDispatcher", "stop");
    return 0;
}

void ResultDispatcher::consume(Calculator* calculator) {
    std::vector<int64_t> result = calculator->getResult();
    this->sendNetworkMessage(CalcResult(calculator->getPendingRequest(), calculator->getCalcIndex(),
     result.size(), result), "192.168.0.113", "8082");
}

void ResultDispatcher::sendNetworkMessage(CalcResult message, char* ip, char* port) {
    Socket socket =  this->connect(ip, port);
    socket << message;
    socket.send();
    this->close();
}
