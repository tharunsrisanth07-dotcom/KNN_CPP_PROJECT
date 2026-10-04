#include "DataSet.h"
#include <algorithm>
#include <random>
using namespace std;

void DataSet::addPoint(DataPoint p) {
    points.push_back(p);
}

DataPoint DataSet::getPoint(int index) {
    return points[index];
}

int DataSet::size() {
    return points.size();
}

vector<DataPoint> DataSet::getPoints() {
    return points;
}

void DataSet::shuffle(int seed) {
    mt19937 g(seed);
    std::shuffle(points.begin(), points.end(), g);
}

void DataSet::splitTrainTest(DataSet& trainSet, DataSet& testSet, double trainRatio) {
    int trainSize = points.size() * trainRatio;
    for (int i = 0; i < points.size(); i++) {
        if (i < trainSize) {
            trainSet.addPoint(points[i]);
        } else {
            testSet.addPoint(points[i]);
        }
    }
}
