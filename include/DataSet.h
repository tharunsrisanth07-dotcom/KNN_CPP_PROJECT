#pragma once
#include "DataPoint.h"
#include <vector>

class DataSet {
private:
    std::vector<DataPoint> points;

public:
    void addPoint(DataPoint p);
    DataPoint getPoint(int index);
    int size();
    std::vector<DataPoint> getPoints();
    void shuffle(int seed = 42);
    void splitTrainTest(DataSet& trainSet, DataSet& testSet, double trainRatio = 0.8);
};
