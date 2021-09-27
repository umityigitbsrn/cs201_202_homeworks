/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 2
*/

#include "DecisionTree.h"

DecisionTree::DecisionTree(){
    root = NULL;
}

DecisionTree::~DecisionTree(){
    if (root != NULL)
        delete root;
}

double calculateEntropy(const int* classCount, const int numClasses){
    double sum = 0.0;
    double result = 0.0;

    // find the total sum to get sample space
    for (int i = 0; i < numClasses; i++){
        sum += classCount[i];
    }

    // check all array items iteratively and make the calculation
    // -(sum i = 0 to numClasses(PilogPi))
    for (int i = 0; i < numClasses && sum != 0; i++){
        if (classCount[i] != 0)
            result += ((classCount[i]/sum) * log2(classCount[i]/sum));
    }
    return (-1 * result);
}

double calculateInformationGain(const bool** data, const int* labels, const int numSamples,
                                const int numFeatures, const bool* usedSamples,
                                const int featureId){
    /* numSamples(rows), numFeatures(columns), labels(vector of length numSamples)
       usedSamples(vector of length numSamples) whose values are true are in the subset
       that is used for the decision at that particular node
       featureId(column id between 0 and numFeatures-1) */

    // IG(P,S) = H(P) - H(S)
    // H(S) = pLeftH(Left) + pRightH(Right)
    double hP;
    double hS;
    double pLeft;
    double pRight;
    double hLeft;
    double hRight;

    int leftSize = 0;
    int rightSize = 0;
    int valueOfMaximumClass = 0;

    // in order to find the maximum class value
    for (int i = 0; i < numSamples; i++){
        if (labels[i] > valueOfMaximumClass)
            valueOfMaximumClass = labels[i];
    }

    // calculating H(P)
    hP = calculateHP(labels, numSamples, usedSamples, valueOfMaximumClass);

    // retrieving the size of the left and right child
    retrieveSizeLeftRight(data, numSamples, usedSamples, featureId, leftSize, rightSize);

    // with using leftSize and rightSize calculating the probabilities
    pLeft = (double) leftSize / (leftSize + rightSize);
    pRight = (double) rightSize / (leftSize + rightSize);

    // create left and right child respect to given featureId
    int* leftChild = new int[leftSize];
    int* rightChild = new int[rightSize];

    // partitioning the datas with the given featureId
    int indexLeft = 0;
    int indexRight = 0;
    for (int i = 0; i < numSamples; i++){
        if (!usedSamples[i]){
            if (data[i][featureId]){
                leftChild[indexLeft] = labels[i];
                indexLeft++;
            }
            else{
                rightChild[indexRight] = labels[i];
                indexRight++;
            }
        }
    }

    // calculating hLeft and hRight
    calculateLeftRight(leftChild, leftSize, rightChild, rightSize, hLeft, hRight, valueOfMaximumClass);
    delete []leftChild;
    delete []rightChild;

    // calculating hS
    hS = (pLeft * hLeft) + (pRight * hRight);

    // returning the result of information gain
//    cout << "HP: " << hP << endl;
//    cout << "HS: " << hS << endl;
//    cout << "pLeft: " << pLeft << endl;
//    cout << "pRight: " << pRight << endl;
//    cout << "hLeft: " << hLeft << endl;
//    cout << "hRight: " << hRight << endl;
//    cout << "IG: " << hP - hS  << "\n" << endl;
    return (hP - hS);
}

double calculateHP(const int* labels, const int numSamples, const bool* usedSamples, int numClasses){
    int* classCount;

    // creating the classCount array for calculation
    classCount = new int[numClasses];
    for (int i = 0; i < numClasses; i++){
        classCount[i] = 0;
    }

    for (int i = 0; i < numSamples; i++){
        if (!usedSamples[i])
            classCount[labels[i] - 1]++;
    }

    double result = calculateEntropy(classCount, numClasses);
    delete []classCount;
    return result;
}

