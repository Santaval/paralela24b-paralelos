// Copyright Aaron Santana Valdelomar - Univerdidad de Costa Rica 2024
#pragma once

#include <unistd.h>
#include <string>
#include <cstdio>

#include "defines.hpp"
#include "Particle.hpp"
#include "Universe.hpp"
#include <iostream>
#include <bits/std_thread.h>


Universe::Universe(magnitude_t delta_time, magnitude_t final_time, std::string path)
  : delta_time(delta_time), final_time(final_time) {
  this->chargeFromFile(path);
}

Universe::Universe(magnitude_t delta_time, magnitude_t final_time)
  : delta_time(delta_time), final_time(final_time) {}

Universe::~Universe() {}

void Universe::addParticle(Particle* particle) {
  particles.push_back(particle);
}

void Universe::next() {
  this->updateWithCollisions();
  this->updatePositions();
  this->current_time += delta_time;
}

void Universe::updateWithCollisions() {
  const size_t thread_num = std::thread::hardware_concurrency();
  const size_t chunk_size = this->particles.size() / thread_num;

  #pragma omp parallel for schedule(static, chunk_size)
  for (size_t i = 0; i < particles.size(); ++i) {
    if (particles[i]->isAbsorbed()) continue;

    Vector force(0, 0, 0);

    for (size_t j = 0; j < particles.size(); ++j) {
      if (i != j && !particles[j]->isAbsorbed()) {
        if (areColliding(particles[i], particles[j])) {
          #pragma omp critical
          {
            handleCollision(particles[i], particles[j]);
          }
        }
        force = force + particles[i]->calcAttractionForce(particles[j]);
      }
    }

    Vector acceleration = force * (1 / particles[i]->getMass());
    particles[i]->setAcceleration(acceleration);
    particles[i]->setVelocity(delta_time);
  }
}


bool Universe::areColliding(Particle* particle1, Particle* particle2) {
  Vector distance = particle1->getPosition() - particle2->getPosition();
  return particle1->getRadio() + particle2->getRadio() > distance.magnitude();
}

void Universe::handleCollision(Particle* particle1, Particle* particle2) {
  if (particle1->isAbsorbed() || particle2->isAbsorbed()) {
    return;
  }
  if (*particle1 > *particle2) {
    particle1->absorb(*particle2);
  } else if (*particle1 < *particle2) {
    particle2->absorb(*particle1);
  } else {
    particle1->absorb(*particle2);
  }
  this->absorbedCount++;
}


void Universe::updatePositions() {
  const size_t thread_num = std::thread::hardware_concurrency();
  const size_t chunk_size = this->particles.size() / thread_num;
  #pragma omp parallel for schedule(dynamic, chunk_size)
  for (size_t i = 0; i < particles.size(); i++) {
    if (!particles[i]->isAbsorbed()) {
      particles[i]->setPosition(this->delta_time);
    }
  }
}

void Universe::clean() {
  for (size_t i = 0; i < particles.size(); i++) {
    if (particles[i]->isAbsorbed()) {
      delete particles[i];
    }
  }
  particles.clear();
}

void Universe::chargeFromFile(std::string path) {
  std::cout << "Charging from file: " << path << std::endl;
  // format: mass radio x y z vx vy vz
  FILE* file = fopen(path.c_str(), "r");
  if (file == NULL) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }
  magnitude_t mass, radio, x, y, z, vx, vy, vz;
  while (fscanf(file, "%lf %lf %lf %lf %lf %lf %lf %lf\n", &mass,
    &radio, &x , &y, &z, &vx, &vy, &vz) != EOF) {
    Particle* particle = new Particle(mass, radio, Vector(x, y, z), Vector(vx, vy, vz));
    this->addParticle(particle);
  }
}
