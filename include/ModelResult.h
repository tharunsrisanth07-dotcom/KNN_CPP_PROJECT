#pragma once
#include "ModelConfig.h"
#include <vector>

// Problem: Stores the CV evaluation results for a specific configuration
// Used by: ModelSelector
struct ModelResult {
    ModelConfig config;
    std::vector<double> foldAccuracies;
    double averageAccuracy;
};