void retrieveSizeLeftRight(const bool** data, const int numSamples, const bool* usedSamples,
                           const int featureId, int& leftSize, int& rightSize){
    for (int i = 0; i < numSamples; i++){
        if (!usedSamples[i]){
            if (data[i][featureId])
                leftSize++;
            else
                rightSize++;
        }
    }
}

void calculateLeftRight(const int* leftChild, const int leftSize,
                        const int* rightChild, const int rightSize,
                        double& hLeft, double& hRight, int numClasses){

    int classCountLeft[numClasses];
    for (int i = 0; i < numClasses; i++)
        classCountLeft[i] = 0;

    int classCountRight[numClasses];
    for (int i = 0; i < numClasses; i++)
        classCountRight[i] = 0;

    for (int i = 0; i < leftSize; i++)
        classCountLeft[leftChild[i] - 1]++;


    for (int i = 0; i < rightSize; i++)
        classCountRight[rightChild[i] - 1]++;

    // calculating left and right entropy values
    hLeft = calculateEntropy(classCountLeft, numClasses);
    hRight = calculateEntropy(classCountRight, numClasses);
}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples,
                         const int numFeatures){
    tmpNumFeatures = numFeatures;
    bool usedSamples[numSamples];
    bool usedFeatures[numFeatures];

    for (int i = 0; i < numSamples; i++)
        usedSamples[i] = false;

    for (int i = 0; i < numFeatures; i++)
        usedFeatures[i] = false;

    trainTree(data, labels, numSamples, numFeatures, root, usedSamples, usedFeatures);
}

void DecisionTree::trainTree(const bool** data, const int* labels, const int numSamples,
                             const int numFeatures, DecisionTreeNode*& root,
                             const bool* usedSamples, const bool* usedFeatures){
    if (root == NULL){

        int bestFeatureId = 0;
        double maxIG = -1.0; // for initialize with the non-possible value

        for (int i = 0; i < numFeatures; i++){
            if(!usedFeatures[i]){
                double IG = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, i);
                //cout << "IG: " << IG << endl;
                if (IG >= maxIG){
                    maxIG = IG;
                    bestFeatureId = i;
                }
            }
        } // finding best feature ID for the split

        //cout << "Feature ID: " << bestFeatureId << endl;
        if (maxIG > 0){ // not leaf
            bool leaf = false;
            root = new DecisionTreeNode(bestFeatureId, leaf);
        }
        else if (maxIG == 0){ // leaf
            bool leaf = true;
            root = new DecisionTreeNode(-1, leaf);

            int maxValTmp = 0;
            for (int i = 0; i < numSamples; i++){
                if (labels[i] > maxValTmp)
                    maxValTmp = labels[i];
            }

            int classCountTmp[maxValTmp];
            for (int i = 0; i < maxValTmp; i++)
                classCountTmp[i] = 0;

            for (int i = 0; i < numSamples; i++){
                if (!usedSamples[i])
                    classCountTmp[labels[i] - 1]++;
            }

            int mod = 0;
            int maxID = 0;
            for (int i = 0; i < maxValTmp; i++){
                if (classCountTmp[i] > mod){
                    mod = classCountTmp[i];
                    maxID = i;
                }
            }

            (*root).setNodeItem(maxID + 1);
        }

        bool usedSamplesLeft[numSamples];
        bool usedSamplesRight[numSamples];

        bool usedFeaturesTmp[numFeatures];

        for (int i = 0; i < numSamples; i++){
            if (!usedSamples[i]){
                if (data[i][bestFeatureId]){
                    usedSamplesLeft[i] = false;
                    usedSamplesRight[i] = true;
                }
                else{
                    usedSamplesLeft[i] = true;
                    usedSamplesRight[i] = false;
                }
            }
            else{
                usedSamplesLeft[i] = true;
                usedSamplesRight[i] = true;
            }
        }

        for (int i = 0; i < numFeatures; i++){
            if (i == bestFeatureId)
                usedFeaturesTmp[i] = true;
            else
                usedFeaturesTmp[i] = false;
        }

//        for (int i = 0; i < numFeatures; i++)
//            cout << usedFeaturesTmp[i] << " ";
//        cout << endl;

        if (!(*root).isLeaf()){
            trainTree(data, labels, numSamples, numFeatures, root->leftChildPtr, usedSamplesLeft, usedFeaturesTmp);
            trainTree(data, labels, numSamples, numFeatures, root->rightChildPtr, usedSamplesRight, usedFeaturesTmp);
        } // by using recursion creating all the possible nodes in the tree
    }
}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures){
    int* labels = new int[numSamples];
    bool** data = new bool*[numSamples];

    for (int i = 0; i < numSamples; i++)
        data[i] = new bool[numFeatures];

    fstream file(fileName, ios_base::in);

    int value;
    int xIndex = 0;
    int yIndex = 0;
    while(file >> value){
        if (xIndex < numSamples){
            if (yIndex < numFeatures){
                data[xIndex][yIndex] = value;
//                cout << "yIndex: " << yIndex << " xIndex: " << xIndex << endl;
//                cout << "value " << value << endl;
                yIndex++;
            }
            else{
                labels[xIndex] = value;
                yIndex = 0;
                xIndex++;
            }
        }
    }
//
//    for (int i = 0; i < numSamples; i++){
//        for (int j = 0; j < numFeatures; j++)
//            cout << data[i][j] << " ";
//        cout << labels[i] << endl;
//    }

    train((const bool**) data, labels, numSamples, numFeatures);

    for (int i = 0; i < numSamples; i++)
        delete[] data[i];

    delete[] data;

    delete[] labels;
}

