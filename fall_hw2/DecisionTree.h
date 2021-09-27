/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 2
*/

#ifndef __DECISION_TREE
#define __DECISION_TREE

#include <iostream>
#include <tgmath.h>
#include <string>
#include <fstream>
#include "DecisionTreeNode.h"

using namespace std;

class DecisionTree{
public:
    DecisionTree();
    ~DecisionTree();
    void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
    void train(const string fileName, const int numSamples, const int numFeatures);
    int predict(const bool* data);
    double test(const bool** data, const int* labels, const int numSamples);
    double test(const string fileName, const int numSamples);
    void print();

private:
    DecisionTreeNode* root;
    void trainTree(const bool** data, const int* labels, const int numSamples,
                   const int numFeatures, DecisionTreeNode*& root, const bool* usedSamples, const bool* usedFeatures);
    int predictTree(const bool* data, DecisionTreeNode* root);
    void printTree(DecisionTreeNode* root, int stage);
    int tmpNumFeatures;
};

double calculateEntropy(const int* classCount, const int numClasses);

double calculateInformationGain(const bool** data, const int* labels, const int numSamples,
                                    const int numFeatures, const bool* usedSamples,
                                    const int featureId);

// helper functions for calculateInformationGain function
double calculateHP(const int* labels, const int numSamples, const bool* usedSamples, int numClasses);

void retrieveSizeLeftRight(const bool** data, const int numSamples, const bool* usedSamples,
                           const int featureId, int& leftSize, int& rightSize);

void calculateLeftRight(const int* leftChild, const int leftSize,
                        const int* rightChild, const int rightSize,
                        double& hLeft, double& hRight, int numClasses);

#endif // __DECISION_TREE
