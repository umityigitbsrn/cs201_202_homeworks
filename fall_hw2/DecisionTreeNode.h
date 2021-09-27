/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 2
*/

#ifndef __DECISION_TREE_NODE
#define __DECISION_TREE_NODE

#include <iostream>

class DecisionTreeNode{
private:
    DecisionTreeNode(const int& nodeItem = -1,
                     const bool& leaf = false,
                     DecisionTreeNode* left = NULL,
                     DecisionTreeNode* right = NULL);

    ~DecisionTreeNode();
    void setNodeItem(int nodeItem);
    bool isLeaf();

    bool leaf;
    int item; //if leaf then it should contain class number, otherwise it should contain featureId
    DecisionTreeNode* leftChildPtr;
    DecisionTreeNode* rightChildPtr;

    friend class DecisionTree;
};
#endif // __DECISION_TREE_NODE
