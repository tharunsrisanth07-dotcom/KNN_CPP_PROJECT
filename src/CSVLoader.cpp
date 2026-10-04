#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>

DataSet CSVLoader::load(const std::string& filename) const {
    DataSet dataset;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return dataset;
    }
    
    std::string line;
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, value, ',')) {
            tokens.push_back(value);
        }
        
        if (tokens.size() > 1) {
            std::string label = tokens.back();
            if (!label.empty() && label.back() == '\r') {
                label.pop_back();
            }
            
            std::vector<double> features;
            for (size_t i = 0; i < tokens.size() - 1; ++i) {
                try {
                    features.push_back(std::stod(tokens[i]));
                } catch (const std::exception& e) {
                    // if conversion fails, skip
                }
            }
            
            if (features.size() == tokens.size() - 1) {
                dataset.addPoint(DataPoint(features, label));
            }
        }
    }
    
    file.close();
    return dataset;
}
