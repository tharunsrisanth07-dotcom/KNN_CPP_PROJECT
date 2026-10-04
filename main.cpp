#include "CSVLoader.h"
#include "ModelSelector.h"
#include "PredictionService.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

void displayMenu() {
    std::cout << "\n====================================\n";
    std::cout << "        MINI KNN CLASSIFIER\n";
    std::cout << "====================================\n";
    std::cout << "1. Load Dataset\n";
    std::cout << "2. View Dataset Information\n";
    std::cout << "3. Run Cross Validation & Select Best Model\n";
    std::cout << "4. Train Final Model\n";
    std::cout << "5. Predict New Point\n";
    std::cout << "6. Exit\n";
    std::cout << "------------------------------------\n";
    std::cout << "  Distance options: euclidean, manhattan, minkowski\n";
    std::cout << "  Weighted KNN: enabled automatically in cross-validation\n";
    std::cout << "====================================\n";
    std::cout << "Select an option: ";
}

int main() {
    DataSet mainDataset;
    bool datasetLoaded = false;
    ModelConfig bestConfig = {5, "euclidean", "standard", false}; // Default config
    bool hasBestConfig = false;
    PredictionService predictionService;

    int choice;
    while (true) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            std::string filename;
            std::cout << "Enter dataset filename (e.g., data/iris.csv): ";
            std::cin >> filename;
            CSVLoader loader;
            mainDataset = loader.load(filename);
            if (mainDataset.size() > 0) {
                std::cout << "Dataset loaded successfully with " << mainDataset.size() << " points.\n";
                datasetLoaded = true;
            } else {
                std::cout << "Failed to load dataset or dataset is empty.\n";
            }

        } else if (choice == 2) {
            if (!datasetLoaded) {
                std::cout << "Please load a dataset first (Option 1).\n";
            } else {
                int numFeatures = 0;
                if (mainDataset.size() > 0) {
                    numFeatures = static_cast<int>(mainDataset.getPoint(0).getFeatures().size());
                }

                // Print dataset dimensions
                std::cout << "\n--- Dataset Information ---\n";
                std::cout << "Total rows    : " << mainDataset.size() << "\n";
                std::cout << "Total features: " << numFeatures << "\n";
                std::cout << "Total columns : " << (numFeatures + 1) << " (features + label)\n";

                // Print first 5 rows
                std::cout << "\n--- First 5 Rows ---\n";
                std::cout << std::setw(5) << "Row";
                for (int f = 0; f < numFeatures; ++f) {
                    std::cout << std::setw(10) << ("Feat" + std::to_string(f + 1));
                }
                std::cout << std::setw(15) << "Label" << "\n";
                std::cout << std::string(5 + numFeatures * 10 + 15, '-') << "\n";

                int rowsToPrint = static_cast<int>(mainDataset.size()) < 5 ? static_cast<int>(mainDataset.size()) : 5;
                for (int i = 0; i < rowsToPrint; ++i) {
                    const DataPoint& dp = mainDataset.getPoint(i);
                    std::cout << std::setw(5) << (i + 1);
                    for (double val : dp.getFeatures()) {
                        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << val;
                    }
                    std::cout << std::setw(15) << dp.getLabel() << "\n";
                }
                std::cout << "\n";
            }

        } else if (choice == 3) {
            if (!datasetLoaded) {
                std::cout << "Please load a dataset first (Option 1).\n";
            } else {
                ModelSelector selector;
                bestConfig = selector.findBestModel(mainDataset);
                hasBestConfig = true;
            }

        } else if (choice == 4) {
            if (!datasetLoaded) {
                std::cout << "Please load a dataset first (Option 1).\n";
            } else if (!hasBestConfig) {
                std::cout << "Please run Cross Validation first (Option 3) to find the best configuration.\n";
            } else {
                predictionService.trainFinalModel(mainDataset, bestConfig);
            }

        } else if (choice == 5) {
            if (!predictionService.getIsTrained()) {
                std::cout << "Please train the final model first (Option 4).\n";
            } else {
                std::cout << "Enter 4 feature values separated by space (e.g., 5.1 3.5 1.4 0.2): \n";
                double f1, f2, f3, f4;
                if (std::cin >> f1 >> f2 >> f3 >> f4) {
                    std::vector<double> features = {f1, f2, f3, f4};
                    DataPoint newPoint(features, "Unknown");
                    
                    std::cout << "\n---------------------------------\n";
                    std::cout << "FINAL MODEL\n";
                    std::cout << "---------------------------------\n";
                    ModelConfig currentConfig = predictionService.getConfig();
                    std::cout << "K: " << currentConfig.k << "\n";
                    std::cout << "Distance: " << currentConfig.distanceType << "\n";
                    std::cout << "Scaling: " << currentConfig.scalerType << "\n";
                    std::cout << "Weighted: " << (currentConfig.weighted ? "Yes" : "No") << "\n";
                    std::cout << "\n---------------------------------\n";
                    std::cout << "PREDICTION\n";
                    std::cout << "---------------------------------\n";
                    
                    std::string prediction = predictionService.predictNewPoint(newPoint);
                    std::cout << "Predicted Class: " << prediction << "\n";
                    std::cout << "---------------------------------\n";
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter valid numbers.\n";
                }
            }

        } else if (choice == 6) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}
