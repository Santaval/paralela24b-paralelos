// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <csignal>
#include <iostream>

#include "HttpApp.hpp"
#include "HttpConnectionHandler.hpp"
#include "SlaveServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"


const char* const usage =
  "Usage: webserver [port] [queue capacity] [master server port]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  queue       Queue capacity\n";

// Inicializa el puntero de la instancia como nullptr
SlaveServer* SlaveServer::instance = nullptr;

// Método estático para obtener la instancia de Singleton
SlaveServer* SlaveServer::getInstance() {
  if (instance == nullptr) {
    instance = new SlaveServer();
  }
  return instance;
}

SlaveServer::SlaveServer() {
}

SlaveServer::~SlaveServer() {}

void SlaveServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void SlaveServer::chainWebApp(ProductionLineWebApp* application) {
  assert(application);
  this->applications.push_back(application);
}

int SlaveServer::run() {
  return 0;
}

int SlaveServer::run(int argc, char* argv[]) {
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
      Log::getInstance().start();

      this->startProductionLine();

      // Start waiting for connections
      // TODO(you): Log the main thread id
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));


      // Accept all client connections. The main process will get blocked
      // running this method and will not return. When SlaveServer::stop() is
      // called from another execution thread, an exception will be launched
      // that stops the acceptAllConnections() invocation and enters in the
      // catch below. Then, the main thread can continue stopping apps,
      /// finishing the server and any further cleaning it requires.
      this->acceptAllConnections();
    } else {
      return EXIT_FAILURE;
    }
  } catch (const std::runtime_error& error) {
    std::cerr << error.what() << std::endl;
  }

  if (this->appsStarted) {
    this->stopApps();
  }

  this->stop();

  return EXIT_SUCCESS;
}

void SlaveServer::startApps() {
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->start();
  }
}

void SlaveServer::stopApps() {
  // Stop web applications. Give them an opportunity to clean up
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->stop();
  }
}


bool SlaveServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 1) {
    this->port = argv[1];
  }

  if (argc >= 2) {
    this->queueCapacity = std::stoi(argv[3]);
  }

  if (argc >= 3) {
    this->masterServerPort = argv[4];
  }


  return true;
}

void SlaveServer::createCalcWorkers() {
  for (int index = 0; index < this->calcWorkersCount; ++index) {
    CalculatorWorker* worker = new CalculatorWorker();
    this->calcWorkers.push_back(worker);
  }
}

void SlaveServer::setCalcWorkersQueues() {
  for (int index = 0; index < this->calcWorkersCount; ++index) {
    this->calcWorkers.at(index)->setConsumingQueue(this->pendingCalcsQueue);
    this->calcWorkers.at(index)->setProducingQueue(this->resultDispatcher->
      getConsumingQueue());
  }
}


void SlaveServer::startProductionLine() {
  this->resultDispatcher = new ResultDispatcher();
  this->createCalcWorkers();

  // create queues
  this->pendingCalcsQueue = new Queue<Calculator*>(this->queueCapacity);
  this->setProducingQueue(this->pendingCalcsQueue);
  this->setCalcWorkersQueues();

  // start threads
  this->initCalcWorkers();
  this->resultDispatcher->startThread();

  // Start all web applications
  this->startApps();
}


void SlaveServer::stop() {
  this->resultDispatcher->waitToFinish();
  for (int index = 0; index < this->calcWorkersCount; ++index) {
    this->calcWorkers.at(index)->waitToFinish();
  }

  // free memory
  for (int index = 0; index < this->calcWorkersCount; ++index) {
    delete this->calcWorkers.at(index);
  }
  delete this->pendingCalcsQueue;
}

void SlaveServer::initCalcWorkers() {
  for (int index = 0; index < this->calcWorkersCount ; ++index) {
    this->calcWorkers.at(index)->startThread();
  }
}

void SlaveServer::handleClientConnection(Socket& client) {
  CalcRequest request = this->parseRequestLine(client);

  if (request == CalcRequest()) {
    int threadsNumber = std::thread::hardware_concurrency();
    for (int i = 0; i < threadsNumber; i++) {
      this->produce(nullptr);
    }
    this->stopListening();
  }

  if (request.number != -1) {
    Calculator* calculator = this->assembleCalculator(request);
    this->produce(calculator);
  }
}

void SlaveServer::handleSignal(int signal) {
  Log::append(Log::INFO, "signal", "Signal " +
      std::to_string(signal) + " received");
    SlaveServer::getInstance()->stopListening();
    throw std::runtime_error("Stop server in progress...");
}

CalcRequest SlaveServer::parseRequestLine(Socket& client) {
  while (true) {
    std::string requestLine;
    if (!client.readLine(requestLine, '\n')) {
      Log::append(Log::ERROR, "CalcAssembler", "Failed to read from client");
      break;
    }

    // line format: "type:string,pendingRequest:HttpPendingRequest*,
    // numberIndex:int,number:int"

    std::istringstream lineStream(requestLine);
    std::string type, pendingRequest, numberIndexStr, numberStr;

    std::getline(lineStream, type, ',');
    std::getline(lineStream, pendingRequest, ',');
    std::getline(lineStream, numberIndexStr, ',');
    std::getline(lineStream, numberStr, ',');

    const int numberIndex = std::stoi(numberIndexStr);
    const int number = std::stoi(numberStr);

    // convert the string to a pointer
    std::uintptr_t address = std::stoull(pendingRequest, nullptr, 16);
    HttpPendingRequest* pointer = reinterpret_cast<HttpPendingRequest*>
      (address);
    CalcRequest calcRequest = CalcRequest(type, pointer, numberIndex, number);
    return calcRequest;
  }
  return CalcRequest("", nullptr, -1, -1);
}

Calculator* SlaveServer::assembleCalculator(CalcRequest request) {
  for (size_t i = 0; i < this->applications.size(); i++) {
    Calculator* calculator = this->applications[i]->buildCalculator(request);
    if (calculator != nullptr) {
      return calculator;
    }
  }
  return nullptr;
}
