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
        string token;
        vector<double> features;
        string label = "";
        
        int commaCount = 0;
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == ',') commaCount++;
        }
        
        int current = 0;
        while(getline(ss, token, ',')) {
            if(current < commaCount) {
                double val = stod(token);
                features.push_back(val);
            } else {
                label = token;
                if (label.length() > 0 && label[label.length()-1] == '\r') {
                    label.pop_back();
                }
            }
            current++;
        }
        
        if(features.size() > 0 && label != "") {
            DataPoint pt(features, label);
            dataset.addPoint(pt);
        }
    }
    
    file.close();
    return dataset;
}
