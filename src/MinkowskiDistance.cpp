#include "MinkowskiDistance.h"
#include <cmath>
using namespace std;

MinkowskiDistance::MinkowskiDistance(double p) {
    this->p = p;
}

double MinkowskiDistance::calculate(DataPoint a, DataPoint b) {
    double sum = 0.0;
    vector<double> f1 = a.getFeatures();
    vector<double> f2 = b.getFeatures();
    for (int i = 0; i < f1.size(); i++) {
        sum += pow(abs(f1[i] - f2[i]), p);
    }
    return pow(sum, 1.0 / p);
}
