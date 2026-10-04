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

Header files (`.h`) are in the `include/` folder and implementation files (`.cpp`) are in the `src/` folder.

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

## Diagrams and Flow

The UML Class Diagram and Program Flowchart have been placed in a separate file for better readability.

👉 **[View Diagrams here](diagrams.md)**

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
g++ -Iinclude main.cpp src/*.cpp -o miniknn
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

---

## Design Decisions

### Why IDistance (Interface)?
Distance calculation is pluggable. `KNNClassifier` holds a `unique_ptr<IDistance>`, so switching between Euclidean and Manhattan doesn't change any algorithm logic.

### Why loadCSV inside DataSet?
The dataset is responsible for managing its own data, including how it loads from a file. This is simpler and keeps the class self-contained.

### Why 80/20 split?
150 samples → 120 training, 30 testing. Standard ML practice. Gives enough training data while keeping a fair test set.

### Why shuffle before split?
Iris CSV is sorted by class. Without shuffle, the test set would only contain one class and the results would be inaccurate.

---

## Team Responsibilities

| Member | Work |
|--------|------|
| Member 1 | DataPoint, DataSet classes |
| Member 2 | IDistance, EuclideanDistance, ManhattanDistance |
| Member 3 | KNNClassifier — fit and predict logic |
| Member 4 | Evaluator, main.cpp, menu |

---

## Possible Extensions (for Meet 2 discussion)

| Extension | What it adds |
|-----------|--------------|
| Cross Validation | Split into N folds, test each fold, average accuracy |
| Feature Scaling | Normalize features so large values don't dominate distance |
| Weighted KNN | Closer neighbours get higher vote weight |
| Multiple Datasets | Load any CSV, not just Iris |
| Best K Finder | Loop K from 1 to 20, pick the K with highest accuracy |
