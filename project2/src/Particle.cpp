// Copyright Aaron Santana Valdelomar - Univerdidad de Costa Rica 2024
#include <cmath>
#include <iostream>
#include "Particle.hpp"

Particle::Particle(magnitude_t mass, magnitude_t radio, Vector position,
    Vector velocity)
    :mass(mass), radio(radio), acceleration(Vector(0, 0, 0)),
    position(position), velocity(velocity)  {}

Particle::~Particle() {}

Vector Particle::calcAttractionForce(const Particle* atractor) {
    Vector distance = this->position - atractor->position;
    magnitude_t m = sqrt(pow(distance.x, 2) + pow(distance.y, 2) + pow(distance.z, 2));
    magnitude_t scalar = -G_CONST * this->mass * atractor->mass /
    pow(distance.magnitude(), 3);
    return distance * scalar;
}

void Particle::setAcceleration(Vector acceleration) {
    this->acceleration = acceleration;
}

void Particle::setVelocity(magnitude_t delta_time) {
    if (acceleration.magnitude() == 0) {
        return;
    }
    this->velocity = this->velocity + this->acceleration * delta_time;
}

void Particle::setPosition(magnitude_t delta_time) {
    Vector localVelocity = this->velocity;
    this->position = this->position + localVelocity * delta_time;
}

void Particle::absorb(Particle& other) {
    other.markAsAbsorbed();
    this->radio = cbrt(pow(this->radio, 3) + pow(other.radio, 3));
    this->mass += other.mass;
    Vector localVelocity = this->velocity;
    Vector otherVelocity = other.velocity;
    this->velocity = (localVelocity * this->mass + otherVelocity * other.mass) *
    (1 / (this->mass + other.mass));
}
