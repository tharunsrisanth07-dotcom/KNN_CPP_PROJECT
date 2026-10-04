#include "DataSet.h"
#include <algorithm>
#include <random>

void DataSet::addPoint(const DataPoint& p) {
    points.push_back(p);
}

const DataPoint& DataSet::getPoint(size_t index) const {
    return points[index];
}

size_t DataSet::size() const {
    return points.size();
}

const std::vector<DataPoint>& DataSet::getPoints() const {
    return points;
}

void DataSet::shuffle(int seed) {
    std::mt19937 g(seed);
    std::shuffle(points.begin(), points.end(), g);
}

void DataSet::splitTrainTest(DataSet& trainSet, DataSet& testSet, double trainRatio) const {
    size_t trainSize = static_cast<size_t>(points.size() * trainRatio);
    for (size_t i = 0; i < points.size(); ++i) {
        if (i < trainSize) {
            trainSet.addPoint(points[i]);
        } else {
            testSet.addPoint(points[i]);
        }
    }
}
