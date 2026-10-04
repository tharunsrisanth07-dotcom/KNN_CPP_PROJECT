#pragma once
#include "DataSet.h"
#include "ModelConfig.h"
#include "ModelResult.h"

// Problem: Evaluates a model configuration using K-Fold Cross Validation
// Methods: evaluate(...)
// Used by: ModelSelector
class CrossValidator {
public:
    ModelResult evaluate(const DataSet& data, const ModelConfig& config, int folds = 5) const;
};
