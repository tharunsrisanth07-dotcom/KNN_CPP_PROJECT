#include "MinMaxScaler.h"
#include <limits>

void MinMaxScaler::fit(const DataSet& data) {
    minValues.clear();
    maxValues.clear();
    
    if (data.size() == 0) return;
    
    size_t numFeatures = data.getPoint(0).getFeatures().size();
    minValues.resize(numFeatures, std::numeric_limits<double>::max());
    maxValues.resize(numFeatures, std::numeric_limits<double>::lowest());
    
    for (size_t i = 0; i < data.size(); ++i) {
        const auto& features = data.getPoint(i).getFeatures();
        for (size_t j = 0; j < numFeatures; ++j) {
            if (features[j] < minValues[j]) minValues[j] = features[j];
            if (features[j] > maxValues[j]) maxValues[j] = features[j];
        }
    }
}

DataPoint MinMaxScaler::transform(const DataPoint& point) const {
    const auto& features = point.getFeatures();
    std::vector<double> scaledFeatures(features.size());
    
    for (size_t j = 0; j < features.size(); ++j) {
        if (j < minValues.size() && j < maxValues.size() && (maxValues[j] - minValues[j]) != 0.0) {
            scaledFeatures[j] = (features[j] - minValues[j]) / (maxValues[j] - minValues[j]);
        } else {
            scaledFeatures[j] = 0.0;
        }
    }
    
    return DataPoint(scaledFeatures, point.getLabel());
}
