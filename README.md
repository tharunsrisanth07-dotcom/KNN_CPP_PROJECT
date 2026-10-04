# MiniKNN — K-Nearest Neighbours Classifier in C++

A KNN classifier built from scratch in C++17. No external libraries.

---

## Features

- Euclidean, Manhattan, Minkowski distance
- Standard Scaler & MinMax Scaler
- Weighted KNN
- 5-Fold Cross Validation (fixed seed = 42)
- Auto model selection (54 configs tested)
- Confusion Matrix, Precision, Recall, F1 Score

---

## Project Structure

```
KNN_CPP_PROJECT/
├── main.cpp
├── include/          ← all .h files
├── src/              ← all .cpp files
├── data/iris.csv
└── Makefile
```

### Classes

| Class | What it does |
|---|---|
| `DataPoint` | Stores one row: features + label |
| `DataSet` | Collection of DataPoints |
| `CSVLoader` | Reads CSV into a DataSet |
| `IDistance` | Interface for distance metrics |
| `EuclideanDistance` | sqrt of sum of squared diffs |
| `ManhattanDistance` | sum of absolute diffs |
| `MinkowskiDistance` | generalised distance (p=3) |
| `IScaler` | Interface for feature scaling |
| `StandardScaler` | normalise to mean=0, std=1 |
| `MinMaxScaler` | normalise to [0, 1] |
| `KNNClassifier` | core KNN: fit + predict |
| `Evaluator` | accuracy, confusion matrix, precision, recall, F1 |
| `CrossValidator` | K-Fold cross validation |
| `ModelSelector` | tries all configs, picks best |
| `PredictionService` | end-to-end predict for new point |

---

## UML Class Diagram

```
DataPoint ──< DataSet <── CSVLoader

IDistance <|── EuclideanDistance
IDistance <|── ManhattanDistance
IDistance <|── MinkowskiDistance

IScaler   <|── StandardScaler
IScaler   <|── MinMaxScaler

KNNClassifier ──> IDistance
KNNClassifier ──> DataSet

CrossValidator ──> KNNClassifier
CrossValidator ──> Evaluator
CrossValidator ──> IScaler

ModelSelector ──> CrossValidator

PredictionService ──> KNNClassifier
PredictionService ──> IScaler
PredictionService ──> IDistance
```

---

## How to Compile & Run

**Linux / Mac:**
```bash
make
./miniknn
```

**Windows (no make):**
```powershell
g++ -std=c++17 -Iinclude src/*.cpp main.cpp -o miniknn
./miniknn
```

---

## Menu

```
1. Load Dataset
2. View Dataset Information     ← shows dimensions + first 5 rows
3. Run Cross Validation         ← tests 54 configs, prints best + metrics
4. Train Final Model
5. Predict New Point
6. Exit
```

---

## How KNN Works

1. Calculate distance from new point to every training point
2. Sort by distance
3. Pick K nearest neighbours
4. Return the class with the most votes (or highest weight if weighted)

## How K-Fold Works

1. Shuffle data with `seed = 42` (fixed, reproducible)
2. Split into 5 equal folds
3. For each fold: train on 4 folds, test on 1
4. Average the 5 accuracies = CV accuracy

## Evaluation Metrics

| Metric | Formula |
|---|---|
| Accuracy | correct / total |
| Precision | TP / (TP + FP) |
| Recall | TP / (TP + FN) |
| F1 Score | 2 × (P × R) / (P + R) |
