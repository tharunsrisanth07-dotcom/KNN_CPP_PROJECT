#pragma once
#include "DataSet.h"
#include "ModelConfig.h"

// Problem: Tries multiple configurations to find the best one
// Used by: main.cpp
class ModelSelector {
public:
    ModelConfig findBestModel(const DataSet& data);
};
