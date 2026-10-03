#include "KNNClassifier.h"
#include <cmath>
#include <vector>

using namespace std;

struct Neighbor {
    double distance;
    string label;
};

KNNClassifier::KNNClassifier(int kValue) {
    k = kValue;
}

void KNNClassifier::fit(DataSet data) {
    trainingData = data;
}

double KNNClassifier::calculateDistance(DataPoint a, DataPoint b) {
    vector<double> f1 = a.getFeatures();
    vector<double> f2 = b.getFeatures();
    double sum = 0.0;

    for(int i = 0; i < f1.size(); i++) {
        double diff = f1[i] - f2[i];
        sum = sum + (diff * diff);
    }

    return sqrt(sum);
}

string KNNClassifier::predict(DataPoint point) {
    vector<Neighbor> neighbors;

    for(int i = 1; i <= trainingData.size(); i++) {
        DataPoint trainPoint = trainingData.getPoint(i);
        double dist = calculateDistance(point, trainPoint);

        Neighbor n;
        n.distance = dist;
        n.label = trainPoint.getLabel();
        neighbors.push_back(n);
    }

    for(int i = 0; i < neighbors.size(); i++) {
        for(int j = i + 1; j < neighbors.size(); j++) {
            if(neighbors[j].distance < neighbors[i].distance) {
                Neighbor temp = neighbors[i];
                neighbors[i] = neighbors[j];
                neighbors[j] = temp;
            }
        }
    }

    int actualK = k;
    if (neighbors.size() < k) {
        actualK = neighbors.size();
    }

    vector<string> labels;
    vector<int> counts;

    for(int i = 0; i < actualK; i++) {
        string l = neighbors[i].label;
        bool found = false;
        for(int j = 0; j < labels.size(); j++) {
            if(labels[j] == l) {
                counts[j]++;
                found = true;
                break;
            }
        }
        if(!found) {
            labels.push_back(l);
            counts.push_back(1);
        }
    }

    string bestLabel = "";
    int maxVotes = -1;

    for(int i = 0; i < labels.size(); i++) {
        if(counts[i] > maxVotes) {
            maxVotes = counts[i];
            bestLabel = labels[i];
        }
    }

    return bestLabel;
}
