#pragma once
#include "DataSet.h"
#include "DataPoint.h"

// Problem: Abstract interface for feature scaling
// Methods: fit(dataset), transform(datapoint)
// Used by: CrossValidator, PredictionService
class IScaler {
public:
    virtual void fit(const DataSet& data) = 0;
    virtual DataPoint transform(const DataPoint& point) const = 0;
    virtual ~IScaler() {}
};
