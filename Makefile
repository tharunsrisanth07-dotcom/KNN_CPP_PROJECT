CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRCS = $(wildcard src/*.cpp) main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o miniknn

clean:
	rm -f miniknn
