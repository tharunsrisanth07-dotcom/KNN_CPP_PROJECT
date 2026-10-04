#include "CSVLoader.h"
#include "ModelSelector.h"
#include "PredictionService.h"
#include <iostream>
#include <string>
#include <limits>

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
                std::cout << "Dataset Size: " << mainDataset.size() << " points.\n";
                if (mainDataset.size() > 0) {
                    std::cout << "Number of features: " << mainDataset.getPoint(0).getFeatures().size() << "\n";
                }
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
