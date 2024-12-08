// Copyriht Aaron Josue Santana Valdelomar - Universidad de Costa Rica 2024
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

#include "Particle.hpp"
#include "defines.hpp"
#include "Universe.hpp"
#include "Mpi.hpp"

#define MAIN_PROCESS 0

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

void sendJobData(JobData& jobData, int dest, Mpi& mpi) {
    // int plateFileLength = strlen(jobData->plateFile) + 1;
    // int directoryLength = strlen(jobData->directory) + 1;
    mpi.send(jobData.delta_time, dest);
    mpi.send(jobData.final_time, dest);
    mpi.send(jobData.path, dest);
    mpi.send(jobData.directory, dest);
}

void receiveJobData(JobData& jobData, int source, Mpi& mpi) {
    mpi.receive(jobData.delta_time, source);
    mpi.receive(jobData.final_time, source);
    mpi.receive(jobData.path, source);
    mpi.receive(jobData.directory, source);
}

void processJob(JobData& jobData) {
    Universe universe(jobData.delta_time, jobData.final_time, jobData.directory + "/" + jobData.path);
    while (universe.particlesAlive() > 1 && (universe.getCurrentTime() < universe.getFinalTime())) {
        universe.next();
    }
    writeToFile(jobData, universe);
}

#ifndef INTERFACE
int main(int argc, char* argv[]) {
  Mpi mpi(argc, argv);
  if (mpi.size() < 2) {
    std::cerr << "This program must be run with at least 2 processes" << std::endl;
    return 1;
  }

  std::cout << "Process " << mpi.rank() << " of " << mpi.size() << " is running" << std::endl;

  if (mpi.rank() == MAIN_PROCESS) {
    if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_jobs_file" << std::endl;
    return 1;
  }
  std::vector<JobData> jobs = loadJobsFromFile(argv[1]);
  size_t processedCount = 0, disconnectedCount = 0;
  int DISCONNECT_SIGNAL = 1;
  int FINISHED_JOB_SIGNAL = 1;

  for (int i = 1; i < mpi.size(); i++) {
    if (processedCount < jobs.size()) {
      bool shouldProcessAJob = true;
      mpi.send(&shouldProcessAJob, i);
      sendJobData(jobs[processedCount], i, mpi);
      processedCount++;
    } else {
      bool shouldProcessAJob = false;
      mpi.send(&shouldProcessAJob, i);
      mpi.receive(DISCONNECT_SIGNAL, i);
      disconnectedCount++;
    }
  }

    // receive jobs results
  while (disconnectedCount < (mpi.size() - 1)) {
    int* source = new int;
    mpi.receive(FINISHED_JOB_SIGNAL, MPI_ANY_SOURCE, 0, source);
    if (processedCount < jobs.size()) {
      bool shouldProcessAJob = true;
      mpi.send(shouldProcessAJob, *source);
      sendJobData(jobs[processedCount], *source, mpi);
    } else {
      bool shouldProcessAJob = false;
      mpi.send(shouldProcessAJob, *source);
      mpi.receive(DISCONNECT_SIGNAL, *source);
      disconnectedCount++;
  }

      processedCount++;
    }
  } else {
    while (true) {
      bool shouldProcessAJob = false;
      mpi.receive(shouldProcessAJob, MAIN_PROCESS);
      std::cout << "Process " << mpi.rank() << " received job: " << shouldProcessAJob << std::endl;
      if (shouldProcessAJob) {
        JobData jobData;
        receiveJobData(jobData, MAIN_PROCESS, mpi);
        std::cout << "Process " << mpi.rank() << " received job: " << jobData.path << std::endl;
        processJob(jobData);
        mpi.send(1, MAIN_PROCESS);
      } else {
        mpi.send(1, MAIN_PROCESS);
        break;
      }
    }
  }
}
#endif
