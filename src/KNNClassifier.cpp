#include "KNNClassifier.h"
#include "EuclideanDistance.h"
#include "ManhattanDistance.h"
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Neighbor {
    double distance;
    string label;
};

bool compareNeighbors(Neighbor n1, Neighbor n2) {
    return n1.distance < n2.distance;
}

KNNClassifier::KNNClassifier(int kValue) {
    k = kValue;
    metric = make_unique<EuclideanDistance>();
}

void KNNClassifier::setDistanceType(string type) {
    if (type == "manhattan") {
        metric = make_unique<ManhattanDistance>();
    } else {
        metric = make_unique<EuclideanDistance>();
    }
}

void KNNClassifier::setK(int kValue) {
    k = kValue;
}

void KNNClassifier::fit(DataSet data) {
    trainingData = data;
}

string KNNClassifier::predict(DataPoint point) {
    vector<Neighbor> neighbors;

    for(int i = 1; i <= trainingData.size(); i++) {
        DataPoint trainPoint = trainingData.getPoint(i);
        double dist = metric->calculate(point, trainPoint);

        Neighbor n;
        n.distance = dist;
        n.label = trainPoint.getLabel();
        neighbors.push_back(n);
    }

    sort(neighbors.begin(), neighbors.end(), compareNeighbors);

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
