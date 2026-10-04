#pragma once
#include <vector>
#include <string>

class DataPoint {
private:
    std::vector<double> features;
    std::string label;

public:
    DataPoint() {}
    DataPoint(std::vector<double> f, std::string l);
    std::vector<double> getFeatures();
    std::string getLabel();
};
