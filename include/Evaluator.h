#pragma once
#include "DataSet.h"
#include "KNNClassifier.h"

using namespace std;

class Evaluator {
public:
    double calculateAccuracy(DataSet testData, KNNClassifier classifier);
};
