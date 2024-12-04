#include "CalcDispatcherClient.hpp"



CalcDispatcherClient::CalcDispatcherClient(std::string ip, std::string port)
    : ip(ip), port(port) {
}

CalcDispatcherClient::~CalcDispatcherClient() {
}




void CalcDispatcherClient::sendNetworkMessage(CalcRequest message) {
    if (!this->isConnected()) {
        this->connect(ip.c_str(), port.c_str());
    }

    Socket socket = this->getSocket();
    socket << message << "\n";
}
