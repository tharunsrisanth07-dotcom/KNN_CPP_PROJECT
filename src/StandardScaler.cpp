#include "StandardScaler.h"
#include <cmath>
using namespace std;

void StandardScaler::fit(DataSet data) {
    mean.clear();
    stdDev.clear();

    int n = data.size();
    int numFeatures = data.getPoint(0).getFeatures().size();

    mean.resize(numFeatures, 0.0);
    stdDev.resize(numFeatures, 0.0);

    for (int i = 0; i < n; i++) {
        vector<double> features = data.getPoint(i).getFeatures();
        for (int j = 0; j < numFeatures; j++) {
            mean[j] += features[j];
        }
    }
    for (int j = 0; j < numFeatures; j++) {
        mean[j] /= n;
    }

    for (int i = 0; i < n; i++) {
        vector<double> features = data.getPoint(i).getFeatures();
        for (int j = 0; j < numFeatures; j++) {
            double diff = features[j] - mean[j];
            stdDev[j] += diff * diff;
        }
    }
    for (int j = 0; j < numFeatures; j++) {
        stdDev[j] = sqrt(stdDev[j] / n);
    }
}

DataPoint StandardScaler::transform(DataPoint point) {
    vector<double> features = point.getFeatures();
    vector<double> scaled(features.size());
    for (int j = 0; j < features.size(); j++) {
        if (stdDev[j] != 0.0) {
            scaled[j] = (features[j] - mean[j]) / stdDev[j];
        } else {
            scaled[j] = features[j];
        }
    }
    return DataPoint(scaled, point.getLabel());
}
