#pragma once
#include "IDistance.h"

class ManhattanDistance : public IDistance {
public:
    double calculate(DataPoint a, DataPoint b) override;
};
