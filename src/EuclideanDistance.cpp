#include "EuclideanDistance.h"
#include <cmath>
using namespace std;

double EuclideanDistance::calculate(DataPoint a, DataPoint b) {
    double sum = 0.0;
    vector<double> f1 = a.getFeatures();
    vector<double> f2 = b.getFeatures();
    for (int i = 0; i < f1.size(); i++) {
        double diff = f1[i] - f2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}
