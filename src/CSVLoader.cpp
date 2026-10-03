#include "CSVLoader.h"
#include <fstream>
#include <sstream>

using namespace std;

DataSet CSVLoader::load(string filename) {
    DataSet dataset;
    ifstream file(filename);
    
    if(!file.is_open()) {
        return dataset; 
    }
    
    string line;
    getline(file, line); 
    
    while(getline(file, line)) {
        if(line == "") continue;
        
        stringstream ss(line);
        string f1, f2, f3, f4, label;
        
        // Iris dataset has exactly 4 numbers and 1 label
        getline(ss, f1, ',');
        getline(ss, f2, ',');
        getline(ss, f3, ',');
        getline(ss, f4, ',');
        getline(ss, label, ',');
        
        if (label.length() > 0 && label[label.length()-1] == '\r') {
            label.pop_back();
        }
        
        vector<double> features;
        features.push_back(stod(f1));
        features.push_back(stod(f2));
        features.push_back(stod(f3));
        features.push_back(stod(f4));
        
        DataPoint pt(features, label);
        dataset.addPoint(pt);
    }
    
    file.close();
    return dataset;
}
