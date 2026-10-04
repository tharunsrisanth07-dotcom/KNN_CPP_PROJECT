#include "PredictionService.h"
#include "StandardScaler.h"
#include "MinMaxScaler.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include "MinkowskiDistance.h"
#include <iostream>
using namespace std;

PredictionService::PredictionService() {
    finalScaler = nullptr;
    finalDistance = nullptr;
    finalKNN = nullptr;
    isTrained = false;
}

PredictionService::~PredictionService() {
    if (finalScaler != nullptr) delete finalScaler;
    if (finalDistance != nullptr) delete finalDistance;
    if (finalKNN != nullptr) delete finalKNN;
}

void PredictionService::trainFinalModel(DataSet allData, ModelConfig bestConfig) {
    config = bestConfig;

    if (finalScaler != nullptr) { delete finalScaler; finalScaler = nullptr; }
    if (finalDistance != nullptr) { delete finalDistance; finalDistance = nullptr; }
    if (finalKNN != nullptr) { delete finalKNN; finalKNN = nullptr; }

    DataSet trainingData = allData;

    if (config.scalerType == "standard") {
        finalScaler = new StandardScaler();
    } else if (config.scalerType == "minmax") {
        finalScaler = new MinMaxScaler();
    }

    if (finalScaler != nullptr) {
        finalScaler->fit(trainingData);
        DataSet scaledTrain;
        for (int i = 0; i < trainingData.size(); i++) {
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

    cout << "Model trained on all " << allData.size() << " data points. Ready to predict!\n";
}

string PredictionService::predictNewPoint(DataPoint point) {
    DataPoint processPoint = point;
    if (finalScaler != nullptr) {
        processPoint = finalScaler->transform(point);
    }
    return finalKNN->predict(processPoint);
}

bool PredictionService::getIsTrained() {
    return isTrained;
}

ModelConfig PredictionService::getConfig() {
    return config;
}
