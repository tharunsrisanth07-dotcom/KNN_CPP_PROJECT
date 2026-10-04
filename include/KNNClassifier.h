#pragma once
#include "DataSet.h"
#include "IDistance.h"
#include <string>
#include <memory>

using namespace std;

class KNNClassifier {
private:
    int k;
    unique_ptr<IDistance> metric;
    DataSet trainingData;

public:
    KNNClassifier(int kValue);
    
    void setDistanceType(string type);
    void setK(int kValue);
    void fit(DataSet data);
    string predict(DataPoint point);
};
