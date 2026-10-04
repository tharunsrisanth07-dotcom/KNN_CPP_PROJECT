#pragma once
#include "IDistance.h"

// Problem: Calculates the Manhattan distance between two DataPoints
// Inherits from: IDistance
// Used by: KNNClassifier (when configured for Manhattan)
class ManhattanDistance : public IDistance {
public:
    double calculate(const DataPoint& a, const DataPoint& b) const override;
};
