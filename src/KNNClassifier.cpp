#include "KNNClassifier.h"
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Neighbor {
    double distance;
    string label;
};

KNNClassifier::KNNClassifier(int k, IDistance* distanceMetric, bool weighted) {
    this->k = k;
    this->distanceMetric = distanceMetric;
    this->weighted = weighted;
}

void KNNClassifier::fit(DataSet data) {
    trainingData = data;
}

string KNNClassifier::predict(DataPoint point) {
    vector<Neighbor> neighbors;
    for (int i = 0; i < trainingData.size(); i++) {
        DataPoint trainPoint = trainingData.getPoint(i);
        double dist = distanceMetric->calculate(point, trainPoint);
        Neighbor nb;
        nb.distance = dist;
        nb.label = trainPoint.getLabel();
        neighbors.push_back(nb);
    }

    sort(neighbors.begin(), neighbors.end(), [](Neighbor a, Neighbor b) {
        return a.distance < b.distance;
    });

    int actualK = k;
    if (actualK > neighbors.size()) actualK = neighbors.size();

    if (!weighted) {
        map<string, int> votes;
        for (int i = 0; i < actualK; i++) {
            votes[neighbors[i].label]++;
        }
        string bestLabel;
        int maxVotes = -1;
        for (auto pair : votes) {
            if (pair.second > maxVotes) {
                maxVotes = pair.second;
                bestLabel = pair.first;
            }
        }
        return bestLabel;
    } else {
        map<string, double> weightedVotes;
        for (int i = 0; i < actualK; i++) {
            double weight = 1.0 / (neighbors[i].distance + 0.000001);
            weightedVotes[neighbors[i].label] += weight;
        }
        string bestLabel;
        double maxWeight = -1.0;
        for (auto pair : weightedVotes) {
            if (pair.second > maxWeight) {
                maxWeight = pair.second;
                bestLabel = pair.first;
            }
        }
        return bestLabel;
    }
}
