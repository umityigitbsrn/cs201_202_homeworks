/*
 * Title: Homework - 3
 * Author: Umit Yigit Basaran
 * ID: 21704103
 * Section: 2
 * Assignment: 3
 * Description: maxHeap2 header file - [Heap and Heap Item classes]
 */

#ifndef __MAH_HEAP_2_H
#define __MAH_HEAP_2_H

#include <iostream>
using namespace std;

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
    ~Heap();
    Heap(const Heap& cpyHeap);


    bool heapIsEmpty() const;
    void heapInsert(const HeapItem& newItem);
    void heapDelete(HeapItem& rootItem);

    // helper functions - these can be erased
    void printHeap();
    void operator=(const Heap& rhs);
    int getSpace();

protected:
    void heapRebuild(int root);

private:
    HeapItem* items;
    int size;
    int space;
};

#include "simulator.cpp"
#endif // __MAH_HEAP_2_H
