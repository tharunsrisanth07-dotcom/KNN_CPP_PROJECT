#pragma once
#include "DataPoint.h"
#include <vector>

// Problem: Manages a collection of DataPoints
// Data Members: a vector of DataPoints
// Methods: add point, get points, shuffle, split train/test
// Used by: CSVLoader, CrossValidator, KNNClassifier
class DataSet {
private:
    std::vector<DataPoint> points;

public:
    void addPoint(const DataPoint& p);
    const DataPoint& getPoint(size_t index) const;
    size_t size() const;
    const std::vector<DataPoint>& getPoints() const;
    void shuffle(int seed = 42);
    void splitTrainTest(DataSet& trainSet, DataSet& testSet, double trainRatio = 0.8) const;
};
