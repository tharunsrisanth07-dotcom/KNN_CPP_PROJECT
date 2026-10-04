#include "StandardScaler.h"
#include <cmath>

void StandardScaler::fit(const DataSet& data) {
    mean.clear();
    stdDev.clear();
    
    if (data.size() == 0) return;
    
    size_t numFeatures = data.getPoint(0).getFeatures().size();
    mean.resize(numFeatures, 0.0);
    stdDev.resize(numFeatures, 0.0);
    
    // Calculate Mean
    for (size_t i = 0; i < data.size(); ++i) {
        const auto& features = data.getPoint(i).getFeatures();
        for (size_t j = 0; j < numFeatures; ++j) {
            mean[j] += features[j];
        }
    }
    for (size_t j = 0; j < numFeatures; ++j) {
        mean[j] /= data.size();
    }
    
    // Calculate Standard Deviation
    for (size_t i = 0; i < data.size(); ++i) {
        const auto& features = data.getPoint(i).getFeatures();
        for (size_t j = 0; j < numFeatures; ++j) {
            double diff = features[j] - mean[j];
            stdDev[j] += diff * diff;
        }
    }
    for (size_t j = 0; j < numFeatures; ++j) {
        stdDev[j] = std::sqrt(stdDev[j] / data.size());
    }
}

DataPoint StandardScaler::transform(const DataPoint& point) const {
    const auto& features = point.getFeatures();
    std::vector<double> scaledFeatures(features.size());
    
    for (size_t j = 0; j < features.size(); ++j) {
        if (j < mean.size() && j < stdDev.size() && stdDev[j] != 0.0) {
            scaledFeatures[j] = (features[j] - mean[j]) / stdDev[j];
        } else {
            scaledFeatures[j] = features[j]; // Avoid division by zero
        }
    }
    
    return DataPoint(scaledFeatures, point.getLabel());
}
