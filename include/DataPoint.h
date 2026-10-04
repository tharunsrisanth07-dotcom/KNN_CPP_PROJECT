#pragma once
#include <vector>
#include <string>

// Problem: Represents a single row in our dataset
// Data Members: features (the numeric columns) and label (the target class)
// Methods: getters for features and label
// Used by: DataSet, KNNClassifier, etc.
class DataPoint {
private:
    std::vector<double> features;
    std::string label;

public:
    DataPoint(const std::vector<double>& f, const std::string& l);
    const std::vector<double>& getFeatures() const;
    std::string getLabel() const;
};
