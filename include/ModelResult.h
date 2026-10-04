#pragma once
#include "ModelConfig.h"
#include <vector>

struct ModelResult {
    ModelConfig config;
    std::vector<double> foldAccuracies;
    double averageAccuracy;
};
