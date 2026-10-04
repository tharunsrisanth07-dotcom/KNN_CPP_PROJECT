# KNN Classifier - C++ Project

## What is this project?

This is a K-Nearest Neighbours (KNN) classifier built from scratch in C++. We used the Iris flower dataset which has 150 samples. The program lets you load the data, pick K, choose a distance method, evaluate accuracy, and predict a flower species from your own input.

---

## How KNN Works

1. Load all the training data points.
2. For a new point, calculate the distance to every training point.
3. Sort all training points from closest to farthest.
4. Take the top K closest points.
5. Look at what class label appears most among those K points.
6. That label is the prediction.

---

## Project Structure

All files are in the root folder for simplicity.

| File | What it does |
|------|-------------|
| `DataPoint.h / .cpp` | Stores one row of data (4 numbers + a label) |
| `DataSet.h / .cpp` | Stores all DataPoints, handles shuffle, split, and CSV loading |
| `IDistance.h` | Abstract base class for distance methods |
| `EuclideanDistance.h / .cpp` | Euclidean distance formula |
| `ManhattanDistance.h / .cpp` | Manhattan distance formula |
| `KNNClassifier.h / .cpp` | The main KNN algorithm (fit + predict) |
| `Evaluator.h / .cpp` | Tests the model and calculates accuracy |
| `main.cpp` | Menu-based interface to run everything |

---

## Class Design

```
DataPoint
  - features : vector<double>
  - label : string
  + getFeatures()
  + getLabel()

DataSet
  - points : vector<DataPoint>
  + loadCSV(filename)
  + shuffle()
  + splitTrainTest(ratio, train, test)
  + getPoint(index)
  + size()

IDistance  (abstract)
  + calculate(a, b) = 0

EuclideanDistance : IDistance
  + calculate(a, b)

ManhattanDistance : IDistance
  + calculate(a, b)

KNNClassifier
  - k : int
  - metric : IDistance*
  - trainingData : DataSet
  + fit(data)
  + predict(point)

Evaluator
  + calculateAccuracy(testData, classifier)
```

---

## Dataset

**Iris Dataset** - 150 rows, 4 features per row, 3 classes:
- Features: Sepal Length, Sepal Width, Petal Length, Petal Width
- Classes: Iris-setosa, Iris-versicolor, Iris-virginica

We split it 80% training (120 samples) and 20% testing (30 samples).

---

## How to Compile

Make sure you are in the project folder, then run:

```
g++ *.cpp -o miniknn
```

Or just use:

```
make
```

---

## How to Run

On Linux / Mac:
```
./miniknn
```

On Windows:
```
miniknn.exe
```

---

## Menu Options

```
====================================
        KNN CLASSIFIER MENU
====================================
1. Load dataset (Iris)
2. View dataset info
3. Choose K
4. Choose distance method (Euclidean / Manhattan)
5. Evaluate model
6. Predict a new point
7. Exit
```

---

## Sample Output

```
Enter choice: 1
Dataset loaded and split successfully.

Enter choice: 5
Evaluating model...
Accuracy: 93.3333%

Enter choice: 6
Enter Sepal Length: 5.1
Enter Sepal Width: 3.5
Enter Petal Length: 1.4
Enter Petal Width: 0.2
Predicted Class: Iris-setosa
```