int DecisionTree::predict(const bool* data){
    return predictTree(data, root);
}

int DecisionTree::predictTree(const bool* data, DecisionTreeNode* root){
    if ((*root).isLeaf())
        return root->item;

    if (data[(root->item)])
        predictTree(data, root->leftChildPtr);
    else
        predictTree(data, root->rightChildPtr);
}


double DecisionTree::test(const bool** data, const int* labels, const int numSamples){
    int truePrediction = 0;

    for (int i = 0; i < numSamples; i++){
        const bool* dataSample = data[i];
        int prediction = predict(dataSample);

        if (prediction == labels[i])
            truePrediction++;
    }

    return (double)truePrediction/numSamples;
}

double DecisionTree::test(const string fileName, const int numSamples){
    int* labels = new int[numSamples];
    bool** data = new bool*[numSamples];
    int numFeatures = tmpNumFeatures;

    for (int i = 0; i < numSamples; i++)
        data[i] = new bool[numFeatures];

    fstream file(fileName, ios_base::in);

    int value;
    int xIndex = 0;
    int yIndex = 0;
    while(file >> value){
        if (xIndex < numSamples){
            if (yIndex < numFeatures){
                data[xIndex][yIndex] = value;
//                cout << "yIndex: " << yIndex << " xIndex: " << xIndex << endl;
//                cout << "value " << value << endl;
                yIndex++;
            }
            else{
                labels[xIndex] = value;
                yIndex = 0;
                xIndex++;
            }
        }
    }

//    for (int i = 0; i < numSamples; i++){
//        for (int j = 0; j < numFeatures; j++)
//            cout << data[i][j] << " ";
//        cout << labels[i] << endl;
//    }

    double result = test((const bool**) data, labels, numSamples);

    for (int i = 0; i < numSamples; i++)
        delete[] data[i];

    delete[] data;
    delete[] labels;

    return result;
}

void DecisionTree::print(){
    cout << "=============TREE - LEFT==============" << endl;
    printTree(root, 0);
    cout << "=============TREE - RIGHT==================" << endl;
}

void DecisionTree::printTree(DecisionTreeNode* root, int stage){
    if (root == NULL)
        return;

    for (int i = 0; i < stage; i++)
        cout << '\t';

    if ((*root).isLeaf())
        cout << "class = ";

    cout << root->item << endl;
    printTree(root->leftChildPtr, stage+1);
    printTree(root->rightChildPtr, stage + 1);
}


