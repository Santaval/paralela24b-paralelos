// Copyriht Aaron Josue Santana Valdelomar - Universidad de Costa Rica 2024
#pragma once
#include <SFML/Graphics.hpp>

#include "Particle.hpp"
#include "defines.hpp"
#include "Universe.hpp"
#include <unistd.h>
#include <iostream>

#define DISPLAY_SCALE 0.2

void renderParticles(sf::RenderWindow& window, const std::vector<Particle*>& particles) {
  // Clear the window
  window.clear();

  // Get the center of the window
  sf::Vector2u windowSize = window.getSize();
  sf::Vector2f center(windowSize.x / 2.0f, windowSize.y / 2.0f);

  // Draw particles
  for (const auto& particle : particles) {
    if (particle->isAbsorbed()) {
      continue;
    }
    sf::CircleShape shape(particle->getRadio()); // Use radius for simplicity
    shape.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE);
    
    // add label with velocity
    sf::Font font;
    font.loadFromFile("/home/savaldev/Documents/ucr/paralela24b-paralelos/project2/Montserrat-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("V: " + std::to_string(particle->getVelocity().magnitude()));
    text.setCharacterSize(8);
    text.setFillColor(sf::Color::White);
    text.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 20);

    // print position
    sf::Text text2;
    text2.setFont(font);
    text2.setString("P: " + std::to_string(particle->getPosition().x) + ", " + std::to_string(particle->getPosition().y));
    text2.setCharacterSize(8);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 30);

    // print acceleration
    sf::Text text3;
    text3.setFont(font);
    text3.setString("A: " + std::to_string(particle->getAcceleration().magnitude()));
    text3.setCharacterSize(8);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 40);
    // radius
    sf::Text text4;
    text4.setFont(font);
    text4.setString("R: " + std::to_string(particle->getRadio()));
    text4.setCharacterSize(8);
    text4.setFillColor(sf::Color::White);
    text4.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 50);

    window.draw(text4);
    window.draw(text3);
    window.draw(text2);
    window.draw(text);

    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
  }

  // Draw axes
  sf::Vertex xAxis[] = {
    sf::Vertex(sf::Vector2f(0, center.y), sf::Color::Red),
    sf::Vertex(sf::Vector2f(windowSize.x, center.y), sf::Color::Red)
  };
  sf::Vertex yAxis[] = {
    sf::Vertex(sf::Vector2f(center.x, 0), sf::Color::Red),
    sf::Vertex(sf::Vector2f(center.x, windowSize.y), sf::Color::Red)
  };
  window.draw(xAxis, 2, sf::Lines);
  window.draw(yAxis, 2, sf::Lines);

  // Display the contents of the window
  window.display();
}


int main(int argc, char const *argv[]) {
  Universe universe(20, 500000);
  universe.addParticle(new Particle(2500, 5, Vector(0, 0, 0), Vector(0, 0, 0)));
  universe.addParticle(new Particle(60, 1, Vector(15, 5, 0), Vector(0, 0, 0)));
  universe.addParticle(new Particle(10000, 20, Vector(120, -30, 0), Vector(0, 0, 0)));
  universe.addParticle(new Particle(50, 20, Vector(-12, 30, 0), Vector(0, 0, 0)));

  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Particle Simulation");


  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    if (universe.getCurrentTime() < universe.getFinalTime() && universe.particlesAlive() > 1) {
      universe.next();
      renderParticles(window, universe.getParticles());
      sleep(0.1);
    }
  }
}
