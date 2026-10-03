#pragma once
#include "DataPoint.h"
#include <vector>

using namespace std;

class DataSet {
private:
    vector<DataPoint> points;

public:
    void addPoint(DataPoint point);
    DataPoint getPoint(int index);
    int size();
    vector<DataPoint> getPoints();
    
    void shuffle();
    void splitTrainTest(double trainRatio, DataSet& trainSet, DataSet& testSet);
};
