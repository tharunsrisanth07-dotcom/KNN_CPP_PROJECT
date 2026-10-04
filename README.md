# MiniKNN: K-Nearest Neighbours Classifier Library

## 1. Project Title
MiniKNN: A Custom C++ implementation of the K-Nearest Neighbours (KNN) classification algorithm.

## 2. Problem Statement
This project demonstrates how to build a Machine Learning pipeline in standard C++17 from scratch, without external dependencies like scikit-learn or OpenCV. It solves the problem of classifying data points into categories based on nearest neighbors.

## 3. What is KNN
K-Nearest Neighbours is a simple, intuitive machine learning algorithm. It classifies a new data point based on the majority class of its 'K' closest neighbors in the training dataset.

## 4. How KNN works
- Calculate the distance between the test point and all training points.
- Sort the distances.
- Select the first K nearest points.
- Find the most frequent class among these K points (or use weighted voting).

## 5. Architecture
The project follows a strong Object-Oriented design with several layers:
- Data Layer: Manages datasets and parsing (DataSet, DataPoint, CSVLoader).
- Distance Layer: Handles distance metrics (Euclidean, Manhattan).
- Scaling Layer: Handles feature normalization (StandardScaler, MinMaxScaler).
- ML Layer: The core KNN algorithm.
- Evaluation Layer: Performs cross-validation and selects the best model.
- App Layer: Handles user prediction.

## 6. Class Responsibilities
- `DataPoint`: Represents a single row in the dataset.
- `DataSet`: A collection of DataPoints.
- `CSVLoader`: Parses CSV files to create a DataSet.
- `IDistance`: Abstract interface for distances.
- `IScaler`: Abstract interface for scaling.
- `KNNClassifier`: Core prediction algorithm.
- `CrossValidator`: Performs K-Fold cross validation.
- `ModelSelector`: Selects the best hyperparameter configuration.
- `PredictionService`: Handles end-to-end user prediction.

## 7. Distance Metrics
The project supports Euclidean and Manhattan distance.

## 8. Feature Scaling
Features are scaled using either Standard scaling (mean 0, std dev 1) or Min-Max scaling ([0, 1] range) to ensure all features contribute equally.

## 9. Weighted KNN
Optionally gives closer neighbors more weight using `weight = 1 / (distance + epsilon)`.

## 10. Cross-validation
Uses Stratified 5-Fold Cross Validation. The dataset is split into 5 equal parts. The model is trained on 4 parts and validated on the remaining 1 part, repeating this 5 times.

## 11. Model selection
Tests 36 configurations (combinations of K, distance metrics, scalers, and weights) and selects the one with the highest average CV accuracy.

## 12. Final prediction pipeline
The best configuration is used to train a final model on the entire dataset. When a user inputs a new point, the same scaler is applied, and the final KNN model makes the prediction.

## 13. How to compile
Use the provided Makefile:
```sh
make
```

## 14. How to run
```sh
./miniknn
```

## 15. Example Output
```text
====================================
        MINI KNN CLASSIFIER
====================================
1. Load Dataset
...
```
