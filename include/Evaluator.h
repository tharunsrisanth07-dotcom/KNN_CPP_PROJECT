#pragma once
#include <vector>
#include <string>
#include <map>

// Problem: Measures performance of predictions
// Methods: calculateAccuracy, printConfusionMatrix, calculatePrecision, calculateRecall, calculateF1Score
// Used by: CrossValidator, main
class Evaluator {
public:
    double calculateAccuracy(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const;
    void printConfusionMatrix(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const;

    // For each class: Precision = TP / (TP + FP)
    void printPrecision(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const;

    // For each class: Recall = TP / (TP + FN)
    void printRecall(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const;

    // For each class: F1 = 2 * (Precision * Recall) / (Precision + Recall)
    void printF1Score(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const;
};
