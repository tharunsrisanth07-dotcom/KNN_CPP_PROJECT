#pragma once
#include "IDistance.h"

class EuclideanDistance : public IDistance {
public:
    double calculate(DataPoint a, DataPoint b) override;
};
