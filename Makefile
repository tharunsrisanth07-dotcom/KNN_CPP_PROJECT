CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRCS = src/DataPoint.cpp \
       src/DataSet.cpp \
       src/CSVLoader.cpp \
       src/EuclideanDistance.cpp \
       src/ManhattanDistance.cpp \
       src/MinkowskiDistance.cpp \
       src/StandardScaler.cpp \
       src/MinMaxScaler.cpp \
       src/KNNClassifier.cpp \
       src/Evaluator.cpp \
       src/CrossValidator.cpp \
       src/ModelSelector.cpp \
       src/PredictionService.cpp \
       main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = miniknn

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
