#pragma once
#include <vector>
#include <string>
#include <map>

// Problem: Measures performance of predictions
// Methods: calculateAccuracy, printConfusionMatrix
// Used by: CrossValidator, main
class Evaluator {
public:
    double calculateAccuracy(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const;
    void printConfusionMatrix(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const;
};
