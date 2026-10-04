#pragma once
#include "DataSet.h"
#include <string>

class CSVLoader {
public:
    DataSet load(std::string filename);
};
