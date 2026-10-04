#include "KNNClassifier.h"
#include <vector>
#include <algorithm>
#include <map>

struct Neighbor {
    double distance;
    std::string label;
};

KNNClassifier::KNNClassifier(int k, IDistance* distanceMetric, bool weighted)
    : k(k), distanceMetric(distanceMetric), weighted(weighted) {}

void KNNClassifier::fit(const DataSet& data) {
    trainingData = data;
}

std::string KNNClassifier::predict(const DataPoint& point) const {
    if (trainingData.size() == 0) return "Unknown";

    std::vector<Neighbor> neighbors;
    for (size_t i = 0; i < trainingData.size(); ++i) {
        const DataPoint& trainPoint = trainingData.getPoint(i);
        double dist = distanceMetric->calculate(point, trainPoint);
        neighbors.push_back({dist, trainPoint.getLabel()});
    }

    // Sort neighbors by distance ascending
    std::sort(neighbors.begin(), neighbors.end(), [](const Neighbor& a, const Neighbor& b) {
        return a.distance < b.distance;
    });

    int actualK = std::min(k, static_cast<int>(neighbors.size()));

    if (!weighted) {
        std::map<std::string, int> votes;
        for (int i = 0; i < actualK; ++i) {
            votes[neighbors[i].label]++;
        }

        std::string bestLabel;
        int maxVotes = -1;
        for (const auto& pair : votes) {
            if (pair.second > maxVotes) {
                maxVotes = pair.second;
                bestLabel = pair.first;
            }
        }
        return bestLabel;
    } else {
        std::map<std::string, double> weightedVotes;
        for (int i = 0; i < actualK; ++i) {
            double weight = 1.0 / (neighbors[i].distance + 0.000000001);
            weightedVotes[neighbors[i].label] += weight;
        }

        std::string bestLabel;
        double maxWeight = -1.0;
        for (const auto& pair : weightedVotes) {
            if (pair.second > maxWeight) {
                maxWeight = pair.second;
                bestLabel = pair.first;
            }
        }
        return bestLabel;
    }
}
