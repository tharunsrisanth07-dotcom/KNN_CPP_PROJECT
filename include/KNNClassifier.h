#pragma once
#include "DataSet.h"
#include "IDistance.h"
#include <string>
#include <vector>

class KNNClassifier {
private:
    int k;
    IDistance* distanceMetric;
    bool weighted;
    DataSet trainingData;

public:
    KNNClassifier(int k, IDistance* distanceMetric, bool weighted = false);
    void fit(DataSet data);
    std::string predict(DataPoint point);
};
