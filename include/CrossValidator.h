#pragma once
#include "DataSet.h"
#include "ModelConfig.h"
#include "ModelResult.h"

class CrossValidator {
public:
    ModelResult evaluate(DataSet data, ModelConfig config, int folds = 5);
};
