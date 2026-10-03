#include <iostream>
#include <string>
#include "DataSet.h"
#include "KNNClassifier.h"
#include "Evaluator.h"

using namespace std;

int main() {
    DataSet dataset;
    DataSet trainSet;
    DataSet testSet;
    int kValue = 5;
    string distanceType = "euclidean";
    bool dataLoaded = false;
    
    while(true) {
        cout << "\n--- KNN Menu ---\n";
        cout << "1. Load Iris Data\n";
        cout << "2. Show data info\n";
        cout << "3. Change K (now " << kValue << ")\n";
        cout << "4. Change distance (now " << distanceType << ")\n";
        cout << "5. Test accuracy\n";
        cout << "6. Predict point\n";
        cout << "7. Quit\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            dataset.loadCSV("data/iris.csv");
            if (dataset.size() > 0) {
                dataset.shuffle();
                trainSet = DataSet();
                testSet = DataSet();
                dataset.splitTrainTest(0.8, trainSet, testSet);
                dataLoaded = true;
                cout << "Data loaded okay\n";
            } else {
                cout << "Failed to load\n";
            }
        } else if (choice == 2) {
            if(!dataLoaded) {
                cout << "Load data first\n";
            } else {
                cout << "Total: " << dataset.size() << "\n";
                cout << "Train: " << trainSet.size() << "\n";
                cout << "Test: " << testSet.size() << "\n";
            }
        } else if (choice == 3) {
            cout << "New K: ";
            cin >> kValue;
            cout << "K is now " << kValue << "\n";
        } else if (choice == 4) {
            cout << "1. Euclidean\n";
            cout << "2. Manhattan\n";
            cout << "Enter (1/2): ";
            int distChoice;
            cin >> distChoice;
            if(distChoice == 1) {
                distanceType = "euclidean";
            } else {
                distanceType = "manhattan";
            }
        } else if (choice == 5) {
            if(!dataLoaded) {
                cout << "Load data first\n";
            } else {
                cout << "Testing...\n";
                KNNClassifier knn(kValue);
                knn.setDistanceType(distanceType);
                knn.fit(trainSet);
                
                Evaluator eval;
                double acc = eval.calculateAccuracy(testSet, knn);
                cout << "Accuracy: " << acc * 100 << "%\n";
            }
        } else if (choice == 6) {
            if(!dataLoaded) {
                cout << "Load data first\n";
            } else {
                double sl, sw, pl, pw;
                cout << "Sepal Length: ";
                cin >> sl;
                cout << "Sepal Width: ";
                cin >> sw;
                cout << "Petal Length: ";
                cin >> pl;
                cout << "Petal Width: ";
                cin >> pw;
                
                vector<double> feats;
                feats.push_back(sl);
                feats.push_back(sw);
                feats.push_back(pl);
                feats.push_back(pw);
                
                DataPoint newPoint(feats, "Unknown");
                
                KNNClassifier knn(kValue);
                knn.setDistanceType(distanceType);
                knn.fit(dataset); 
                
                string p = knn.predict(newPoint);
                cout << "Prediction: " << p << "\n";
            }
        } else if (choice == 7) {
            cout << "Bye\n";
            break;
        } else {
            cout << "Wrong choice\n";
        }
    }
    return 0;
}
