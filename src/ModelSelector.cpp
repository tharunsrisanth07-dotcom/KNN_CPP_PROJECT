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

ModelConfig ModelSelector::findBestModel(const DataSet& data) {
    std::vector<int> ks = {3, 5, 7};
    std::vector<std::string> distances = {"euclidean", "manhattan", "minkowski"};  // Added minkowski
    std::vector<std::string> scalers = {"none", "standard", "minmax"};
    std::vector<bool> weights = {false, true};

    CrossValidator cv;
    ModelResult bestResult;
    bestResult.averageAccuracy = -1.0;

    std::cout << "Running 5-Fold Cross Validation...\n\n";

    for (int k : ks) {
        for (const std::string& dist : distances) {
            for (const std::string& scaler : scalers) {
                for (bool w : weights) {
                    ModelConfig config = {k, dist, scaler, w};
                    ModelResult result = cv.evaluate(data, config, 5);
                    
                    std::cout << "K=" << k << " | " << dist << " | " << scaler 
                              << " | " << (w ? "Weighted" : "Normal") 
                              << " | Avg Acc: " << std::fixed << std::setprecision(2) 
                              << (result.averageAccuracy * 100.0) << "%\n";
                    
                    if (result.averageAccuracy > bestResult.averageAccuracy) {
                        bestResult = result;
                    }
                }
            }
        }
    }

    std::cout << "\n====================================\n";
    std::cout << "BEST CONFIGURATION\n";
    std::cout << "====================================\n";
    std::cout << "K: " << bestResult.config.k << "\n";
    std::cout << "Distance: " << bestResult.config.distanceType << "\n";
    std::cout << "Scaling: " << bestResult.config.scalerType << "\n";
    std::cout << "Weighted: " << (bestResult.config.weighted ? "Yes" : "No") << "\n";
    std::cout << "Average CV Accuracy: " << (bestResult.averageAccuracy * 100.0) << "%\n";
    std::cout << "====================================\n\n";

    // Now run the best config one more time to show full evaluation metrics
    std::cout << "--- Running best config one more time to show full metrics ---\n";
    
    // Shuffle and split 80/20 train-test for showing metrics
    DataSet shuffled = data;
    shuffled.shuffle(42);   // fixed seed so it's reproducible
    DataSet trainSet, testSet;
    shuffled.splitTrainTest(trainSet, testSet, 0.8);

    // Apply scaling
    IScaler* scaler = nullptr;
    if (bestResult.config.scalerType == "standard") scaler = new StandardScaler();
    else if (bestResult.config.scalerType == "minmax") scaler = new MinMaxScaler();

    if (scaler) {
        scaler->fit(trainSet);
        DataSet scaledTrain, scaledTest;
        for (size_t i = 0; i < trainSet.size(); ++i)
            scaledTrain.addPoint(scaler->transform(trainSet.getPoint(i)));
        for (size_t i = 0; i < testSet.size(); ++i)
            scaledTest.addPoint(scaler->transform(testSet.getPoint(i)));
        trainSet = scaledTrain;
        testSet  = scaledTest;
    }

    // Pick distance metric
    IDistance* dist = nullptr;
    if (bestResult.config.distanceType == "euclidean")       dist = new EuclideanDistance();
    else if (bestResult.config.distanceType == "manhattan")  dist = new ManhattanDistance();
    else if (bestResult.config.distanceType == "minkowski")  dist = new MinkowskiDistance(3.0);
    else                                                     dist = new EuclideanDistance();

    KNNClassifier knn(bestResult.config.k, dist, bestResult.config.weighted);
    knn.fit(trainSet);

    std::vector<std::string> actual, predicted;
    for (size_t i = 0; i < testSet.size(); ++i) {
        actual.push_back(testSet.getPoint(i).getLabel());
        predicted.push_back(knn.predict(testSet.getPoint(i)));
    }

    Evaluator eval;
    std::cout << "Test Accuracy: " << std::fixed << std::setprecision(2)
              << (eval.calculateAccuracy(actual, predicted) * 100.0) << "%\n";
    eval.printConfusionMatrix(actual, predicted);
    eval.printPrecision(actual, predicted);
    eval.printRecall(actual, predicted);
    eval.printF1Score(actual, predicted);

    delete dist;
    if (scaler) delete scaler;

    return bestResult.config;
}
