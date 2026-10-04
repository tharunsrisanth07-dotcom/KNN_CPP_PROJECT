#pragma once
#include "IScaler.h"
#include <vector>

// Problem: Scales features to the range [0, 1]
// Data Members: minValues and maxValues for each feature
// Used by: CrossValidator
class MinMaxScaler : public IScaler {
private:
    std::vector<double> minValues;
    std::vector<double> maxValues;

public:
    void fit(const DataSet& data) override;
    DataPoint transform(const DataPoint& point) const override;
};
