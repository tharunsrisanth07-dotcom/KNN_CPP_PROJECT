# UML Class Diagram and Program Flow

## UML Class Diagram

```mermaid
classDiagram
    class DataPoint {
        - vector~double~ features
        - string label
        + DataPoint(f: vector~double~, l: string)
        + getFeatures() vector~double~
        + getLabel() string
    }

    class DataSet {
        - vector~DataPoint~ points
        + addPoint(p: DataPoint) void
        + getPoint(index: int) DataPoint
        + size() int
        + getPoints() vector~DataPoint~
        + shuffle(seed: int) void
        + splitTrainTest(train: DataSet, test: DataSet, ratio: double) void
    }

    class CSVLoader {
        + load(filename: string) DataSet
    }

    class IDistance {
        <<abstract>>
        + calculate(a: DataPoint, b: DataPoint) double
    }

    class EuclideanDistance {
        + calculate(a: DataPoint, b: DataPoint) double
    }

    class ManhattanDistance {
        + calculate(a: DataPoint, b: DataPoint) double
    }

    class MinkowskiDistance {
        - double p
        + MinkowskiDistance(p: double)
        + calculate(a: DataPoint, b: DataPoint) double
    }

    class IScaler {
        <<abstract>>
        + fit(data: DataSet) void
        + transform(point: DataPoint) DataPoint
    }

    class StandardScaler {
        - vector~double~ mean
        - vector~double~ stdDev
        + fit(data: DataSet) void
        + transform(point: DataPoint) DataPoint
    }

    class MinMaxScaler {
        - vector~double~ minValues
        - vector~double~ maxValues
        + fit(data: DataSet) void
        + transform(point: DataPoint) DataPoint
    }

    class KNNClassifier {
        - int k
        - IDistance* distanceMetric
        - bool weighted
        - DataSet trainingData
        + KNNClassifier(k: int, metric: IDistance*, weighted: bool)
        + fit(data: DataSet) void
        + predict(point: DataPoint) string
    }

    class Evaluator {
        + calculateAccuracy(actual: vector~string~, predicted: vector~string~) double
        + printConfusionMatrix(actual: vector~string~, predicted: vector~string~) void
        + printPrecision(actual: vector~string~, predicted: vector~string~) void
        + printRecall(actual: vector~string~, predicted: vector~string~) void
        + printF1Score(actual: vector~string~, predicted: vector~string~) void
    }

    class ModelConfig {
        + int k
        + string distanceType
        + string scalerType
        + bool weighted
    }

    class ModelResult {
        + ModelConfig config
        + vector~double~ foldAccuracies
        + double averageAccuracy
    }

    class CrossValidator {
        + evaluate(data: DataSet, config: ModelConfig, folds: int) ModelResult
    }

    class ModelSelector {
        + findBestModel(data: DataSet) ModelConfig
    }

    DataSet "1" o-- "many" DataPoint : contains
    CSVLoader --> DataSet : creates

    IDistance <|-- EuclideanDistance : inherits
    IDistance <|-- ManhattanDistance : inherits
    IDistance <|-- MinkowskiDistance : inherits

    IScaler <|-- StandardScaler : inherits
    IScaler <|-- MinMaxScaler : inherits

    KNNClassifier --> IDistance : uses
    KNNClassifier o-- DataSet : stores training data

    CrossValidator --> KNNClassifier : creates and uses
    CrossValidator --> Evaluator : uses
    CrossValidator --> IScaler : uses
    CrossValidator --> ModelConfig : takes as input
    CrossValidator --> ModelResult : returns

    ModelSelector --> CrossValidator : calls evaluate
    ModelSelector --> ModelConfig : returns best

```

---

## Program Flowchart

```mermaid
flowchart TD
    A([Start]) --> B[Show Menu]
    B --> C{User Choice}

    C -->|1 - Load Dataset| D[CSVLoader reads data/iris.csv]
    D --> E[DataSet is filled with DataPoints]
    E --> B

    C -->|2 - View Info| F[Print dimensions and first 5 rows]
    F --> B
    
    C -->|3 - Select K| G[Read new K from user]
    G --> B
    
    C -->|4 - Select Distance| H[Read distance method from user]
    H --> B

    C -->|5 - Select Voting Method| V[Read Normal or Weighted from user]
    V --> B

    C -->|6 - Select Scaler Method| SC[Read none, standard, or minmax from user]
    SC --> B

    C -->|7 - Predict New Point| N[User enters 4 feature values]
    N --> O[Create DataPoint]
    O --> P{Is Final Model Trained?}
    P -->|Yes| Q1[Use automated Final Model]
    P -->|No| Q2[Manual KNNClassifier.fit & predict]
    Q1 --> R[Print predicted class]
    Q2 --> R
    R --> B

    C -->|8 - Cross Validation| I[ModelSelector.findBestModel]
    I --> J[Try all 54 configs with CrossValidator]
    J --> K[Print each config accuracy]
    K --> L[Print best config and full metrics]
    L --> B

    C -->|9 - Train Final Model| M[Train final model in main.cpp]
    M --> B

    C -->|10 - Exit| S([Exit])
```

---

## How Data Flows Through the Project

```
iris.csv
   ↓
CSVLoader → DataSet (150 DataPoints)
   ↓
ModelSelector
   ↓ tries 54 combinations of K, distance, scaler, weighted
CrossValidator (5-Fold)
   ↓ for each fold: trains KNNClassifier, checks accuracy
Evaluator → prints confusion matrix, precision, recall, F1
   ↓
Best ModelConfig
   ↓
main.cpp → trains on ALL 150 points → ready to predict new data
```
