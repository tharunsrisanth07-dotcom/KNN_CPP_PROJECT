#include "DataPoint.h"
#include <cmath>

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

double DataPoint::distanceTo(DataPoint other) {
    double sum = 0.0;
    vector<double> otherF = other.getFeatures();
    for (int i = 0; i < features.size(); i++) {
        double diff = features[i] - otherF[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}
