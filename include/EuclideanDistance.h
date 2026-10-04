#pragma once
#include "IDistance.h"

// Problem: Calculates the Euclidean distance between two DataPoints
// Inherits from: IDistance
// Used by: KNNClassifier (when configured for Euclidean)
class EuclideanDistance : public IDistance {
public:
    double calculate(const DataPoint& a, const DataPoint& b) const override;
};
