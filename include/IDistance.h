#pragma once
#include "DataPoint.h"

class IDistance {
public:
    virtual double calculate(DataPoint a, DataPoint b) = 0;
    virtual ~IDistance() {}
};
