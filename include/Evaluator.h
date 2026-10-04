#pragma once
#include <vector>
#include <string>
#include <map>

class Evaluator {
public:
    double calculateAccuracy(std::vector<std::string> actual, std::vector<std::string> predicted);
    void printConfusionMatrix(std::vector<std::string> actual, std::vector<std::string> predicted);
    void printPrecision(std::vector<std::string> actual, std::vector<std::string> predicted);
    void printRecall(std::vector<std::string> actual, std::vector<std::string> predicted);
    void printF1Score(std::vector<std::string> actual, std::vector<std::string> predicted);
};
