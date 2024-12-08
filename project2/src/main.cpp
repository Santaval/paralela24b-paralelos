// Copyriht Aaron Josue Santana Valdelomar - Universidad de Costa Rica 2024
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

#include "Particle.hpp"
#include "defines.hpp"
#include "Universe.hpp"

std::vector<JobData> loadJobsFromFile(const std::string& path) {
    FILE* file = fopen(path.c_str(), "r");
    if (!file) {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(1);
    }
    std::vector<JobData> jobs;
    magnitude_t delta_time, final_time;
    char universe_file[100];
    while (fscanf(file, "%s %lf %lf\n", universe_file, &delta_time,
      &final_time) != EOF) {
        jobs.push_back({delta_time, final_time, std::string(universe_file)});
    }
    std::string directory = path.substr(0, path.find_last_of("/\\"));
    for (auto& job : jobs) job.directory = directory;
    fclose(file);
    return jobs;
}

void writeToFile(JobData job, Universe& universe) {
  // path format: <directory>/<filename-universeCurrentTime>.tsv
  std::string path = job.directory + "/" + job.path + "-" + std::to_string(universe.getCurrentTime()) + ".tsv";
    FILE* file = fopen(path.c_str(), "w");
    if (!file) {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(1);
    }
    for (auto particle : universe.getParticles()) {
        Vector position = particle->getPosition();
        Vector velocity = particle->getVelocity();
        Vector acceleration = particle->getAcceleration();
        fprintf(file, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
           particle->getMass(), particle->getRadio(), position.x, position.y, position.z,
            velocity.x, velocity.y, velocity.z, acceleration.x, acceleration.y, acceleration.z);
    }
    fclose(file);
}

#ifndef INTERFACE
int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_jobs_file" << std::endl;
    return 1;
  }
  std::vector<JobData> jobs = loadJobsFromFile(argv[1]);
  for (size_t i = 0; i < jobs.size(); i++) {
    JobData job = jobs[i];
    Universe universe(job.delta_time, job.final_time, job.directory + "/" + job.path);
    while (universe.particlesAlive() > 1 && (universe.getCurrentTime() < universe.getFinalTime())) {
      std::cout << "Time: " << universe.getCurrentTime() << std::endl;
      universe.next();
    }
    writeToFile(job, universe);
  }
}
#endif
