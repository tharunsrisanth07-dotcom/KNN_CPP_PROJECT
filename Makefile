all:
	g++ -Iinclude main.cpp src/*.cpp -o miniknn

clean:
	rm -f miniknn miniknn.exe
