#include "Evaluator.h"
#include <iostream>
#include <iomanip>
#include <set>
using namespace std;

double Evaluator::calculateAccuracy(vector<string> actual, vector<string> predicted) {
    int correct = 0;
    for (int i = 0; i < actual.size(); i++) {
        if (actual[i] == predicted[i]) {
            correct++;
        }
    }
    return (double)correct / actual.size();
}

void Evaluator::printConfusionMatrix(vector<string> actual, vector<string> predicted) {
    set<string> classes;
    for (string l : actual) classes.insert(l);
    for (string l : predicted) classes.insert(l);

    map<string, map<string, int>> matrix;
    for (int i = 0; i < actual.size(); i++) {
        matrix[actual[i]][predicted[i]]++;
    }

    cout << "\nConfusion Matrix (Rows = Actual, Cols = Predicted):\n";
    cout << setw(15) << "";
    for (string c : classes) {
        cout << setw(15) << c;
    }
    cout << "\n";

    for (string actualClass : classes) {
        cout << setw(15) << actualClass;
        for (string predictedClass : classes) {
            cout << setw(15) << matrix[actualClass][predictedClass];
        }
        cout << "\n";
    }
    cout << "\n";
}

void Evaluator::printPrecision(vector<string> actual, vector<string> predicted) {
    set<string> classes;
    for (string l : actual) classes.insert(l);

    cout << "\nPrecision per class:\n";
    for (string cls : classes) {
        int tp = 0, fp = 0;
        for (int i = 0; i < actual.size(); i++) {
            if (predicted[i] == cls && actual[i] == cls) tp++;
            if (predicted[i] == cls && actual[i] != cls) fp++;
        }
        double precision = (tp + fp == 0) ? 0.0 : (double)tp / (tp + fp);
        cout << "  " << cls << ": " << fixed << setprecision(2) << (precision * 100.0) << "%\n";
    }
}

void Evaluator::printRecall(vector<string> actual, vector<string> predicted) {
    set<string> classes;
    for (string l : actual) classes.insert(l);

    cout << "\nRecall per class:\n";
    for (string cls : classes) {
        int tp = 0, fn = 0;
        for (int i = 0; i < actual.size(); i++) {
            if (actual[i] == cls && predicted[i] == cls) tp++;
            if (actual[i] == cls && predicted[i] != cls) fn++;
        }
        double recall = (tp + fn == 0) ? 0.0 : (double)tp / (tp + fn);
        cout << "  " << cls << ": " << fixed << setprecision(2) << (recall * 100.0) << "%\n";
    }
}

void Evaluator::printF1Score(vector<string> actual, vector<string> predicted) {
    set<string> classes;
    for (string l : actual) classes.insert(l);

    cout << "\nF1 Score per class:\n";
    for (string cls : classes) {
        int tp = 0, fp = 0, fn = 0;
        for (int i = 0; i < actual.size(); i++) {
            if (predicted[i] == cls && actual[i] == cls) tp++;
            if (predicted[i] == cls && actual[i] != cls) fp++;
            if (actual[i] == cls && predicted[i] != cls) fn++;
        }
        double precision = (tp + fp == 0) ? 0.0 : (double)tp / (tp + fp);
        double recall = (tp + fn == 0) ? 0.0 : (double)tp / (tp + fn);
        double f1 = (precision + recall == 0.0) ? 0.0 : 2.0 * (precision * recall) / (precision + recall);
        cout << "  " << cls << ": " << fixed << setprecision(2) << (f1 * 100.0) << "%\n";
    }
}
