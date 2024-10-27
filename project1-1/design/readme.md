# Concurrent Web Server (Technical Documentation)

## Overview
This project implements a concurrent web server in C++ designed to handle multiple client requests simultaneously. The server leverages the **Pthreads** library to create and manage threads, allowing efficient handling of multiple requests by processing them in parallel.

The server hosts two web applications:
1. **Prime Factorization**: Decomposes a number into its prime factors.
2. **Goldbach Sums**: Finds prime pairs that sum up to a given even number (related to the Goldbach conjecture).

## Problem Statement
Once we understand the concept of a web server, we can start to think about the problem. This project are base in <a href="https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/ejemplos/#prod_cons_pattern"> Jeisson Hidalgo's code</a> that implements the producer-consumer pattern. The producer-consumer pattern is a synchronization pattern that allows us to create a buffer between two threads. The producer thread writes data to the buffer and the consumer thread reads data from the buffer. There's an image taken from <a href="https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/ejemplos/#prod_cons_pattern"> Jeisson Hidalgo's ecample</a> that shows the producer-consumer pattern.

<img src="https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/ejemplos/taskc/prod_cons_pattern/design/network_simulation_given.svg">

I our case we need modify the code to convert it from serial implementation to a concurrent implementation. The server should be able to handle multiple requests concurrently.

## Architecture
The server is built with a modular architecture, where different components handle specific tasks:
- **Connection Pool**: Manages threads that handle incoming client requests.
- **Request Queue**: Stack in which the different requests arrive
- HandleConnection: It is responsible for differentiating the different connections and putting them in the pending request stack
- Pending Request Queue: The requests arrive divided by their number, for their respective processes
- Calculators team: It is responsible for processing the numbers, saving the result and then putting it in the pile to pack them
- Processed cal Queue: Queue in which the results arrive to wait to be sent to the user
- Packer: It is responsible for verifying if all the results requested by the user are there, in order to send the complete response
- Dispacher: Create and deliver complete solutions to users

The following diagram illustrates the server's architecture:

![Architecture Diagram](img/diagram2.svg)

## Server Workflow
1. **Listening for Connections**: The server listens on a specified port for incoming HTTP requests.
2. **Queueing Requests**: Accepted connections are enqueued in a request queue.
3. **Processing Requests**: The connection pool dispatches threads to handle each request from the queue.
4. **Sending Responses**: Each request handler processes and sends an HTTP response back to the client, delivering either the prime factorization result or Goldbach sum pairs.

## Applications

### Prime Factorization
- **Endpoint**: `/fact`
- **Function**: Decomposes a given number into its prime factors.
- **Request Format**: 
GET /fact?number=<'number'>


### Goldbach Sums
- **Endpoint**: `/golbach`
- **Function**: Finds pairs of prime numbers that sum up to a specified even number.
- **Request Format**: 
GET /goldbach?number=<'number'>


## Concurrency Details
The server uses an **extended producer-consumer model**:

- **Producers**: There are multiple producers that accept incoming connections and place them into different work queues. Each queue can be intended for specific types of requests or priority levels, allowing for better organization and handling of incoming tasks.
    
- **Consumers**: A group of consumer threads, organized into several thread pools, dequeue and process each request. Each thread runs focused on your own task, this ensures that many parts of the project can be executed at the same time
    

This concurrent model allows the server to handle multiple client connections efficiently, distributing the load across threads and queues in a balanced manner. The implementation of multiple queues and specialized consumers ensures that requests are processed in an orderly and prioritized manner, improving the system's responsiveness and scalability.
## Installation and Setup

### Prerequisites
- C++ compiler with support for Pthreads (e.g., GCC on Unix-based systems)
- `make` utility

### Steps
1. Clone the repository:
 ```bash
 git clone <repository_url>
 cd <repository_folder>
```
2. Compile the server:

```bash
make -j
```

3. Run the server:

```bash
make run
```

