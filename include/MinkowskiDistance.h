#pragma once
#include "IDistance.h"

class MinkowskiDistance : public IDistance {
private:
    double p;

public:
    MinkowskiDistance(double p);
    double calculate(DataPoint a, DataPoint b) override;
};
