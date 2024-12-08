// Copyriht Aaron Josue Santana Valdelomar - Universidad de Costa Rica 2024
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

#include "Particle.hpp"
#include "defines.hpp"
#include "Universe.hpp"

#define DISPLAY_SCALE 1
// void renderParticles(sf::RenderWindow& window, Universe& universe) {
  
//   const std::vector<Particle*>& particles = universe.getParticles();
//   // Clear the window

//   window.clear();

//   // Get the center of the window
//   sf::Vector2u windowSize = window.getSize();
//   sf::Vector2f center(windowSize.x / 2.0f, windowSize.y / 2.0f);
//   sf::Font font;
//   font.loadFromFile("/home/savaldev/Documents/ucr/paralela24b-paralelos/project2/Montserrat-Regular.ttf");


//       // print time
//     sf::Text text5;
//     text5.setFont(font);
//     text5.setString("T: " + std::to_string(universe.getCurrentTime()));
//     text5.setCharacterSize(8);
//     text5.setFillColor(sf::Color::White);
//     text5.setPosition(0, 0);
//     window.draw(text5);
//   // Draw particles
//   for (const auto& particle : particles) {
//     if (particle->isAbsorbed()) {
//       continue;
//     }
//     sf::CircleShape shape(particle->getRadio() / DISPLAY_SCALE); // Use radius for simplicity
//     shape.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE);
//     // add label with velocity
//     sf::Text text;
//     text.setFont(font);
//     text.setString("V: " + std::to_string(particle->getVelocity().magnitude()));
//     text.setCharacterSize(8);
//     text.setFillColor(sf::Color::White);
//     text.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 20);

//     // print position
//     sf::Text text2;
//     text2.setFont(font);
//     text2.setString("P: " + std::to_string(particle->getPosition().x) + ", " + std::to_string(particle->getPosition().y));
//     text2.setCharacterSize(8);
//     text2.setFillColor(sf::Color::White);
//     text2.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 30);

//     // print mass
//     sf::Text text3;
//     text3.setFont(font);
//     text3.setString("M: " + std::to_string(particle->getMass()));
//     text3.setCharacterSize(8);
//     text3.setFillColor(sf::Color::White);
//     text3.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 40);
//     // radius
//     sf::Text text4;
//     text4.setFont(font);
//     text4.setString("R: " + std::to_string(particle->getRadio()));
//     text4.setCharacterSize(8);
//     text4.setFillColor(sf::Color::White);
//     text4.setPosition(center.x + particle->getPosition().x / DISPLAY_SCALE, center.y - particle->getPosition().y / DISPLAY_SCALE + 50);
//     window.draw(text4);
//     window.draw(text3);
//     window.draw(text2);
//     window.draw(text);

//     shape.setFillColor(sf::Color::Green);
//     window.draw(shape);
//   }

//   // Draw axes
//   sf::Vertex xAxis[] = {
//     sf::Vertex(sf::Vector2f(0, center.y), sf::Color::Red),
//     sf::Vertex(sf::Vector2f(windowSize.x, center.y), sf::Color::Red)
//   };
//   sf::Vertex yAxis[] = {
//     sf::Vertex(sf::Vector2f(center.x, 0), sf::Color::Red),
//     sf::Vertex(sf::Vector2f(center.x, windowSize.y), sf::Color::Red)
//   };
//   window.draw(xAxis, 2, sf::Lines);
//   window.draw(yAxis, 2, sf::Lines);

//   // Display the contents of the window
//   window.display();
// }

// std::vector<JobData> loadJobsFromFile(const std::string& path) {
//     FILE* file = fopen(path.c_str(), "r");
//     if (!file) {
//         std::cerr << "Error opening file: " << path << std::endl;
//         exit(1);
//     }
//     std::vector<JobData> jobs;
//     magnitude_t delta_time, final_time;
//     char universe_file[100];
//     while (fscanf(file, "%s %lf %lf\n", universe_file, &delta_time,
//       &final_time) != EOF) {
//         jobs.push_back({delta_time, final_time, std::string(universe_file)});
//     }
//     std::string directory = path.substr(0, path.find_last_of("/\\"));
//     for (auto& job : jobs) job.directory = directory;
//     fclose(file);
//     return jobs;
// }

#ifdef INTERFACE
int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_jobs_file" << std::endl;
    return 1;
  }
  std::vector<JobData> jobs = loadJobsFromFile(argv[1]);
  for (size_t i = 0; i < jobs.size(); i++) {
    JobData job = jobs[i];
    std::cout << "Running job: " << job.directory << "/" << job.path << std::endl;
    Universe universe(job.delta_time, job.final_time, job.directory + "/" + job.path);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Universe");
    while (window.isOpen() && (universe.particlesAlive() > 1 &&
        (universe.getCurrentTime() < universe.getFinalTime()))) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }
      universe.next();
      renderParticles(window, universe);
      sleep(0.1);
    }
  }
}
#endif
