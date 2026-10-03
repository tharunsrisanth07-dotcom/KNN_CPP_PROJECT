#include <iostream>
#include <string>
#include "CSVLoader.h"
#include "DataSet.h"
#include "KNNClassifier.h"
#include "Evaluator.h"

using namespace std;

int main() {
    CSVLoader loader;
    DataSet dataset;
    DataSet trainSet;
    DataSet testSet;
    int kValue = 5;
    string distanceType = "euclidean";
    bool dataLoaded = false;
    
    while(true) {
        cout << "\n====================================\n";
        cout << "        KNN CLASSIFIER MENU         \n";
        cout << "====================================\n";
        cout << "1. Load dataset (Iris)\n";
        cout << "2. View dataset info\n";
        cout << "3. Choose K (Current: " << kValue << ")\n";
        cout << "4. Choose distance method (Current: " << distanceType << ")\n";
        cout << "5. Evaluate model\n";
        cout << "6. Predict a new point\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }
        
        switch(choice) {
            case 1: {
                dataset = loader.load("data/iris.csv");
                if (dataset.size() > 0) {
                    dataset.shuffle();
                    // Split 80% Train, 20% Test
                    trainSet = DataSet(); // reset
                    testSet = DataSet(); // reset
                    dataset.splitTrainTest(0.80, trainSet, testSet);
                    dataLoaded = true;
                    cout << "Dataset loaded and split successfully.\n";
                } else {
                    cout << "Error loading dataset.\n";
                }
                break;
            }
            case 2: {
                if(!dataLoaded) {
                    cout << "Please load dataset first.\n";
                } else {
                    cout << "Total samples: " << dataset.size() << "\n";
                    cout << "Training samples: " << trainSet.size() << "\n";
                    cout << "Testing samples: " << testSet.size() << "\n";
                }
                break;
            }
            case 3: {
                cout << "Enter new K value: ";
                cin >> kValue;
                cout << "K updated to " << kValue << ".\n";
                break;
            }
            case 4: {
                cout << "1. Euclidean\n";
                cout << "2. Manhattan\n";
                cout << "Enter choice: ";
                int distChoice;
                cin >> distChoice;
                if(distChoice == 1) {
                    distanceType = "euclidean";
                    cout << "Distance method updated to euclidean.\n";
                } else if (distChoice == 2) {
                    distanceType = "manhattan";
                    cout << "Distance method updated to manhattan.\n";
                } else {
                    cout << "Invalid choice.\n";
                }
                break;
            }
            case 5: {
                if(!dataLoaded) {
                    cout << "Please load dataset first.\n";
                } else {
                    cout << "Evaluating model...\n";
                    KNNClassifier knn(kValue);
                    knn.setDistanceType(distanceType);
                    knn.fit(trainSet);
                    
                    Evaluator eval;
                    double accuracy = eval.calculateAccuracy(testSet, knn);
                    cout << "Accuracy: " << (accuracy * 100.0) << "%\n";
                }
                break;
            }
            case 6: {
                if(!dataLoaded) {
                    cout << "Please load dataset first.\n";
                } else {
                    double sl, sw, pl, pw;
                    cout << "Enter Sepal Length: ";
                    cin >> sl;
                    cout << "Enter Sepal Width: ";
                    cin >> sw;
                    cout << "Enter Petal Length: ";
                    cin >> pl;
                    cout << "Enter Petal Width: ";
                    cin >> pw;
                    
                    vector<double> feats;
                    feats.push_back(sl);
                    feats.push_back(sw);
                    feats.push_back(pl);
                    feats.push_back(pw);
                    
                    DataPoint newPoint(feats, "Unknown");
                    
                    KNNClassifier knn(kValue);
                    knn.setDistanceType(distanceType);
                    knn.fit(dataset); // fit on all data for prediction
                    
                    string pred = knn.predict(newPoint);
                    cout << "Predicted Class: " << pred << "\n";
                }
                break;
            }
            case 7: {
                cout << "Exiting program.\n";
                return 0;
            }
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
