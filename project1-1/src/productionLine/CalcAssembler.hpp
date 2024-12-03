#include "../prodcons/Assembler.hpp"
#include "Calculator.hpp"
#include "Socket.hpp"
#include "HttpRequest.hpp"
#include "../webapp/ProductionLineWebApp.hpp"

class CalcAssembler : public Assembler<Socket, Calculator*> {
 private:
    std::vector<ProductionLineWebApp*> applications;

 public:
    /// Constructor
    explicit CalcAssembler(std::vector<ProductionLineWebApp*> applications);
    int run() override;
    /// Consume
    /// Get requests from the stack
    /// @param data Queue whit requests
    void consume(Socket data) override;
    /// @brief handle Client Connection.
    /// Create the new http whit the request
    /// @param client Specific request from user
    void handleClientConnection(Socket& client);
    /// @brief handle Http Request.
    /// Show IP and Request and retunr rute
    /// @param httpRequest Request from user
    /// @param httpResponse Response from Web
    bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse);
    /// @brief route.
    /// Give the route from the applications
    /// @param httpRequest Request from user
    /// @param httpResponse Response from Web
    bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
};
