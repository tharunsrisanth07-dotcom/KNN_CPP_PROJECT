#include "DataSet.h"
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

void DataSet::addPoint(DataPoint point) {
    points.push_back(point);
}

DataPoint DataSet::getPoint(int index) {
    if (index < 1 || index > points.size()) {
        throw out_of_range("Invalid index");
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

void DataSet::loadCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    
    string line;
    getline(file, line); 
    
    while(getline(file, line)) {
        if(line == "") continue;
        
        stringstream ss(line);
        string f1, f2, f3, f4, label;
        
        getline(ss, f1, ',');
        getline(ss, f2, ',');
        getline(ss, f3, ',');
        getline(ss, f4, ',');
        getline(ss, label, ',');
        
        vector<double> features;
        features.push_back(stod(f1));
        features.push_back(stod(f2));
        features.push_back(stod(f3));
        features.push_back(stod(f4));
        
        DataPoint pt(features, label);
        points.push_back(pt);
    }
    
    file.close();
}
