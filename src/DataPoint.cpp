#include "DataPoint.h"
#include <vector>
#include <string>
using namespace std;

DataPoint::DataPoint(vector<double> f, string l) {
    features = f;
    label = l;
}

vector<double> DataPoint::getFeatures() {
    return features;
}

string DataPoint::getLabel() {
    return label;
}
