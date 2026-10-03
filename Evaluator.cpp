#include "Evaluator.h"

using namespace std;

double Evaluator::calculateAccuracy(DataSet testData, KNNClassifier& classifier) {
    if(testData.size() == 0) return 0.0;

    int correct = 0;
    for(int i = 1; i <= testData.size(); i++) {
        DataPoint pt = testData.getPoint(i);
        string predicted = classifier.predict(pt);
        if(predicted == pt.getLabel()) {
            correct++;
        }
    }
    return (double)correct / testData.size();
}
