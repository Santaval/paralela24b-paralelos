#pragma once

#include "../prodcons/Consumer.hpp"
#include "HttpPendingRequest.hpp"


class HttpResponseDispatcher : public Consumer<HttpPendingRequest*> {
 public:
    explicit HttpResponseDispatcher(Queue<HttpPendingRequest*>* httpPendingRequestQueue = nullptr)
        : Consumer<HttpPendingRequest*>(httpPendingRequestQueue) {
            this->createOwnQueue();
    }
    virtual ~HttpResponseDispatcher() {
    }
 protected:
        /// @brief Consume a HttpPendingRequest
        /// @param HttpPendingRequest
        virtual void consume(HttpPendingRequest* httpPendingRequest) override;
        /// @brief Override of run method from Thread
        virtual int run() override;
};
