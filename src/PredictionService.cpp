#include "PredictionService.h"
#include "StandardScaler.h"
#include "MinMaxScaler.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include "MinkowskiDistance.h"
#include <iostream>

PredictionService::PredictionService() : finalScaler(nullptr), finalDistance(nullptr), finalKNN(nullptr), isTrained(false) {}

PredictionService::~PredictionService() {
    if (finalScaler) delete finalScaler;
    if (finalDistance) delete finalDistance;
    if (finalKNN) delete finalKNN;
}

void PredictionService::trainFinalModel(const DataSet& allData, const ModelConfig& bestConfig) {
    config = bestConfig;
    
    if (finalScaler) { delete finalScaler; finalScaler = nullptr; }
    if (finalDistance) { delete finalDistance; finalDistance = nullptr; }
    if (finalKNN) { delete finalKNN; finalKNN = nullptr; }

    DataSet trainingData = allData;

    if (config.scalerType == "standard") {
        finalScaler = new StandardScaler();
    } else if (config.scalerType == "minmax") {
        finalScaler = new MinMaxScaler();
    }

    if (finalScaler) {
        finalScaler->fit(trainingData);
        DataSet scaledTrain;
        for (size_t i = 0; i < trainingData.size(); ++i) {
            scaledTrain.addPoint(finalScaler->transform(trainingData.getPoint(i)));
        }
        trainingData = scaledTrain;
    }

    if (config.distanceType == "euclidean") finalDistance = new EuclideanDistance();
    else if (config.distanceType == "manhattan") finalDistance = new ManhattanDistance();
    else if (config.distanceType == "minkowski") finalDistance = new MinkowskiDistance(3.0);
    else finalDistance = new EuclideanDistance();

    finalKNN = new KNNClassifier(config.k, finalDistance, config.weighted);
    finalKNN->fit(trainingData);
    isTrained = true;
    
    std::cout << "Final model trained successfully on all " << allData.size() << " data points.\n";
}

std::string PredictionService::predictNewPoint(const DataPoint& point) const {
    if (!isTrained) return "Model not trained yet.";

    DataPoint processPoint = point;
    if (finalScaler) {
        processPoint = finalScaler->transform(point);
    }
    
    return finalKNN->predict(processPoint);
}

bool PredictionService::getIsTrained() const {
    return isTrained;
}

ModelConfig PredictionService::getConfig() const {
    return config;
}
