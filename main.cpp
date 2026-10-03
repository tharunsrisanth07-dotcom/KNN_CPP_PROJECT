#include <iostream>
#include <string>
#include "CSVLoader.h"
#include "DataSet.h"
#include "KNNClassifier.h"
#include "Evaluator.h"

using namespace std;

int main() {
    cout << "====================================\n";
    cout << "        KNN CLASSIFIER PROJECT      \n";
    cout << "====================================\n";

    CSVLoader loader;
    DataSet dataset = loader.load("data/iris.csv");

    if (dataset.size() == 0) {
        cout << "Error: Could not load dataset.\n";
        return 1;
    }

    cout << "Dataset loaded: " << dataset.size() << " samples.\n";
    cout << "Number of features: " << dataset.getPoint(1).getFeatures().size() << "\n";

    dataset.shuffle();

    DataSet trainSet;
    DataSet testSet;
    dataset.splitTrainTest(0.80, trainSet, testSet);

    cout << "Training Set: " << trainSet.size() << " samples\n";
    cout << "Testing Set:  " << testSet.size() << " samples\n";

    int kValue = 5;
    cout << "\nTraining KNN with K = " << kValue << "...\n";

    KNNClassifier knn(kValue);
    knn.fit(trainSet);

    Evaluator eval;
    double accuracy = eval.calculateAccuracy(testSet, knn);

    cout << "\n====================================\n";
    cout << "RESULTS\n";
    cout << "====================================\n";
    cout << "Accuracy: " << (accuracy * 100.0) << "%\n";
    cout << "====================================\n";

    return 0;
}
