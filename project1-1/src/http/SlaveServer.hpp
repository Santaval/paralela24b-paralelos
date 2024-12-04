// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#pragma once

#include <thread>
#include <vector>
#include <string>

#include "TcpServer.hpp"
#include "HttpConnectionHandler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../productionLine/CalcDispatcher.hpp"
#include "../productionLine/Calculator.hpp"
#include "Queue.hpp"
#include "../productionLine/CalculatorWorker.hpp"
#include "../productionLine/CalcAssembler.hpp"
#include "../productionLine/ResultDispatcher.hpp"
#include "../productionLine/ResultAssembler.hpp"
#include "HttpResponseDispatcher.hpp"
#include "../webapp/ProductionLineWebApp.hpp"
#include "../productionLine/CalcResult.hpp"
#include "Socket.hpp"




#define DEFAULT_PORT "8080"

class HttpApp;

/**
@brief Implements a minimalist web server.

A web server is a software that listens for client connections,
accept them, waits for requests of resources, and answers the requests. All
communication with clients are following the rules of the HTTP (HyperText
Transfer Protocol).

A SlaveServer is a stand-alone object, you do not require to inherit a class.
A web server should be a generic software that may be used for many
applications. A web application is a piece of software that deals with a
specific domain, e.g: a marble shop, a video game, a newspaper, and so on.
Your SlaveServer can be connected with an arbitrary number of web
applications. The following code shows how the server can answer requests
of two different applications, one for lottery results and other for pets.

```cpp
int main(int argc, char* argv[]) {
  // Create the web server
  SlaveServer SlaveServer;
  // Create some web applications
  LotteryWebApp lotteryWebApp;
  PetsWebApp petsWebApp;
  // Register the web application(s) with the web server
  SlaveServer.chainWebApp(&lotteryWebApp);
  SlaveServer.chainWebApp(&petsWebApp);
  // Start the web server
  return SlaveServer.run(argc, argv);
}
```

In the previous code, when a request arrives, the server asks the lottery
application to examine the request. The lottery application will study the
HttpRequest fields (e.g: URI) to determine if the request is about lottery.
In such case, the web application returns true to the server indicating it
managed the request. If the application returns false, indicates the server
that the request was not intended for the lottery application, and the server
repeats the process with the following application in the chain: the pets
application. If no application manages the request, a 404 Not-found response
is sent to the client.
*/
class SlaveServer : public TcpServer, Producer<Calculator*> {
  DISABLE_COPY(SlaveServer);

 private:
    // Almacena la única instancia de SlaveServer
    static SlaveServer* instance;

 protected:
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;
  /// Queue capacity for queues capacity
  int queueCapacity = SEM_VALUE_MAX;
  // master node address
  std::string masterNodeRoute = "localhost:8080";

  /// Chain of registered web applications. Each time an incoming HTTP request
  /// is received, the request is provided to each application of this chain.
  /// If an application detects the request is for it, the application will
  /// call the httpResponse.send() and the chain stops. If no web app serves
  /// the request, the not found page will be served.
  std::vector<ProductionLineWebApp*> applications;

  /// Pending calcs queue
  Queue<Calculator*>* pendingCalcsQueue = nullptr;

  // Pending request queue


  // set calc workers queues
  void setCalcWorkersQueues();


  // Calculator Workers threads
  // It is a vector of threads
  // Each thread will be a Calculator worker
  std::vector<CalculatorWorker*> calcWorkers;


  /// Result dispatcher
  // It is a pointer to a result dispatcher
  ResultDispatcher* resultDispatcher = nullptr;


  /// indicate if apps were started
  bool appsStarted = false;

  /// Number of connection calcWorkers threads
  // Initially, the server will use the number of cores this->consumingQueue->enqueue(Socket()); in the system
  int calcWorkersCount = std::thread::hardware_concurrency();

 public:
  // Método estático para obtener la única instancia del servidor
  static SlaveServer* getInstance();
  /// Registers a web application to the chain
  void chainWebApp(ProductionLineWebApp* application);
  /// Start the web server for listening client connections and HTTP requests
  int run(int argc, char* argv[]);
  /// Stop the web server. The server may stop not immediately. It will stop
  /// for listening further connection requests at once, but pending HTTP
  /// requests that are enqueued will be allowed to finish
  int run() override;
  void stop();
  // handle the signal
  static void handleSignal(int signal);
  /// Indefinitely listen for client connection requests and accept all of them.
  /// For each accepted connection request, the virtual onConnectionAccepted()
  /// will be called. Inherited classes must override that method
  void listenForever(const char* port);

  /// Start production line
  void startProductionLine();

 private:
  /// Constructor is private to avoid multiple instances
  SlaveServer();
  /// Destructor
  ~SlaveServer();

 protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);
  /// Start all registered applications, given them a chance to build their
  /// data structures just before starting to run
  void startApps();
  /// Stop all running applications, given them a chance to clean their data
  /// structures
  void stopApps();
  /// Create the calcWorkers threads
  void createCalcWorkers();
  /// This method is called each time a client connection request is accepted.
  void handleClientConnection(Socket& client) override;
  // Init calc workers
  void initCalcWorkers();
  /// @brief parse the request line.
  /// Parse the request line from the socket
  /// @return true on success, false on error or connection closed by peer
  CalcRequest parseRequestLine(Socket& client);
  /// Ask to webapps to build a calculator
  /// @param request Request to calculate
  /// @return Calculator
  Calculator* assembleCalculator(CalcRequest request);
};


