#include "ManhattanDistance.h"
#include <cmath>
#include <algorithm>

double ManhattanDistance::calculate(const DataPoint& a, const DataPoint& b) const {
    double sum = 0.0;
    const auto& f1 = a.getFeatures();
    const auto& f2 = b.getFeatures();
    
    size_t minSize = std::min(f1.size(), f2.size());
    for (size_t i = 0; i < minSize; ++i) {
        sum += std::abs(f1[i] - f2[i]);
    }
    
    return sum;
}
