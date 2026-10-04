#include "DataPoint.h"

DataPoint::DataPoint(const std::vector<double>& f, const std::string& l) : features(f), label(l) {}

const std::vector<double>& DataPoint::getFeatures() const {
    return features;
}

std::string DataPoint::getLabel() const {
    return label;
}
