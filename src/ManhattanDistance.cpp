#include "ManhattanDistance.h"
#include <cmath>
#include <vector>

using namespace std;

double ManhattanDistance::calculate(DataPoint a, DataPoint b) {
    vector<double> f1 = a.getFeatures();
    vector<double> f2 = b.getFeatures();
    double sum = 0.0;
    for(int i = 0; i < f1.size(); i++) {
        double diff = f1[i] - f2[i];
        sum += abs(diff);
    }
    return sum;
}
