/*
 * Title: Homework - 3
 * Author: Umit Yigit Basaran
 * ID: 21704103
 * Section: 2
 * Assignment: 3
 * Description: maxHeap1 header file - [Heap and Heap Item classes]
 */

#ifndef __MAX_HEAP_1_H
#define __MAX_HEAP_1_H

#include <iostream>

using namespace std;
const int MAX_HEAP = 2000;

class HeapItem{
public:
    //constructors and destructors
    HeapItem(int idCpy = 0, int priorityCpy = 0,
             int arrivalTimeCpy = 0, int execTimeCpy = 0);
    ~HeapItem();
    HeapItem(const HeapItem& cpyItem);

    //get and set methods
    int getId();
    double getPriority();
    int getArrivalTime();
    int getExecTime();

    void setId(int setId);
    void setPriority(int setPriority);
    void setArrivalTime(int setArrivalTime);
    void setExecTime(int setExecTime);

    // helper functions - these can be erased
    void printHeapItem();
    void operator=(const HeapItem& rhs);

private:
    int id;
    int priority;
    int arrivalTime;
    int execTime;
    friend class Heap;
};

class Heap{
public:
    Heap(); //default constructor

    bool heapIsEmpty() const;
    void heapInsert(const HeapItem& newItem);
    void heapDelete(HeapItem& rootItem);

    // helper functions - these can be erased
    void printHeap();

protected:
    void heapRebuild(int root);

private:
    HeapItem items[MAX_HEAP];
    int size;
};

#include "simulator.cpp"
#endif // __MAX_HEAP_1_H
