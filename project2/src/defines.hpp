// Copyright Aaron Santana Valdelomar - Univerdidad de Costa Rica 2024
#pragma once
#include <string>

#define magnitude_t double
#define G_CONST 6.67430e-11

struct JobData {
    magnitude_t delta_time;
    magnitude_t final_time;
    std::string path;
    std::string directory;
};
