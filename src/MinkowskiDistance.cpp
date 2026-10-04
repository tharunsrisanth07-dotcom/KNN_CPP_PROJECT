#include "MinkowskiDistance.h"
#include <cmath>
#include <algorithm>

MinkowskiDistance::MinkowskiDistance(double p) : p(p) {}

double MinkowskiDistance::calculate(const DataPoint& a, const DataPoint& b) const {
    double sum = 0.0;
    const auto& f1 = a.getFeatures();
    const auto& f2 = b.getFeatures();
    
    size_t minSize = std::min(f1.size(), f2.size());
    for (size_t i = 0; i < minSize; ++i) {
        sum += std::pow(std::abs(f1[i] - f2[i]), p);
    }
    
    return std::pow(sum, 1.0 / p);
}
