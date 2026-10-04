#pragma once
#include "DataSet.h"
#include "ModelConfig.h"

class ModelSelector {
public:
    ModelConfig findBestModel(DataSet data);
};
