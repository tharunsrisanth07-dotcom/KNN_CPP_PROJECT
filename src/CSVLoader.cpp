#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

DataSet CSVLoader::load(string filename) {
    DataSet dataset;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return dataset;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string value;
        vector<string> tokens;

        while (getline(ss, value, ',')) {
            tokens.push_back(value);
        }

        if (tokens.size() > 1) {
            string label = tokens.back();
            if (!label.empty() && label.back() == '\r') {
                label.pop_back();
            }

            vector<double> features;
            for (int i = 0; i < tokens.size() - 1; i++) {
                features.push_back(stod(tokens[i]));
            }

            dataset.addPoint(DataPoint(features, label));
        }
    }

    file.close();
    return dataset;
}
