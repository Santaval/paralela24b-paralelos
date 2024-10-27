// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <csignal>

#include "HttpApp.hpp"
#include "HttpConnectionHandler.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"


const char* const usage =
  "Usage: webserv [port] [handlers]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  handlers     Number of connection handler theads\n"
  "  queue       Queue capacity\n"
  ;

// Inicializa el puntero de la instancia como nullptr
HttpServer* HttpServer::instance = nullptr;

// Método estático para obtener la instancia de Singleton
HttpServer* HttpServer::getInstance() {
  if (instance == nullptr) {
    instance = new HttpServer();
  }
  return instance;
}

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
  // Delete all connection handlers
  for (int index = 0; index < this->connectionHandlersCount; ++index) {
    delete this->connectionHandlers.at(index);
  }
  for (int index = 0; index < this->calcWorkersCount; ++index) {
    delete this->calcWorkers.at(index);
  }
  // Delete the sockets queue
  delete this->socketsQueue;
  // Delete the pending calcs queue
  delete this->pendingCalcsQueue;
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
  application->setProducingQueue(this->calcDispatcher->getConsumingQueue());
}

int HttpServer::run(int argc, char* argv[]) {
  try {
    if (this->analyzeArguments(argc, argv)) {
      // Start the log service
      Log::getInstance().start();
      this->createQueues();
      // Create connection handlers
      this->createConnectionHandlers();


      this->startProductionLine();

      // Start waiting for connections
      // TODO(you): Log the main thread id
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
        + " port " + std::to_string(address.getPort()));


      // Accept all client connections. The main process will get blocked
      // running this method and will not return. When HttpServer::stop() is
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
  this->stop();
  return EXIT_SUCCESS;
}

void HttpServer::startApps() {
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->start();
  }
}

void HttpServer::stopApps() {
  // Stop web applications. Give them an opportunity to clean up
  for (size_t index = 0; index < this->applications.size(); ++index) {
    this->applications[index]->stop();
  }
}

void HttpServer::stopConnectionHandlers() {
  // Enqueue a stop condition for each connection handler
  for (int index = 0; index < this->connectionHandlersCount; ++index) {
    this->socketsQueue->enqueue(Socket());
  }
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests. When stopListing()
  // method is called -maybe by a secondary thread-, the web server -running
  // by the main thread- will stop executing the acceptAllConnections() method.
  this->stopConnectionHandlers();

  // If applications were started
  if (this->appsStarted) {
    // Stop all web applications
    this->stopApps();
  }

  //  join threads
  this->joinThreads();

  // Stop the log service
  Log::getInstance().stop();

  this->~HttpServer();
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    this->port = argv[1];
  }

  if (argc >= 3) {
    this->connectionHandlersCount = std::stoi(argv[2]);
  }

  if (argc >= 4) {
    this->queueCapacity = std::stoi(argv[3]);
  }

  return true;
}

void HttpServer::createConnectionHandlers() {
  this->connectionHandlers.reserve(this->connectionHandlersCount);
  for (int index = 0; index < this->connectionHandlersCount; ++index) {
    HttpConnectionHandler* handler =
        new HttpConnectionHandler(this->applications);
    handler->setConsumingQueue(this->socketsQueue);
    this->connectionHandlers.push_back(handler);
  }
}

void HttpServer::createCalcWorkers() {
  this->calcWorkers.reserve(this->calcWorkersCount);
  for (int index = 0; index < this->calcWorkersCount; ++index) {
    CalculatorWorker* worker = new CalculatorWorker();
    worker->setConsumingQueue(this->pendingCalcsQueue);
    this->calcWorkers.push_back(worker);
  }
}


void HttpServer::createQueues() {
  this->socketsQueue = new Queue<Socket>(this->queueCapacity);
  this->pendingCalcsQueue = new Queue<Calculator*>(this->queueCapacity);
}

void HttpServer::startProductionLine() {
    // connect calcDispatcher whit the pendingCalcsQueue
    this->calcDispatcher->setProducingQueue(this->pendingCalcsQueue);

    this->initConnectionHandler();
    this->initCalcWorkers();
    // Start all web applications
    this->startApps();
    this->appsStarted = true;
}

void HttpServer::initConnectionHandler() {
  for (int index = 0; index < this->connectionHandlersCount; ++index) {
    this->connectionHandlers.at(index)->startThread();
  }
}
void HttpServer::initCalcWorkers() {
  for (int index = 0; index < this->calcWorkersCount ; ++index) {
    this->calcWorkers.at(index)->startThread();
  }
}

void HttpServer::joinThreads() {
  for (int index = 0; index < this->connectionHandlersCount; ++index) {
    this->connectionHandlers.at(index)->waitToFinish();
  }
}


void HttpServer::handleClientConnection(Socket& client) {
  this->socketsQueue->enqueue(client);
}

void HttpServer::handleSignal(int signal) {
  Log::append(Log::INFO, "signal", "Signal " +
      std::to_string(signal) + " received");
    HttpServer::getInstance()->stopListening();
    throw std::runtime_error("Stop server in progress...");
}

