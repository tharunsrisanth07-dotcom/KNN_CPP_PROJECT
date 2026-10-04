#include "MinMaxScaler.h"
using namespace std;

void MinMaxScaler::fit(DataSet data) {
    minValues.clear();
    maxValues.clear();

    int n = data.size();
    int numFeatures = data.getPoint(0).getFeatures().size();

    minValues.resize(numFeatures, 1e18);
    maxValues.resize(numFeatures, -1e18);

    for (int i = 0; i < n; i++) {
        vector<double> features = data.getPoint(i).getFeatures();
        for (int j = 0; j < numFeatures; j++) {
            if (features[j] < minValues[j]) minValues[j] = features[j];
            if (features[j] > maxValues[j]) maxValues[j] = features[j];
        }
    }
}

DataPoint MinMaxScaler::transform(DataPoint point) {
    vector<double> features = point.getFeatures();
    vector<double> scaled(features.size());
    for (int j = 0; j < features.size(); j++) {
        double range = maxValues[j] - minValues[j];
        if (range != 0.0) {
            scaled[j] = (features[j] - minValues[j]) / range;
        } else {
            scaled[j] = 0.0;
        }
    }
    return DataPoint(scaled, point.getLabel());
}
