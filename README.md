# MiniKNN — K-Nearest Neighbours Classifier in C++

A KNN classifier built from scratch in C++. No external libraries. Uses the Iris dataset.

---

## Features

- Euclidean, Manhattan, Minkowski distance
- Standard Scaler & MinMax Scaler
- Weighted KNN
- 5-Fold Cross Validation (seed = 42, fixed for reproducibility)
- Auto model selection — tests 54 configs and picks the best one
- Confusion Matrix, Precision, Recall, F1 Score

---

## Project Structure

```
cpp/
├── main.cpp              ← entry point, menu loop
├── Makefile              ← just run: make
├── data/iris.csv         ← dataset
├── include/              ← all .h header files
│   ├── DataPoint.h
│   ├── DataSet.h
│   ├── CSVLoader.h
│   ├── IDistance.h
│   ├── EuclideanDistance.h
│   ├── ManhattanDistance.h
│   ├── MinkowskiDistance.h
│   ├── IScaler.h
│   ├── StandardScaler.h
│   ├── MinMaxScaler.h
│   ├── KNNClassifier.h
│   ├── Evaluator.h
│   ├── CrossValidator.h
│   ├── ModelConfig.h
│   ├── ModelResult.h
│   ├── ModelSelector.h
│   └── PredictionService.h
└── src/                  ← all .cpp implementation files
    ├── DataPoint.cpp
    ├── DataSet.cpp
    ├── CSVLoader.cpp
    ├── EuclideanDistance.cpp
    ├── ManhattanDistance.cpp
    ├── MinkowskiDistance.cpp
    ├── StandardScaler.cpp
    ├── MinMaxScaler.cpp
    ├── KNNClassifier.cpp
    ├── Evaluator.cpp
    ├── CrossValidator.cpp
    ├── ModelSelector.cpp
    └── PredictionService.cpp
```

---

## Classes

| Class | What it does |
|---|---|
| `DataPoint` | Stores one row: features + label |
| `DataSet` | Collection of DataPoints |
| `CSVLoader` | Reads CSV file into a DataSet |
| `IDistance` | Abstract base class for distance metrics |
| `EuclideanDistance` | sqrt of sum of squared differences |
| `ManhattanDistance` | sum of absolute differences |
| `MinkowskiDistance` | generalised distance (p=3) |
| `IScaler` | Abstract base class for feature scaling |
| `StandardScaler` | scales to mean=0, std=1 |
| `MinMaxScaler` | scales to range [0, 1] |
| `KNNClassifier` | core KNN — fit + predict |
| `Evaluator` | accuracy, confusion matrix, precision, recall, F1 |
| `CrossValidator` | K-Fold cross validation |
| `ModelConfig` | struct to store one set of hyperparameters |
| `ModelResult` | struct to store CV results |
| `ModelSelector` | tries all configs, picks the best one |
| `PredictionService` | trains final model and predicts new points |

---

## How to Compile & Run

**Linux / Mac:**
```bash
make
./miniknn
```

**Windows (MinGW):**
```powershell
g++ -std=c++17 -Iinclude src/DataPoint.cpp src/DataSet.cpp src/CSVLoader.cpp src/EuclideanDistance.cpp src/ManhattanDistance.cpp src/MinkowskiDistance.cpp src/StandardScaler.cpp src/MinMaxScaler.cpp src/KNNClassifier.cpp src/Evaluator.cpp src/CrossValidator.cpp src/ModelSelector.cpp src/PredictionService.cpp main.cpp -o miniknn
./miniknn
```

---

## Menu Options

```
1. Load Dataset
2. View Dataset Info
3. Select K
4. Select Distance Method
5. Predict a New Point
6. Run Cross Validation & Select Best Model
7. Train Final Model
8. Exit
```

---

## How KNN Works

1. Calculate distance from the new point to every training point
2. Sort by distance (smallest first)
3. Pick the K nearest neighbours
4. Return the class with the most votes (or highest weight if weighted KNN)

## How K-Fold Cross Validation Works

1. Shuffle data with seed = 42 (fixed so results are the same every run)
2. Split into 5 equal folds (stratified — each fold has all classes)
3. For each fold: train on the other 4 folds, test on this 1 fold
4. Average the 5 accuracies = final CV accuracy

## Evaluation Metrics

| Metric | Formula |
|---|---|
| Accuracy | correct predictions / total predictions |
| Precision | TP / (TP + FP) |
| Recall | TP / (TP + FN) |
| F1 Score | 2 × (Precision × Recall) / (Precision + Recall) |
