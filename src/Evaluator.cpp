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
