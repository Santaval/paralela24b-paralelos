// Copyright Aaron Santana Valdelomar - Univerdidad de Costa Rica 2024
#pragma once
#include "defines.hpp"
#include "Vector.hpp"

/**
 * @class Particle
 * @brief Represents a particle in a physical simulation.
 * 
 * The Particle class encapsulates the properties and behaviors of a particle,
 * including its mass, radius, acceleration, velocity, and position. It provides
 * methods to manipulate and retrieve these properties, as well as to calculate
 * the attraction force exerted by another particle.
 * 
 * @note This class assumes that the Vector type and magnitude_t type are defined
 * elsewhere in the codebase.
 * 
 * @file Particle.hpp
 */
class Particle {
 private:
    /**
     * @brief Represents the mass of the particle.
     */
    magnitude_t mass;

    /**
     * @brief Represents the radius of the particle.
     */
    magnitude_t radio;
    /**
     * @brief Represents the acceleration of the particle.
     * 
     * This vector holds the acceleration components of the particle in the 
     * respective coordinate system.
     */
    Vector acceleration = Vector(0, 0, 0);

    /**
     * @brief Represents the position of the particle.
     * 
     * This vector holds the position components of the particle in the 
     * respective coordinate system.
     */
    Vector position;

    /**
     * @brief Represents the velocity of the particle.
     * 
     * This vector holds the velocity components of the particle in the 
     * respective coordinate system.
     */
    Vector velocity;

    bool absorbed = false;

 public:
    /**
     * @brief Constructs a new Particle object.
     * 
     * @param mass The mass of the particle.
     * @param radio The radius of the particle.
     * @param acceleration The acceleration vector of the particle.
     * @param velocity The velocity vector of the particle.
     * @param position The position vector of the particle.
     */
    Particle(magnitude_t mass, magnitude_t radio,
      Vector velocity, Vector position);
    /**
     * @brief Destructor for the Particle class.
     * 
     * This destructor is responsible for cleaning up any resources
     * that the Particle object may have acquired during its lifetime.
     */
    ~Particle();
    /**
     * @brief Calculates the attraction force exerted by a given attractor particle.
     * 
     * This function computes the magnitude of the attraction force between the current particle
     * and the specified attractor particle based on their properties such as mass and distance.
     * 
     * @param attractor The particle that exerts the attraction force on the current particle.
     * @return magnitude_t The magnitude of the attraction force.
     */
    Vector calcAttractionForce(const Particle* atractor);
    /**
     * @brief Sets the acceleration of the particle.
     * 
     * This function updates the acceleration vector of the particle to the specified value.
     * 
     * @param acceleration The new acceleration vector to be set.
     */
    void setAcceleration(Vector acceleration);
   /**
    * @brief Sets the velocity of the particle based on the given acceleration and time delta.
    * 
    * This function calculates the new velocity of the particle by applying the provided
    * acceleration over the specified time interval (delta_time).
    * 
    * @param acceleration The acceleration vector to be applied to the particle.
    * @param delta_time The time interval over which the acceleration is applied.
    */
    void setVelocity(magnitude_t delta_time);
    /**
     * @brief Sets the position of the particle.
     * 
     * @param position A Vector object representing the new position of the particle.
     */
    void setPosition(magnitude_t delta_time);
    /**
     * @brief Retrieves the acceleration vector of the particle.
     * 
     * @return Vector representing the acceleration of the particle.
     */
    inline Vector getAcceleration()  const { return acceleration; }
    /**
     * @brief Get the velocity of the particle.
     * 
     * @return Vector representing the velocity of the particle.
     */
    inline Vector getVelocity() const { return velocity; }
    /**
     * @brief Get the position of the particle.
     * 
     * @return Vector The current position of the particle.
     */
    inline Vector getPosition() const { return position; }

    inline magnitude_t getRadio() const { return radio; }

   /**
    * @brief Get the mass of the particle.
    * 
    * @return magnitude_t The mass of the particle.
    */
    inline magnitude_t getMass() const { return mass; }

    // absorb method
    void absorb(Particle& other);

    inline bool isAbsorbed() const { return absorbed; }
    inline void markAsAbsorbed() { this->absorbed = true; }

    bool operator>(const Particle& other) const {
        return this->mass < other.mass;
    }

    bool operator<(const Particle& other) const {
        return this->mass > other.mass;
    }
};
