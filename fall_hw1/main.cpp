/*
* Title: Algorithm Efficiency and Sorting
* Author: Umit Yigit Basaran
* ID: 21704103
* Section: 2
* Assignment: 1
* Description: The main function of the code it sorts
* the given array and shows the compCount and moveCount numbers.
*/

#include "sorting.h"
#include "auxArrayFunctions.h"

int main(){
    int arr1[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};
    int arr2[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};
    int arr3[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};
    int size = 16;

    int compCountQ = 0;
    int moveCountQ = 0;

    int compCountM = 0;
    int moveCountM = 0;

    int compCountI = 0;
    int moveCountI = 0;

    // quick sort
    cout << "Quick Sort" << endl;
    quickSort(arr1, size, compCountQ, moveCountQ);
    displayArray(arr1, size);
    cout << "compCountQ: " << compCountQ << endl;
    cout << "moveCountQ: " << moveCountQ << endl;

    // merge sort
    cout << endl;
    cout << "Merge Sort" << endl;
    mergeSort(arr2, size, compCountM, moveCountM);
    displayArray(arr2, size);
    cout << "compCountM: " << compCountM << endl;
    cout << "moveCountM: " << moveCountM << endl;

    // insertion sort
    cout << endl;
    cout << "Insertion Sort" << endl;
    insertionSort(arr3, size, compCountI, moveCountI);
    displayArray(arr3, size);
    cout << "compCountI: " << compCountI << endl;
    cout << "moveCountI: " << moveCountI << endl;

    return 0;
//performanceAnalysis();
//return 0;
}
