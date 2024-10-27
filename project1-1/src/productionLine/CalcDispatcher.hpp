// Copyright 2020-2024 Jeisson Hidalgo-Cespedes. ECCI-UCR. CC BY 4.0
#pragma once


#include "../prodcons/Consumer.hpp"
#include "../prodcons/Producer.hpp"
#include "../http/HttpPendingRequest.hpp"
#include "Calculator.hpp"

/**
 * @brief A Dispatcher class example
 */
class CalcDispatcher : public Consumer<HttpPendingRequest*>, public Producer<Calculator*> {
  DISABLE_COPY(CalcDispatcher);

 protected:
  ///
  int dispatcherDelay = 0;

 public:
  /// Start redirecting network messages
  int run() override;
};

