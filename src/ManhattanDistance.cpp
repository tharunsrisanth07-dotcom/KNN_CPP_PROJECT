#include "ManhattanDistance.h"
#include <cmath>
using namespace std;

double ManhattanDistance::calculate(DataPoint a, DataPoint b) {
    double sum = 0.0;
    vector<double> f1 = a.getFeatures();
    vector<double> f2 = b.getFeatures();
    for (int i = 0; i < f1.size(); i++) {
        sum += abs(f1[i] - f2[i]);
    }
    return sum;
}
