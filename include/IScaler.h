#pragma once
#include "DataSet.h"
#include "DataPoint.h"

class IScaler {
public:
    virtual void fit(DataSet data) = 0;
    virtual DataPoint transform(DataPoint point) = 0;
    virtual ~IScaler() {}
};
