// Copyright 2024 Aaron Santana, Isaias Alfaro
#pragma once

#include "../prodcons/Consumer.hpp"
#include "HttpPendingRequest.hpp"


class HttpResponseDispatcher : public Consumer<HttpPendingRequest*> {
 public:
    explicit HttpResponseDispatcher(Queue<HttpPendingRequest*>* 
            httpPendingRequestQueue = nullptr)
        : Consumer<HttpPendingRequest*>(httpPendingRequestQueue) {
            this->createOwnQueue();
    }
    virtual ~HttpResponseDispatcher() {
    }
 protected:
        /// @brief Consume a HttpPendingRequest
        /// @param HttpPendingRequest
        void consume(HttpPendingRequest* httpPendingRequest) override;
        /// @brief Override of run method from Thread
        int run() override;
};
