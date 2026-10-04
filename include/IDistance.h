#pragma once
#include "DataPoint.h"

// Problem: Abstract base class to define a common interface for distance calculations
// Methods: calculate(point a, point b)
// Used by: KNNClassifier, EuclideanDistance, ManhattanDistance, MinkowskiDistance
class IDistance {
public:
    virtual double calculate(const DataPoint& a, const DataPoint& b) const = 0;
    virtual ~IDistance() {}
};
