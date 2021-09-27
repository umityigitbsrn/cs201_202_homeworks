/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 2
*/

#include "DecisionTreeNode.h"

DecisionTreeNode::DecisionTreeNode(const int& nodeItem,
                                    const bool& leaf,
                                    DecisionTreeNode* left, DecisionTreeNode* right){
    item = nodeItem;
    this->leaf = leaf;
    leftChildPtr = left;
    rightChildPtr = right;
}

DecisionTreeNode::~DecisionTreeNode(){
    if (leftChildPtr != NULL)
        delete leftChildPtr;

    if (rightChildPtr != NULL)
        delete rightChildPtr;
}
void DecisionTreeNode::setNodeItem(int nodeItem){
    item = nodeItem;
}

bool DecisionTreeNode::isLeaf(){
    return leaf;
}
