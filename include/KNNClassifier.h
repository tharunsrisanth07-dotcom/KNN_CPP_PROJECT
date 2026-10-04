#pragma once
#include "DataSet.h"
#include "IDistance.h"
#include <string>

// Problem: Implements the K-Nearest Neighbors logic
// Data Members: k, distanceMetric, weighted flag, training data
// Methods: fit(dataset), predict(datapoint)
// Used by: CrossValidator, PredictionService
class KNNClassifier {
private:
    int k;
    IDistance* distanceMetric;
    bool weighted;
    DataSet trainingData;

public:
    KNNClassifier(int k, IDistance* distanceMetric, bool weighted = false);
    void fit(const DataSet& data);
    std::string predict(const DataPoint& point) const;
};
