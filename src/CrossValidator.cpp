#include "CrossValidator.h"
#include "KNNClassifier.h"
#include "Evaluator.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include "MinkowskiDistance.h"
#include "StandardScaler.h"
#include "MinMaxScaler.h"
#include <map>
#include <iostream>

ModelResult CrossValidator::evaluate(const DataSet& data, const ModelConfig& config, int folds) const {
    ModelResult result;
    result.config = config;
    result.averageAccuracy = 0.0;
    
    if (data.size() == 0 || folds <= 1) return result;

    // Fix the shuffling using seed = 42 (like srand(42) but for C++ random)
    // This makes sure every run gives the same fold split
    DataSet shuffledData = data;
    shuffledData.shuffle(42);   // seed = 42, fixed so results are reproducible

    // Stratified Split: group points by class, then distribute into folds
    std::map<std::string, std::vector<DataPoint>> classGroups;
    for (size_t i = 0; i < shuffledData.size(); ++i) {
        classGroups[shuffledData.getPoint(i).getLabel()].push_back(shuffledData.getPoint(i));
    }
    
    std::vector<DataSet> foldSets(folds);
    for (auto& pair : classGroups) {
        auto& points = pair.second;
        for (size_t i = 0; i < points.size(); ++i) {
            foldSets[i % folds].addPoint(points[i]);
        }
    }

    double totalAccuracy = 0.0;
    // We store actual/predicted of the LAST fold to print metrics once at the end
    std::vector<std::string> lastActual, lastPredicted;

    for (int i = 0; i < folds; ++i) {
        DataSet validationData = foldSets[i];
        DataSet trainingData;
        for (int j = 0; j < folds; ++j) {
            if (i != j) {
                for (size_t p = 0; p < foldSets[j].size(); ++p) {
                    trainingData.addPoint(foldSets[j].getPoint(p));
                }
            }
        }

        IScaler* scaler = nullptr;
        if (config.scalerType == "standard") scaler = new StandardScaler();
        else if (config.scalerType == "minmax") scaler = new MinMaxScaler();

        if (scaler) {
            scaler->fit(trainingData);
            DataSet scaledTrain;
            for (size_t p = 0; p < trainingData.size(); ++p) {
                scaledTrain.addPoint(scaler->transform(trainingData.getPoint(p)));
            }
            trainingData = scaledTrain;

            DataSet scaledVal;
            for (size_t p = 0; p < validationData.size(); ++p) {
                scaledVal.addPoint(scaler->transform(validationData.getPoint(p)));
            }
            validationData = scaledVal;
        }

        IDistance* dist = nullptr;
        if (config.distanceType == "euclidean")       dist = new EuclideanDistance();
        else if (config.distanceType == "manhattan")  dist = new ManhattanDistance();
        else if (config.distanceType == "minkowski")  dist = new MinkowskiDistance(3.0);
        else                                          dist = new EuclideanDistance();

        KNNClassifier knn(config.k, dist, config.weighted);
        knn.fit(trainingData);

        std::vector<std::string> actual;
        std::vector<std::string> predicted;
        for (size_t p = 0; p < validationData.size(); ++p) {
            actual.push_back(validationData.getPoint(p).getLabel());
            predicted.push_back(knn.predict(validationData.getPoint(p)));
        }

        Evaluator eval;
        double acc = eval.calculateAccuracy(actual, predicted);
        result.foldAccuracies.push_back(acc);
        totalAccuracy += acc;

        // Save last fold's predictions for printing metrics
        lastActual = actual;
        lastPredicted = predicted;

        delete dist;
        if (scaler) delete scaler;
    }

    result.averageAccuracy = totalAccuracy / folds;
    return result;
}
