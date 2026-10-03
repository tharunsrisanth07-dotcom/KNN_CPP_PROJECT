#pragma once
#include <string>

using namespace std;

struct ModelConfig {
    int k;
    string distanceType; 
    string scalerType;   
    bool weighted;
};
