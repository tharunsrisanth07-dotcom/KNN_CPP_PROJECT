#pragma once
#include "DataSet.h"
#include <string>

// Problem: Reads a CSV file and creates a DataSet
// Methods: load(filename)
// Used by: main.cpp to load initial data
class CSVLoader {
public:
    DataSet load(const std::string& filename) const;
};
