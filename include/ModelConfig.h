#pragma once
#include <string>

// Problem: Stores one set of hyperparameters for KNN
// Used by: CrossValidator, ModelSelector, PredictionService
struct ModelConfig {
    int k;
    std::string distanceType;
    std::string scalerType;
    bool weighted;
};
