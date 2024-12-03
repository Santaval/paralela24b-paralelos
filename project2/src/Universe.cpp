// Copyright Aaron Santana Valdelomar - Univerdidad de Costa Rica 2024
#pragma once

#include <unistd.h>

#include "defines.hpp"
#include "Particle.hpp"
#include "Universe.hpp"
#include <iostream>

Universe::Universe(magnitude_t delta_time, magnitude_t final_time)
  : delta_time(delta_time), final_time(final_time) {}

Universe::~Universe() {}

void Universe::addParticle(Particle* particle) {
  particles.push_back(particle);
}

void Universe::next() {
  this->detectCollisions();
  this->updateVelocities();
  this->updatePositions();
  this->current_time += delta_time;
}

void Universe::detectCollisions() {
  for (size_t i = 0; i < particles.size(); i++) {
    for (size_t j = i + 1; j < particles.size(); j++) {
      if (i != j && areColliding(particles[i], particles[j])) {
        handleCollision(particles[i], particles[j]);
      }
    }
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

void Universe::updateVelocities() {
  for (size_t i = 0; i < particles.size(); i++) {
      Vector force(0, 0, 0);
      for (size_t j = 0; j < particles.size(); j++) {
        bool isAbsorbed = particles[j]->isAbsorbed() || particles[i]->isAbsorbed();
          if (i != j && !isAbsorbed) {
              force = force + particles[i]->calcAttractionForce(particles[j]);
          }
      }
      Vector acceleration = force * (1 / particles[i]->getMass());
      particles[i]->setAcceleration(acceleration);
      particles[i]->setVelocity(this->delta_time);
  }
}

void Universe::updatePositions() {
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
