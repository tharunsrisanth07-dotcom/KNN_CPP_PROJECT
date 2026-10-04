#pragma once
#include <string>

struct ModelConfig {
    int k;
    std::string distanceType;
    std::string scalerType;
    bool weighted;
};
