# Concurrent Web Server

## Introduction
This project is a simple web server that can handle multiple requests concurrently. For that purpose, we used <a href="https://es.wikipedia.org/wiki/Pthreads"> Pthreads ,</a> library that allows us to create threads in C++. 

## What is a Web Server?
Before start the explanation of the project, we need to understand what is a web server. A web server is a software that uses HTTP protocol to serve the files that form the web pages to the clients. The clients are the web browsers that request the files to the server. The server receives the request, processes it and sends the response back to the client.

## How does it work?
The server is a simple program that listens to a port and waits for incoming connections. When a client connects to the server handle the request. The request handler reads the request, processes it and sends the response back to the client. But, what happens if another client connects to the server while the first client is being served? Well the server should be a multi-tasking expert and handle the requests concurrently, and this is our goal.

<img src="https://res.cloudinary.com/djiafuqdd/image/upload/v1726725146/client-server_xpdc5a.png">


## Problem Statement
Once we understand the concept of a web server, we can start to think about the problem. This project are base in <a href="https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/ejemplos/#prod_cons_pattern"> Jeisson Hidalgo's code</a> that implements the producer-consumer pattern. The producer-consumer pattern is a synchronization pattern that allows us to create a buffer between two threads. The producer thread writes data to the buffer and the consumer thread reads data from the buffer. There's an image taken from <a href="https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/ejemplos/#prod_cons_pattern"> Jeisson Hidalgo's ecample</a> that shows the producer-consumer pattern.

<img src="https://jeisson.ecci.ucr.ac.cr/concurrente/2021b/ejemplos/taskc/prod_cons_pattern/design/network_simulation_given.svg">

I our case we need modify the code to convert it from serial implementation to a concurrent implementation. The server should be able to handle multiple requests concurrently.