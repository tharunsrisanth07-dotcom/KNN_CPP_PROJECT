#pragma once
#include "ModelConfig.h"
#include "DataSet.h"
#include "KNNClassifier.h"
#include "IScaler.h"

// Problem: Trains final model and makes predictions on new user input
// Used by: main.cpp
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
    void trainFinalModel(const DataSet& allData, const ModelConfig& bestConfig);
    std::string predictNewPoint(const DataPoint& point) const;
    bool getIsTrained() const;
    ModelConfig getConfig() const;
};
