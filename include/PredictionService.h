#pragma once
#include "ModelConfig.h"
#include "DataSet.h"
#include "KNNClassifier.h"
#include "IScaler.h"

class PredictionService {
private:
    ModelConfig config;
    IScaler* finalScaler;
    IDistance* finalDistance;
    KNNClassifier* finalKNN;
    bool isTrained;

public:
    PredictionService();
    ~PredictionService();
    void trainFinalModel(DataSet allData, ModelConfig bestConfig);
    std::string predictNewPoint(DataPoint point);
    bool getIsTrained();
    ModelConfig getConfig();
};
