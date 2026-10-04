#pragma once
#include <vector>
#include <string>

using namespace std;

class DataPoint {
private:
    vector<double> features;
    string label;

public:
    DataPoint(vector<double> f, string l);
    
    vector<double> getFeatures();
    string getLabel();
    double distanceTo(DataPoint other);
};
