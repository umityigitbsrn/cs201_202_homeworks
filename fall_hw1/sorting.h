/*
* Title: Algorithm Efficiency and Sorting
* Author: Umit Yigit Basaran
* ID: 21704103
* Section: 2
* Assignment: 1
* Description: The h. file of the sorting.cpp
* that contains sorting functions and performanceAnalysis
*/

#ifndef __SORTING_H
#define __SORTING_H

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <iomanip>

using namespace std;

void insertionSort(int *arr, int size, int &compCount, int &moveCount);

void quickSort(int *arr, int size, int &compCount, int &moveCount);

void mergeSort(int *arr, int size, int &compCount, int &moveCount);

void performanceAnalysis();

// extra functions
void quickSort(int* theArray, int first, int last, int& compCount, int& moveCount);
void partition(int* theArray, int first, int last, int& pivotIndex, int& compCount, int& moveCount);

void mergeSort(int* arr, int first, int last, int &compCount, int &moveCount);
void merge(int* arr, int first, int mid, int last, int &compCount, int &moveCount);

#endif // __SORTING_H
