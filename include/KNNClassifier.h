#pragma once
#include "DataSet.h"
#include <string>

using namespace std;

class KNNClassifier {
private:
    int k;
    string distanceType;
    DataSet trainingData;
    
    double calculateDistance(DataPoint a, DataPoint b);

public:
    KNNClassifier(int kValue);
    
    void setDistanceType(string type);
    void setK(int kValue);
    void fit(DataSet data);
    string predict(DataPoint point);
};
