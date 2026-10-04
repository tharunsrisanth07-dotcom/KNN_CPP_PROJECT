#include "ModelSelector.h"
#include "CrossValidator.h"
#include "KNNClassifier.h"
#include "Evaluator.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include "MinkowskiDistance.h"
#include "StandardScaler.h"
#include "MinMaxScaler.h"
#include <iostream>
#include <iomanip>
using namespace std;

ModelConfig ModelSelector::findBestModel(DataSet data) {
    vector<int> ks = {3, 5, 7};
    vector<string> distances = {"euclidean", "manhattan", "minkowski"};
    vector<string> scalers = {"none", "standard", "minmax"};
    vector<bool> weights = {false, true};

    CrossValidator cv;
    ModelResult bestResult;
    bestResult.averageAccuracy = -1.0;

    cout << "Running 5-Fold Cross Validation... hang tight!\n\n";

    for (int k : ks) {
        for (string dist : distances) {
            for (string scaler : scalers) {
                for (bool w : weights) {
                    ModelConfig config = {k, dist, scaler, w};
                    ModelResult result = cv.evaluate(data, config, 5);

                    cout << "K=" << k << " | " << dist << " | " << scaler
                         << " | " << (w ? "Weighted" : "Normal")
                         << " | Avg Accuracy: " << fixed << setprecision(2)
                         << (result.averageAccuracy * 100.0) << "%\n";

                    if (result.averageAccuracy > bestResult.averageAccuracy) {
                        bestResult = result;
                    }
                }
            }
        }
    }

    cout << "\n====================================\n";
    cout << "  Best Config Found!\n";
    cout << "====================================\n";
    cout << "K           : " << bestResult.config.k << "\n";
    cout << "Distance    : " << bestResult.config.distanceType << "\n";
    cout << "Scaling     : " << bestResult.config.scalerType << "\n";
    cout << "Weighted    : " << (bestResult.config.weighted ? "Yes" : "No") << "\n";
    cout << "CV Accuracy : " << (bestResult.averageAccuracy * 100.0) << "%\n";
    cout << "====================================\n\n";

    cout << "Now running best config on an 80/20 train-test split to show full metrics:\n";

    DataSet shuffled = data;
    shuffled.shuffle(42);
    DataSet trainSet, testSet;
    shuffled.splitTrainTest(trainSet, testSet, 0.8);

    IScaler* scaler = nullptr;
    if (bestResult.config.scalerType == "standard") scaler = new StandardScaler();
    else if (bestResult.config.scalerType == "minmax") scaler = new MinMaxScaler();

    if (scaler != nullptr) {
        scaler->fit(trainSet);
        DataSet scaledTrain, scaledTest;
        for (int i = 0; i < trainSet.size(); i++)
            scaledTrain.addPoint(scaler->transform(trainSet.getPoint(i)));
        for (int i = 0; i < testSet.size(); i++)
            scaledTest.addPoint(scaler->transform(testSet.getPoint(i)));
        trainSet = scaledTrain;
        testSet = scaledTest;
    }

    IDistance* dist = nullptr;
    if (bestResult.config.distanceType == "euclidean")      dist = new EuclideanDistance();
    else if (bestResult.config.distanceType == "manhattan") dist = new ManhattanDistance();
    else if (bestResult.config.distanceType == "minkowski") dist = new MinkowskiDistance(3.0);
    else                                                    dist = new EuclideanDistance();

    KNNClassifier knn(bestResult.config.k, dist, bestResult.config.weighted);
    knn.fit(trainSet);

    vector<string> actual, predicted;
    for (int i = 0; i < testSet.size(); i++) {
        actual.push_back(testSet.getPoint(i).getLabel());
        predicted.push_back(knn.predict(testSet.getPoint(i)));
    }

    Evaluator eval;
    cout << "Test Accuracy: " << fixed << setprecision(2)
         << (eval.calculateAccuracy(actual, predicted) * 100.0) << "%\n";
    eval.printConfusionMatrix(actual, predicted);
    eval.printPrecision(actual, predicted);
    eval.printRecall(actual, predicted);
    eval.printF1Score(actual, predicted);

    delete dist;
    if (scaler != nullptr) delete scaler;

    return bestResult.config;
}
