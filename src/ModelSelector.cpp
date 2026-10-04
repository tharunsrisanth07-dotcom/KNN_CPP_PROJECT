#include "ModelSelector.h"
#include "CrossValidator.h"
#include <iostream>
#include <iomanip>

ModelConfig ModelSelector::findBestModel(const DataSet& data) {
    std::vector<int> ks = {3, 5, 7};
    std::vector<std::string> distances = {"euclidean", "manhattan"};
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

    return bestResult.config;
}
