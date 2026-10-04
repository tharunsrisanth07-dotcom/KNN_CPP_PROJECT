# 🤖 MiniKNN — K-Nearest Neighbours Classifier in C++

> A complete Machine Learning pipeline built from scratch in **C++17** — no external libraries!  
> Built by a 2nd year Engineering student to demonstrate KNN classification with cross-validation, multiple distance metrics, and evaluation metrics.

---

## 📋 Table of Contents

1. [What is KNN?](#what-is-knn)
2. [Project Features](#project-features)
3. [Project Structure](#project-structure)
4. [UML Class Diagram](#uml-class-diagram)
5. [System Flowchart](#system-flowchart)
6. [KNN Algorithm Flowchart](#knn-algorithm-flowchart)
7. [K-Fold Cross Validation Flowchart](#k-fold-cross-validation-flowchart)
8. [Distance Metrics](#distance-metrics)
9. [Evaluation Metrics](#evaluation-metrics)
10. [How to Compile & Run](#how-to-compile--run)
11. [Menu Options Explained](#menu-options-explained)
12. [Viva Q&A Quick Reference](#viva-qa-quick-reference)

---

## What is KNN?

**K-Nearest Neighbours (KNN)** is one of the simplest machine learning algorithms.

> **Core Idea:** To classify a new point, look at its **K closest neighbours** in the training data. Whichever class appears most among those K neighbours → that is the predicted class.

**Example:** If K=3 and your 3 nearest neighbours are `[Iris-setosa, Iris-setosa, Iris-versicolor]`, the prediction is **Iris-setosa** (2 votes vs 1).

---

## Project Features

| Feature | Status | Description |
|---|---|---|
| Euclidean Distance | ✅ | Standard straight-line distance |
| Manhattan Distance | ✅ | Sum of absolute differences |
| Minkowski Distance | ✅ | Generalised distance (p=3) |
| Weighted KNN | ✅ | Closer neighbours get more vote weight |
| Standard Scaler | ✅ | Normalise to mean=0, std=1 |
| MinMax Scaler | ✅ | Normalise to [0, 1] range |
| K-Fold Cross Validation | ✅ | Fixed seed=42 for reproducibility |
| Model Selection | ✅ | Tries 54 configs, picks the best |
| Confusion Matrix | ✅ | Shows TP/FP/FN/TN per class |
| Precision | ✅ | TP / (TP + FP) |
| Recall | ✅ | TP / (TP + FN) |
| F1 Score | ✅ | Harmonic mean of Precision & Recall |
| View Dataset (5 rows) | ✅ | Shows dimensions + first 5 rows |

---

## Project Structure

```
KNN_CPP_PROJECT/
│
├── main.cpp                    ← Entry point, menu-driven interface
│
├── include/                    ← All header (.h) files
│   ├── DataPoint.h             ← Represents one row (features + label)
│   ├── DataSet.h               ← Collection of DataPoints
│   ├── CSVLoader.h             ← Reads CSV file into DataSet
│   ├── IDistance.h             ← Interface (abstract class) for distances
│   ├── EuclideanDistance.h     ← Euclidean distance implementation
│   ├── ManhattanDistance.h     ← Manhattan distance implementation
│   ├── MinkowskiDistance.h     ← Minkowski distance implementation
│   ├── IScaler.h               ← Interface for feature scalers
│   ├── StandardScaler.h        ← Z-score normalisation
│   ├── MinMaxScaler.h          ← Min-Max normalisation
│   ├── KNNClassifier.h         ← Core KNN logic (fit + predict)
│   ├── Evaluator.h             ← Accuracy, Confusion Matrix, Precision, Recall, F1
│   ├── CrossValidator.h        ← K-Fold cross validation
│   ├── ModelConfig.h           ← Struct holding hyperparameters
│   ├── ModelResult.h           ← Struct holding CV results
│   ├── ModelSelector.h         ← Tries all configs, finds the best one
│   └── PredictionService.h     ← End-to-end prediction for a new point
│
├── src/                        ← All implementation (.cpp) files
│   ├── DataPoint.cpp
│   ├── DataSet.cpp
│   ├── CSVLoader.cpp
│   ├── EuclideanDistance.cpp
│   ├── ManhattanDistance.cpp
│   ├── MinkowskiDistance.cpp
│   ├── StandardScaler.cpp
│   ├── MinMaxScaler.cpp
│   ├── KNNClassifier.cpp
│   ├── Evaluator.cpp
│   ├── CrossValidator.cpp
│   ├── ModelSelector.cpp
│   └── PredictionService.cpp
│
├── data/
│   └── iris.csv                ← Sample dataset
│
└── Makefile                    ← Build script
```

---

## UML Class Diagram

```
┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│                              MiniKNN — UML Class Diagram                                     │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

  ┌─────────────────────┐         ┌──────────────────────────────┐
  │      DataPoint      │         │           DataSet            │
  ├─────────────────────┤         ├──────────────────────────────┤
  │ - features: double[]│ 1    *  │ - points: DataPoint[]        │
  │ - label: string     │─────────│                              │
  ├─────────────────────┤         │ + addPoint(p)                │
  │ + getFeatures()     │         │ + getPoint(i): DataPoint     │
  │ + getLabel()        │         │ + size(): int                │
  └─────────────────────┘         │ + shuffle(seed=42)           │
                                  │ + splitTrainTest(train, test) │
                                  └──────────┬───────────────────┘
                                             │ uses
                                  ┌──────────▼───────────────────┐
                                  │         CSVLoader            │
                                  ├──────────────────────────────┤
                                  │ + load(filename): DataSet    │
                                  └──────────────────────────────┘


  ┌────────────────────┐   implements   ┌──────────────────────┐
  │   <<interface>>    │◄───────────────│  EuclideanDistance   │
  │     IDistance      │                ├──────────────────────┤
  ├────────────────────┤                │ + calculate(a,b)     │
  │ + calculate(a,b)   │                └──────────────────────┘
  └────────────────────┘◄───────────────┌──────────────────────┐
                                        │  ManhattanDistance   │
                        ◄───────────────├──────────────────────┤
                                        │ + calculate(a,b)     │
                                        └──────────────────────┘
                                        ┌──────────────────────┐
                        ◄───────────────│  MinkowskiDistance   │
                                        ├──────────────────────┤
                                        │ - p: double (=3.0)   │
                                        │ + calculate(a,b)     │
                                        └──────────────────────┘


  ┌────────────────────┐   implements   ┌──────────────────────┐
  │   <<interface>>    │◄───────────────│   StandardScaler     │
  │      IScaler       │                ├──────────────────────┤
  ├────────────────────┤                │ + fit(dataset)       │
  │ + fit(dataset)     │                │ + transform(point)   │
  │ + transform(point) │                └──────────────────────┘
  └────────────────────┘◄───────────────┌──────────────────────┐
                                        │    MinMaxScaler      │
                                        ├──────────────────────┤
                                        │ + fit(dataset)       │
                                        │ + transform(point)   │
                                        └──────────────────────┘


  ┌─────────────────────────────────────┐
  │           KNNClassifier             │
  ├─────────────────────────────────────┤
  │ - k: int                            │
  │ - distanceMetric: IDistance*        │◄─── uses EuclideanDistance/
  │ - weighted: bool                    │     ManhattanDistance/
  │ - trainingData: DataSet             │     MinkowskiDistance
  ├─────────────────────────────────────┤
  │ + KNNClassifier(k, dist, weighted)  │
  │ + fit(dataset)                      │
  │ + predict(point): string            │
  └─────────────────────────────────────┘


  ┌─────────────────────────────────────┐
  │             Evaluator               │
  ├─────────────────────────────────────┤
  │ + calculateAccuracy(actual,pred)    │
  │ + printConfusionMatrix(actual,pred) │
  │ + printPrecision(actual,pred)       │
  │ + printRecall(actual,pred)          │
  │ + printF1Score(actual,pred)         │
  └─────────────────────────────────────┘


  ┌───────────────────┐    ┌──────────────────────┐    ┌──────────────────┐
  │    ModelConfig    │    │     ModelResult       │    │  CrossValidator  │
  ├───────────────────┤    ├──────────────────────┤    ├──────────────────┤
  │ k: int            │    │ config: ModelConfig   │    │ + evaluate(data, │
  │ distanceType: str │    │ foldAccuracies: []    │    │   config, folds) │
  │ scalerType: str   │    │ averageAccuracy: dbl  │    │   : ModelResult  │
  │ weighted: bool    │    └──────────────────────┘    └──────────────────┘


  ┌──────────────────────────────────────────────────────────────────────┐
  │                          ModelSelector                               │
  ├──────────────────────────────────────────────────────────────────────┤
  │ + findBestModel(data): ModelConfig                                   │
  │   → tries 54 combinations of (k, distance, scaler, weighted)        │
  │   → runs CrossValidator for each                                     │
  │   → prints Confusion Matrix, Precision, Recall, F1 for best config  │
  └──────────────────────────────────────────────────────────────────────┘


  ┌──────────────────────────────────────────────────────────────────────┐
  │                        PredictionService                             │
  ├──────────────────────────────────────────────────────────────────────┤
  │ - finalKNN: KNNClassifier*                                           │
  │ - finalScaler: IScaler*                                              │
  │ - finalDistance: IDistance*                                          │
  │ - isTrained: bool                                                    │
  ├──────────────────────────────────────────────────────────────────────┤
  │ + trainFinalModel(data, config)                                      │
  │ + predictNewPoint(point): string                                     │
  │ + getIsTrained(): bool                                               │
  │ + getConfig(): ModelConfig                                           │
  └──────────────────────────────────────────────────────────────────────┘
```

---

## System Flowchart

```
┌────────────────────────────────────────────────────┐
│                   Program Start                    │
└──────────────────────┬─────────────────────────────┘
                       │
                       ▼
         ┌─────────────────────────┐
         │      Display Menu       │◄──────────────────┐
         └────────────┬────────────┘                   │
                      │                                │
          ┌───────────┼───────────────┐                │
          │           │               │                │
          ▼           ▼               ▼                │
    ┌──────────┐ ┌─────────┐  ┌──────────────┐        │
    │ Option 1 │ │Option 2 │  │   Option 3   │        │
    │  Load    │ │  View   │  │ Cross-Valid  │        │
    │ Dataset  │ │Dataset  │  │ & Best Model │        │
    └─────┬────┘ └────┬────┘  └──────┬───────┘        │
          │           │               │                │
          ▼           ▼               ▼                │
    ┌──────────┐ ┌──────────┐  ┌──────────────┐        │
    │ Parse CSV│ │Show rows,│  │ Try 54 KNN   │        │
    │ into     │ │dims &    │  │ configs with │        │
    │ DataSet  │ │first 5   │  │ K-Fold CV    │        │
    └──────────┘ │  rows    │  └──────┬───────┘        │
                 └──────────┘         │                │
                                      ▼                │
                              ┌──────────────┐        │
                              │ Pick config  │        │
                              │ with highest │        │
                              │  accuracy    │        │
                              │ Print metrics│        │
                              └──────┬───────┘        │
                                     │                │
          ┌──────────────────────────┘                │
          │                                           │
          ▼           ▼               ▼               │
    ┌──────────┐ ┌─────────┐  ┌──────────────┐        │
    │ Option 4 │ │Option 5 │  │   Option 6   │        │
    │  Train   │ │Predict  │  │    Exit      │        │
    │  Final   │ │  New    │  └──────────────┘        │
    │  Model   │ │  Point  │                          │
    └─────┬────┘ └────┬────┘                          │
          │           │                               │
          ▼           ▼                               │
    ┌──────────┐ ┌──────────┐                         │
    │Train KNN │ │Scale &   │                         │
    │on all    │ │Predict   ├─────────────────────────┘
    │data      │ │class     │
    └──────────┘ └──────────┘
```

---

## KNN Algorithm Flowchart

```
  Input: New point to classify, Training Data, K
         │
         ▼
  ┌─────────────────────────────────┐
  │  For each training point:       │
  │  Calculate distance to new point│
  │  (Euclidean / Manhattan /       │
  │   Minkowski)                    │
  └────────────────┬────────────────┘
                   │
                   ▼
  ┌─────────────────────────────────┐
  │  Sort all training points       │
  │  by distance (nearest first)    │
  └────────────────┬────────────────┘
                   │
                   ▼
  ┌─────────────────────────────────┐
  │  Select top K nearest neighbours│
  └────────────────┬────────────────┘
                   │
          ┌────────┴────────┐
          │                 │
          ▼                 ▼
   Weighted=false      Weighted=true
          │                 │
          ▼                 ▼
  ┌───────────────┐  ┌───────────────────────────┐
  │ Count votes   │  │ Weight = 1 / (dist + eps) │
  │ per class     │  │ Sum weights per class      │
  └───────┬───────┘  └──────────────┬────────────┘
          │                         │
          └────────┬────────────────┘
                   │
                   ▼
  ┌─────────────────────────────────┐
  │  Return class with MOST votes   │
  │  (or highest weight)            │
  └─────────────────────────────────┘
```

---

## K-Fold Cross Validation Flowchart

```
  Input: Full Dataset, ModelConfig, K=5 folds
         │
         ▼
  ┌─────────────────────────────────┐
  │  Shuffle dataset with seed=42   │
  │  (fixed seed = reproducible!)   │
  └────────────────┬────────────────┘
                   │
                   ▼
  ┌─────────────────────────────────┐
  │  Split into 5 equal parts       │
  │  (Stratified: equal class dist) │
  │                                 │
  │  [Fold1][Fold2][Fold3][Fold4][Fold5]│
  └────────────────┬────────────────┘
                   │
                   ▼
  ┌─────────────────────────────────┐
  │  Repeat 5 times (i = 0 to 4):  │
  │                                 │
  │  Validation = Fold[i]           │
  │  Training   = all other folds   │
  │                                 │
  │  → Scale training data          │
  │  → Scale validation data        │
  │  → Train KNN on training data   │
  │  → Predict on validation data   │
  │  → Calculate accuracy           │
  └────────────────┬────────────────┘
                   │
                   ▼
  ┌─────────────────────────────────┐
  │  Average accuracy of all 5 runs │
  │  = Final CV Accuracy            │
  └─────────────────────────────────┘
```

---

## Distance Metrics

### 1. Euclidean Distance
The straight-line distance between two points.

```
d = sqrt( (x1-y1)² + (x2-y2)² + ... + (xn-yn)² )
```

### 2. Manhattan Distance
Sum of absolute differences (like walking on city blocks).

```
d = |x1-y1| + |x2-y2| + ... + |xn-yn|
```

### 3. Minkowski Distance
A generalised form of both Euclidean (p=2) and Manhattan (p=1). We use p=3.

```
d = ( |x1-y1|^p + |x2-y2|^p + ... + |xn-yn|^p )^(1/p)
```

> **In viva:** "Minkowski with p=1 is Manhattan, p=2 is Euclidean, p=3 is a generalised version."

---

## Evaluation Metrics

All metrics are computed **per class** (multiclass classification).

### Confusion Matrix
A table showing how many times each actual class was predicted as each class.

```
                 Predicted
              A    B    C
Actual   A [ TP   FP   FP ]
         B [ FN   TP   FP ]
         C [ FN   FN   TP ]
```

### Precision
> "Of all the times I predicted class X, how often was I correct?"

```
Precision = TP / (TP + FP)
```

### Recall
> "Of all the actual class X samples, how many did I catch?"

```
Recall = TP / (TP + FN)
```

### F1 Score
> "The balanced average of Precision and Recall."

```
F1 = 2 × (Precision × Recall) / (Precision + Recall)
```

---

## How to Compile & Run

### On Linux / Mac / WSL:
```bash
# Compile
make

# Run
./miniknn
```

### On Windows (without make):
```bash
g++ -std=c++17 -Wall -Iinclude src/*.cpp main.cpp -o miniknn
./miniknn
```

---

## Menu Options Explained

```
====================================
        MINI KNN CLASSIFIER
====================================
1. Load Dataset                    ← Load a CSV file from disk
2. View Dataset Information        ← See rows, columns, first 5 rows
3. Run Cross Validation            ← Tries 54 configs, picks best
4. Train Final Model               ← Trains on 100% of data
5. Predict New Point               ← Type 4 feature values → get class
6. Exit
------------------------------------
  Distance options: euclidean, manhattan, minkowski
  Weighted KNN: enabled automatically in cross-validation
====================================
```

### Step-by-step usage:
1. `Option 1` → Enter `data/iris.csv`
2. `Option 2` → See dataset shape + first 5 rows
3. `Option 3` → Watch all 54 configs being tested with CV accuracy
4. `Option 4` → Train final model on entire dataset
5. `Option 5` → Enter 4 values like `5.1 3.5 1.4 0.2` → get prediction

---

## Viva Q&A Quick Reference

**Q: What is KNN?**  
A: KNN classifies a new point by finding the K nearest training points and taking a majority vote of their labels.

**Q: What is K in KNN?**  
A: K is the number of nearest neighbours we look at. We try K = 3, 5, 7 in our project and pick the best using cross-validation.

**Q: Why do we scale features?**  
A: Without scaling, a feature with large values (e.g., 1000) will dominate the distance calculation over small features (e.g., 0.5). Scaling makes all features equally important.

**Q: What is Weighted KNN?**  
A: Instead of giving all K neighbours equal votes, we give closer neighbours more weight using `weight = 1 / (distance + small_epsilon)`.

**Q: What is K-Fold Cross Validation?**  
A: We split the dataset into K equal parts (folds). In each round, we train on K-1 parts and test on the remaining 1 part. We repeat K times and average the accuracy. We use `seed=42` to fix the shuffling so results are reproducible.

**Q: What is a Confusion Matrix?**  
A: A table that shows how many times each actual class was predicted correctly (diagonal) vs predicted as the wrong class (off-diagonal).

**Q: What is Precision vs Recall?**  
A: Precision = "When I say it's class X, am I right?" | Recall = "Did I find all actual class X samples?"

**Q: What is Minkowski Distance?**  
A: It is a generalised distance formula. When p=1 it's Manhattan, when p=2 it's Euclidean. We use p=3 as a third option.

**Q: How does ModelSelector work?**  
A: It tries every combination of K (3,5,7) × Distance (3) × Scaler (3) × Weighted (2) = **54 configurations**, runs 5-Fold CV for each, and picks the one with the highest average accuracy.

---

## Author

**2nd Year Engineering Student Project**  
Built with ❤️ using pure C++17 — no external ML libraries.
