#include "CSVLoader.h"
#include "ModelSelector.h"
#include "KNNClassifier.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include "MinkowskiDistance.h"
#include "StandardScaler.h"
#include "MinMaxScaler.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

void displayMenu(int k, string dist, double p, bool weighted, string scaler) {
    cout << "\n====================================\n";
    cout << "        Mini KNN Classifier\n";
    cout << "====================================\n";
    cout << "1. Load Dataset\n";
    cout << "2. View Dataset Info\n";
    cout << "3. Select K (Current: " << k << ")\n";
    if (dist == "minkowski") {
        cout << "4. Select Distance Method (Current: " << dist << ", p=" << p << ")\n";
    } else {
        cout << "4. Select Distance Method (Current: " << dist << ")\n";
    }
    cout << "5. Select Voting Method (Current: " << (weighted ? "Weighted" : "Normal") << ")\n";
    cout << "6. Select Scaler Method (Current: " << scaler << ")\n";
    cout << "7. Predict New Point\n";
    cout << "8. Run Cross Validation & Select Best Model\n";
    cout << "9. Train Final Model\n";
    cout << "10. Exit\n";
    cout << "------------------------------------\n";
    cout << "Pick an option: ";
}

int main() {
    DataSet mainDataset;
    bool datasetLoaded = false;
    
    // Manual configs
    int manualK = 5;
    string manualDistance = "euclidean";
    double manualP = 3.0;
    bool manualWeighted = false;
    string manualScaler = "none";
    
    // Automated configs
    ModelConfig bestConfig = {5, "euclidean", "standard", false};
    bool hasBestConfig = false;
    
    // Final trained model state
    bool finalModelTrained = false;
    KNNClassifier* finalKNN = nullptr;
    IDistance* finalDistance = nullptr;
    IScaler* finalScaler = nullptr;

    int choice;
    while (true) {
        displayMenu(manualK, manualDistance, manualP, manualWeighted, manualScaler);
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, try again.\n";
            continue;
        }

        if (choice == 1) {
            string filename = "data/iris.csv";
            CSVLoader loader;
            mainDataset = loader.load(filename);
            if (mainDataset.size() > 0) {
                cout << "Loaded! Got " << mainDataset.size() << " data points from " << filename << ".\n";
                datasetLoaded = true;
            } else {
                cout << "Hmm, could not load the file. Check if data/iris.csv exists.\n";
            }

        } else if (choice == 2) {
            if (!datasetLoaded) {
                cout << "Load the dataset first (Option 1).\n";
            } else {
                int numFeatures = mainDataset.getPoint(0).getFeatures().size();
                cout << "\n--- Dataset Info ---\n";
                cout << "Total rows    : " << mainDataset.size() << "\n";
                cout << "Total features: " << numFeatures << "\n";
                cout << "\n--- First 5 Rows ---\n";
                int rowsToPrint = mainDataset.size() < 5 ? mainDataset.size() : 5;
                for (int i = 0; i < rowsToPrint; i++) {
                    DataPoint dp = mainDataset.getPoint(i);
                    cout << "Row " << (i + 1) << ": ";
                    for (double val : dp.getFeatures()) cout << val << " ";
                    cout << " => " << dp.getLabel() << "\n";
                }
            }
            
        } else if (choice == 3) {
            cout << "Enter new K value: ";
            cin >> manualK;
            cout << "K set to " << manualK << ".\n";
            
        } else if (choice == 4) {
            cout << "Available distances: euclidean, manhattan, minkowski\n";
            cout << "Enter distance method: ";
            cin >> manualDistance;
            if (manualDistance != "euclidean" && manualDistance != "manhattan" && manualDistance != "minkowski") {
                cout << "Invalid distance, falling back to euclidean.\n";
                manualDistance = "euclidean";
            } else {
                cout << "Distance set to " << manualDistance << ".\n";
                if (manualDistance == "minkowski") {
                    cout << "Enter p value for Minkowski distance (choose p >= 1): ";
                    cin >> manualP;
                    if (manualP < 1.0) {
                        cout << "Invalid p. Setting p = 1.0 (Manhattan equivalent).\n";
                        manualP = 1.0;
                    } else {
                        cout << "p value set to " << manualP << ".\n";
                    }
                }
            }
            
        } else if (choice == 5) {
            cout << "Available voting methods: 1 for Normal, 2 for Weighted\n";
            cout << "Enter choice: ";
            int voteChoice;
            cin >> voteChoice;
            if (voteChoice == 2) {
                manualWeighted = true;
                cout << "Voting method set to Weighted.\n";
            } else {
                manualWeighted = false;
                cout << "Voting method set to Normal.\n";
            }
            
        } else if (choice == 6) {
            cout << "Available scalers: none, standard, minmax\n";
            cout << "Enter scaler method: ";
            cin >> manualScaler;
            if (manualScaler != "none" && manualScaler != "standard" && manualScaler != "minmax") {
                cout << "Invalid scaler, falling back to none.\n";
                manualScaler = "none";
            } else {
                cout << "Scaler set to " << manualScaler << ".\n";
            }

        } else if (choice == 7) {
            if (!datasetLoaded) {
                cout << "Load the dataset first (Option 1).\n";
            } else {
                cout << "Enter 4 feature values (example: 5.1 3.5 1.4 0.2): \n";
                double f1, f2, f3, f4;
                cin >> f1 >> f2 >> f3 >> f4;

                // Clear any extra input (like a 5th feature) to avoid messing up the next menu prompt
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vector<double> features = {f1, f2, f3, f4};
                DataPoint newPoint(features, "Unknown");
                string prediction = "";
                
                if (finalModelTrained) {
                    cout << "\nUsing the automated Final Model from Cross Validation...\n";
                    DataPoint processPoint = newPoint;
                    if (finalScaler != nullptr) {
                        processPoint = finalScaler->transform(newPoint);
                    }
                    prediction = finalKNN->predict(processPoint);
                } else {
                    if (manualDistance == "minkowski") {
                        cout << "\nUsing Manual Model (K=" << manualK << ", Distance=" << manualDistance << ", p=" << manualP << ", " << (manualWeighted ? "Weighted" : "Normal") << ", Scaler=" << manualScaler << ")...\n";
                    } else {
                        cout << "\nUsing Manual Model (K=" << manualK << ", Distance=" << manualDistance << ", " << (manualWeighted ? "Weighted" : "Normal") << ", Scaler=" << manualScaler << ")...\n";
                    }
                    
                    IDistance* dist = nullptr;
                    if (manualDistance == "manhattan") dist = new ManhattanDistance();
                    else if (manualDistance == "minkowski") dist = new MinkowskiDistance(manualP);
                    else dist = new EuclideanDistance();
                    
                    IScaler* scaler = nullptr;
                    if (manualScaler == "standard") scaler = new StandardScaler();
                    else if (manualScaler == "minmax") scaler = new MinMaxScaler();

                    DataSet trainData = mainDataset;
                    DataPoint processPoint = newPoint;
                    
                    if (scaler != nullptr) {
                        scaler->fit(trainData);
                        DataSet scaledTrain;
                        for (int i = 0; i < trainData.size(); i++) {
                            scaledTrain.addPoint(scaler->transform(trainData.getPoint(i)));
                        }
                        trainData = scaledTrain;
                        processPoint = scaler->transform(newPoint);
                    }
                    
                    KNNClassifier knn(manualK, dist, manualWeighted);
                    knn.fit(trainData);
                    prediction = knn.predict(processPoint);
                    
                    delete dist;
                    if (scaler != nullptr) delete scaler;
                }
                
                cout << "Predicted Class: " << prediction << "\n";
            }
            
        } else if (choice == 8) {
            if (!datasetLoaded) {
                cout << "Load the dataset first (Option 1).\n";
            } else {
                ModelSelector selector;
                bestConfig = selector.findBestModel(mainDataset);
                hasBestConfig = true;
                
                // Automatically update the menu to show the newly found best parameters
                manualK = bestConfig.k;
                manualDistance = bestConfig.distanceType;
                manualWeighted = bestConfig.weighted;
                manualScaler = bestConfig.scalerType;
                if (manualDistance == "minkowski") {
                    manualP = 3.0; // Best model always uses p=3.0 during CV
                }
            }

        } else if (choice == 9) {
            if (!datasetLoaded) {
                cout << "Load the dataset first (Option 1).\n";
            } else if (!hasBestConfig) {
                cout << "Run Cross Validation first (Option 8) to find the best config.\n";
            } else {
                if (finalScaler != nullptr) { delete finalScaler; finalScaler = nullptr; }
                if (finalDistance != nullptr) { delete finalDistance; finalDistance = nullptr; }
                if (finalKNN != nullptr) { delete finalKNN; finalKNN = nullptr; }

                DataSet trainingData = mainDataset;

                if (bestConfig.scalerType == "standard") {
                    finalScaler = new StandardScaler();
                } else if (bestConfig.scalerType == "minmax") {
                    finalScaler = new MinMaxScaler();
                }

                if (finalScaler != nullptr) {
                    finalScaler->fit(trainingData);
                    DataSet scaledTrain;
                    for (int i = 0; i < trainingData.size(); i++) {
                        scaledTrain.addPoint(finalScaler->transform(trainingData.getPoint(i)));
                    }
                    trainingData = scaledTrain;
                }

                if (bestConfig.distanceType == "euclidean") finalDistance = new EuclideanDistance();
                else if (bestConfig.distanceType == "manhattan") finalDistance = new ManhattanDistance();
                else if (bestConfig.distanceType == "minkowski") finalDistance = new MinkowskiDistance(3.0);
                else finalDistance = new EuclideanDistance();

                finalKNN = new KNNClassifier(bestConfig.k, finalDistance, bestConfig.weighted);
                finalKNN->fit(trainingData);
                finalModelTrained = true;

                cout << "Model trained on all " << mainDataset.size() << " data points. Ready to predict!\n";
                cout << "Final model trained! Option 7 will now use this optimized model automatically.\n";
            }

        } else if (choice == 10) {
            cout << "Bye\n";
            break;
        } else {
            cout << "Invalid option, try again.\n";
        }
    }
    
    // Cleanup
    if (finalScaler != nullptr) delete finalScaler;
    if (finalDistance != nullptr) delete finalDistance;
    if (finalKNN != nullptr) delete finalKNN;
    
    return 0;
}
