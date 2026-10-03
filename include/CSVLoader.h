#pragma once
#include "DataSet.h"
#include <string>

using namespace std;

class CSVLoader {
public:
    DataSet load(string filename);
};
