#include "DataSet.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

void DataSet::addPoint(DataPoint point) {
    points.push_back(point);
}

DataPoint DataSet::getPoint(int index) {
    if (index < 1 || index > points.size()) {
        throw out_of_range("Error: DataPoint index out of bounds.");
    }
    return points[index - 1];
}

int DataSet::size() {
    return points.size();
}

vector<DataPoint> DataSet::getPoints() {
    return points;
}

void DataSet::shuffle() {
    for(int i = 0; i < points.size(); i++) {
        int swapIndex = rand() % points.size();
        DataPoint temp = points[i];
        points[i] = points[swapIndex];
        points[swapIndex] = temp;
    }
}

void DataSet::splitTrainTest(double trainRatio, DataSet& trainSet, DataSet& testSet) {
    int trainSize = points.size() * trainRatio;
    for(int i = 0; i < points.size(); i++) {
        if(i < trainSize) {
            trainSet.addPoint(points[i]);
        } else {
            testSet.addPoint(points[i]);
        }
    }
}
