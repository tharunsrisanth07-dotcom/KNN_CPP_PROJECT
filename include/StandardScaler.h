#pragma once
#include "IScaler.h"
#include <vector>

// Problem: Standardizes features to mean 0 and standard deviation 1
// Data Members: mean and stdDev for each feature
// Used by: CrossValidator
class StandardScaler : public IScaler {
private:
    std::vector<double> mean;
    std::vector<double> stdDev;

public:
    void fit(const DataSet& data) override;
    DataPoint transform(const DataPoint& point) const override;
};
