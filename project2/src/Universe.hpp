// Copyrught Aaron Santana Valdelomar - Universidad de Costa Rica 2024
#pragma once
#include <vector>

#include "Particle.hpp"
#include "defines.hpp"

class Universe {
 private:
    magnitude_t current_time = 0;
    magnitude_t delta_time = 0;
    magnitude_t final_time = 0;
    std::vector<Particle*> particles = std::vector<Particle*>();
    size_t absorbedCount = 0;

 private:
    void handleCollision(Particle* particle1, Particle* particle2);
    bool areColliding(Particle* particle1, Particle* particle2);
 public:
    Universe(magnitude_t delta_time, magnitude_t final_time);
    ~Universe();
    void addParticle(Particle* particle);
    void clean();
    void next();
    void detectCollisions();
    void updateVelocities();
    void updatePositions();
    inline magnitude_t getCurrentTime() const { return current_time; }
    inline magnitude_t getDeltaTime() const { return delta_time; }
    inline magnitude_t getFinalTime() const { return final_time; }
    inline const std::vector<Particle*>& getParticles() const { return particles; }
    inline size_t particlesAlive() const { return particles.size() - absorbedCount; }
};
