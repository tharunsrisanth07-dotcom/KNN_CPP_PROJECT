all:
	-mkdir build
	g++ -std=c++17 -Iinclude -c src/DataPoint.cpp -o build/DataPoint.o
	g++ -std=c++17 -Iinclude -c src/DataSet.cpp -o build/DataSet.o
	g++ -std=c++17 -Iinclude -c src/CSVLoader.cpp -o build/CSVLoader.o
	g++ -std=c++17 -Iinclude -c src/EuclideanDistance.cpp -o build/EuclideanDistance.o
	g++ -std=c++17 -Iinclude -c src/ManhattanDistance.cpp -o build/ManhattanDistance.o
	g++ -std=c++17 -Iinclude -c src/MinkowskiDistance.cpp -o build/MinkowskiDistance.o
	g++ -std=c++17 -Iinclude -c src/StandardScaler.cpp -o build/StandardScaler.o
	g++ -std=c++17 -Iinclude -c src/MinMaxScaler.cpp -o build/MinMaxScaler.o
	g++ -std=c++17 -Iinclude -c src/KNNClassifier.cpp -o build/KNNClassifier.o
	g++ -std=c++17 -Iinclude -c src/Evaluator.cpp -o build/Evaluator.o
	g++ -std=c++17 -Iinclude -c src/CrossValidator.cpp -o build/CrossValidator.o
	g++ -std=c++17 -Iinclude -c src/ModelSelector.cpp -o build/ModelSelector.o
	g++ -std=c++17 -Iinclude -c main.cpp -o build/main.o
	g++ build/DataPoint.o build/DataSet.o build/CSVLoader.o build/EuclideanDistance.o build/ManhattanDistance.o build/MinkowskiDistance.o build/StandardScaler.o build/MinMaxScaler.o build/KNNClassifier.o build/Evaluator.o build/CrossValidator.o build/ModelSelector.o build/main.o -o miniknn

clean:
	rm -rf build miniknn miniknn.exe
