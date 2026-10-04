#pragma once
#include "IScaler.h"
#include <vector>

class MinMaxScaler : public IScaler {
private:
    std::vector<double> minValues;
    std::vector<double> maxValues;

public:
    void fit(DataSet data) override;
    DataPoint transform(DataPoint point) override;
};
