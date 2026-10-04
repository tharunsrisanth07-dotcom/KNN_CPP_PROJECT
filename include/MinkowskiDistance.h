#pragma once
#include "IDistance.h"

// Problem: Calculates the generalized Minkowski distance between two DataPoints
// Inherits from: IDistance
// Used by: KNNClassifier (when configured for Minkowski)
class MinkowskiDistance : public IDistance {
private:
    double p;

public:
    MinkowskiDistance(double p);
    double calculate(const DataPoint& a, const DataPoint& b) const override;
};
