# KNN Classifier - C++ Mini Project

## Project Title
KNN (K-Nearest Neighbours) Classifier implemented in C++ using Object-Oriented Programming.

## Problem Statement
The goal of this project is to implement the K-Nearest Neighbours classification algorithm from scratch in C++. We use the Iris flower dataset to train and test the classifier. The program reads data from a CSV file, splits it into training and test sets, and then predicts the class of new data points.

## What is KNN?
K-Nearest Neighbours is a simple supervised machine learning algorithm used for classification. To classify a new point, it looks at the K closest points in the training data and picks the most common class among them.

## How KNN Works
1. Read all training data points.
2. For a new data point, calculate the Euclidean distance to every training point.
3. Sort all training points by distance (closest first).
4. Pick the top K closest points.
5. Count which class label appears the most among the K points.
6. That class is the predicted label.

## Project Architecture
The project is split into layers, each with a clear responsibility:

- **Data Layer:** `DataPoint`, `DataSet`, `CSVLoader`
- **Algorithm Layer:** `KNNClassifier`
- **Evaluation Layer:** `Evaluator`

## Class Responsibilities

### DataPoint
Stores one row of data from the dataset.
- `features` - a list of numbers (e.g. sepal length, petal width)
- `label` - the class name (e.g. "Iris-setosa")

### DataSet
Stores a collection of DataPoint objects.
- Can shuffle the data randomly
- Can split data into a training set and a test set

### CSVLoader
Reads a `.csv` file line by line and creates a DataSet.

### KNNClassifier
The main algorithm class.
- `fit(data)` - stores the training data
- `predict(point)` - calculates distances, sorts neighbors, applies majority vote, returns predicted label
- Euclidean distance is calculated internally

### Evaluator
Tests the classifier on the test set and calculates accuracy.
- Loops through each test point
- Compares predicted label to actual label
- Returns a percentage accuracy

## Dataset Used
**Iris Dataset** - 150 samples, 3 classes, 4 features each:
- Sepal Length, Sepal Width, Petal Length, Petal Width
- Classes: Iris-setosa, Iris-versicolor, Iris-virginica

## How to Compile
Run this command from the project root folder:
```bash
g++ -Iinclude main.cpp src/*.cpp -o miniknn
```

## How to Run
```bash
# On Linux/Mac
./miniknn

# On Windows
.\miniknn.exe
```

## Example Output
```
====================================
        KNN CLASSIFIER PROJECT
====================================
Dataset loaded: 150 samples.
Number of features: 4
Training Set: 120 samples
Testing Set:  30 samples

Training KNN with K = 5...

====================================
RESULTS
====================================
Accuracy: 96.6667%
====================================
```

## Team Member Responsibilities
| Member | Work Done |
|--------|-----------|
| Member 1 | DataPoint, DataSet classes |
| Member 2 | CSVLoader, CSV parsing |
| Member 3 | KNNClassifier, distance calculation |
| Member 4 | Evaluator, accuracy testing, main.cpp |
