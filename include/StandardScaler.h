#pragma once
#include "IScaler.h"
#include <vector>

class StandardScaler : public IScaler {
private:
    std::vector<double> mean;
    std::vector<double> stdDev;

public:
    void fit(DataSet data) override;
    DataPoint transform(DataPoint point) override;
};
