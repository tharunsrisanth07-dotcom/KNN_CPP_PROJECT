#include "Evaluator.h"
#include <iostream>
#include <iomanip>
#include <set>

double Evaluator::calculateAccuracy(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const {
    if (actual.empty() || actual.size() != predicted.size()) return 0.0;
    
    int correct = 0;
    for (size_t i = 0; i < actual.size(); ++i) {
        if (actual[i] == predicted[i]) {
            correct++;
        }
    }
    
    return static_cast<double>(correct) / actual.size();
}

void Evaluator::printConfusionMatrix(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const {
    if (actual.empty() || actual.size() != predicted.size()) return;

    std::set<std::string> classes;
    for (const auto& l : actual) classes.insert(l);
    for (const auto& l : predicted) classes.insert(l);

    std::map<std::string, std::map<std::string, int>> matrix;
    for (size_t i = 0; i < actual.size(); ++i) {
        matrix[actual[i]][predicted[i]]++;
    }

    std::cout << "\nConfusion Matrix (Rows: Actual, Cols: Predicted):\n";
    std::cout << std::setw(15) << "";
    for (const auto& c : classes) {
        std::cout << std::setw(15) << c;
    }
    std::cout << "\n";

    for (const auto& actualClass : classes) {
        std::cout << std::setw(15) << actualClass;
        for (const auto& predictedClass : classes) {
            std::cout << std::setw(15) << matrix[actualClass][predictedClass];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Precision = TP / (TP + FP)
// TP: we predicted this class AND it was correct
// FP: we predicted this class BUT it was wrong
void Evaluator::printPrecision(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const {
    if (actual.empty() || actual.size() != predicted.size()) return;

    std::set<std::string> classes;
    for (const auto& l : actual) classes.insert(l);

    std::cout << "\nPrecision per class:\n";
    for (const std::string& cls : classes) {
        int tp = 0, fp = 0;
        for (size_t i = 0; i < actual.size(); ++i) {
            if (predicted[i] == cls && actual[i] == cls)  tp++;  // correctly predicted as this class
            if (predicted[i] == cls && actual[i] != cls)  fp++;  // wrongly predicted as this class
        }
        double precision = (tp + fp == 0) ? 0.0 : static_cast<double>(tp) / (tp + fp);
        std::cout << "  " << cls << ": " << std::fixed << std::setprecision(2) << (precision * 100.0) << "%\n";
    }
}

// Recall = TP / (TP + FN)
// TP: we predicted this class AND it was correct
// FN: the actual class was this class BUT we predicted something else
void Evaluator::printRecall(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const {
    if (actual.empty() || actual.size() != predicted.size()) return;

    std::set<std::string> classes;
    for (const auto& l : actual) classes.insert(l);

    std::cout << "\nRecall per class:\n";
    for (const std::string& cls : classes) {
        int tp = 0, fn = 0;
        for (size_t i = 0; i < actual.size(); ++i) {
            if (actual[i] == cls && predicted[i] == cls)  tp++;  // correctly predicted
            if (actual[i] == cls && predicted[i] != cls)  fn++;  // missed this class
        }
        double recall = (tp + fn == 0) ? 0.0 : static_cast<double>(tp) / (tp + fn);
        std::cout << "  " << cls << ": " << std::fixed << std::setprecision(2) << (recall * 100.0) << "%\n";
    }
}

// F1 Score = 2 * (Precision * Recall) / (Precision + Recall)
void Evaluator::printF1Score(const std::vector<std::string>& actual, const std::vector<std::string>& predicted) const {
    if (actual.empty() || actual.size() != predicted.size()) return;

    std::set<std::string> classes;
    for (const auto& l : actual) classes.insert(l);

    std::cout << "\nF1 Score per class:\n";
    for (const std::string& cls : classes) {
        int tp = 0, fp = 0, fn = 0;
        for (size_t i = 0; i < actual.size(); ++i) {
            if (predicted[i] == cls && actual[i] == cls)  tp++;
            if (predicted[i] == cls && actual[i] != cls)  fp++;
            if (actual[i] == cls && predicted[i] != cls)  fn++;
        }
        double precision = (tp + fp == 0) ? 0.0 : static_cast<double>(tp) / (tp + fp);
        double recall    = (tp + fn == 0) ? 0.0 : static_cast<double>(tp) / (tp + fn);
        double f1 = (precision + recall == 0.0) ? 0.0 : 2.0 * (precision * recall) / (precision + recall);
        std::cout << "  " << cls << ": " << std::fixed << std::setprecision(2) << (f1 * 100.0) << "%\n";
    }
}
