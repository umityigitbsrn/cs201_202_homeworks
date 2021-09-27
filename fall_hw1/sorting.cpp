/*
* Title: Algorithm Efficiency and Sorting
* Author: Umit Yigit Basaran
* ID: 21704103
* Section: 2
* Assignment: 1
* Description: This code is contains different sorting algorithms functions
* and performance analysis function that shows the elapsed times, compCounts
* and moveCounts of each algorithm.
*/

#include "sorting.h"
#include "auxArrayFunctions.h"

void insertionSort(int* arr, int size, int& compCount, int& moveCount)
{
    for (int unsorted = 1; unsorted < size; ++unsorted)
    {

        int nextItem = arr[unsorted];
        int loc = unsorted;

        for (  ; (loc > 0) && (++compCount) && (arr[loc-1] > nextItem); --loc){
            arr[loc] = arr[loc-1];
            moveCount++;
        }

        arr[loc] = nextItem;
        moveCount += 2;
    }
}

void quickSort(int* arr, int size, int& compCount, int& moveCount)
{
    quickSort(arr, 0, size - 1, compCount, moveCount);
}

void quickSort(int* theArray, int first, int last, int& compCount, int& moveCount)
{
    int pivotIndex;

    if (first < last)
    {

        // create the partition: S1, pivot, S2
        partition(theArray, first, last, pivotIndex, compCount, moveCount);

        // sort regions S1 and S2
        quickSort(theArray, first, pivotIndex-1, compCount, moveCount);
        quickSort(theArray, pivotIndex+1, last, compCount, moveCount);
    }
}

void partition(int* theArray, int first, int last, int& pivotIndex, int& compCount, int& moveCount)
{

    int pivot = theArray[first]; // copy pivot
    moveCount++;
    // initially, everything but pivot is in unknown
    int lastS1 = first;           // index of last item in S1
    int firstUnknown = first + 1; // index of first item in unknown

    // move one item at a time until unknown region is empty
    for (  ; firstUnknown <= last; ++firstUnknown)
    {
        // Invariant: theArray[first+1..lastS1] < pivot
        //            theArray[lastS1+1..firstUnknown-1] >= pivot

        // move item from unknown to proper region
        if ((++compCount) && (theArray[firstUnknown] < pivot))    	// belongs to S1
        {
            ++lastS1;
            int tmp = theArray[firstUnknown];
            theArray[firstUnknown] = theArray[lastS1];
            theArray[lastS1] = tmp;
            moveCount += 3;
        }	// else belongs to S2
    }
    // place pivot in proper position and mark its location

    int tmp = theArray[first];
    theArray[first] = theArray[lastS1];
    theArray[lastS1] = tmp;
    moveCount += 3;
    pivotIndex = lastS1;
}

void mergeSort(int* arr, int size, int& compCount, int& moveCount)
{
    mergeSort(arr, 0, size - 1, compCount, moveCount);
}

void mergeSort(int* arr, int first, int last, int& compCount, int& moveCount)
{
    if (first < last)
    {

        int mid = (first + last)/2; 	// index of midpoint

        mergeSort(arr, first, mid, compCount, moveCount);

        mergeSort(arr, mid+1, last, compCount, moveCount);

        // merge the two halves
        merge(arr, first, mid, last, compCount, moveCount);
    }
}

void merge(int* arr, int first, int mid, int last, int& compCount, int& moveCount)
{
    int tempArray[150000]; 	// temporary array

    int first1 = first; 	// beginning of first subarray
    int last1 = mid; 		// end of first subarray
    int first2 = mid + 1;	// beginning of second subarray
    int last2 = last;		// end of second subarray
    int index = first1; // next available location in tempArray

    for ( ; (first1 <= last1) && (first2 <= last2); ++index)
    {
        if ((++compCount) && (arr[first1] < arr[first2]))
        {
            tempArray[index] = arr[first1];
            ++first1;
            moveCount++;
        }
        else
        {
            tempArray[index] = arr[first2];
            ++first2;
            moveCount++;
        }
    }

        // finish off the first subarray, if necessary
        for (; first1 <= last1; ++first1, ++index){
            tempArray[index] = arr[first1];
            moveCount++;
        }

        // finish off the second subarray, if necessary
        for (; first2 <= last2; ++first2, ++index){
            tempArray[index] = arr[first2];
            moveCount++;
        }

        // copy the result back into the original array
        for (index = first; index <= last; ++index){
            arr[index] = tempArray[index];
            moveCount++;
        }
}

void performanceAnalysis(){

    typedef std::chrono::high_resolution_clock Clock;
    using namespace std::chrono;
    int wInt = 20;

    double* durationArr = new double[18];
    int* compCountArr = new int[18];
    int* moveCountArr = new int[18];

    int* arr1, *arr2, *arr3;

    // RANDOM ARRAYS
    int index = 0;
    for (int i = 5000; i <= 30000; i += 5000, index++){

        int compCountI = 0;
        int compCountM = 0;
        int compCountQ = 0;

        int moveCountI = 0;
        int moveCountM = 0;
        int moveCountQ = 0;

        // creating three random dynamically allocated arrays
        createRandomArrays(arr1, arr2, arr3, i);

        // insertion sort
        Clock::time_point startTimeInsertion = Clock::now();
        insertionSort(arr1, i, compCountI, moveCountI);
        Clock::time_point endTimeInsertion = Clock::now();
        duration<double> timeSpanInsertion = duration_cast<duration<double>>(endTimeInsertion - startTimeInsertion);

        // merge sort
        Clock::time_point startTimeMerge = Clock::now();
        mergeSort(arr2, i, compCountM, moveCountM);
        Clock::time_point endTimeMerge = Clock::now();
        duration<double> timeSpanMerge = duration_cast<duration<double>>(endTimeMerge - startTimeMerge);

        // quick sort
        Clock::time_point startTimeQuick = Clock::now();
        quickSort(arr3, i, compCountQ, moveCountQ);
        Clock::time_point endTimeQuick = Clock::now();
        duration<double> timeSpanQuick = duration_cast<duration<double>>(endTimeQuick - startTimeQuick);

        durationArr[index] = timeSpanInsertion.count() * 1000;
        durationArr[index + 6] = timeSpanMerge.count() * 1000;
        durationArr[index + 12] = timeSpanQuick.count() * 1000;

        compCountArr[index] = compCountI;
        compCountArr[index + 6] = compCountM;
        compCountArr[index + 12] = compCountQ;

        moveCountArr[index] = moveCountI;
        moveCountArr[index + 6] = moveCountM;
        moveCountArr[index + 12] = moveCountQ;

        // delete the arrays
        delete []arr1;
        delete []arr2;
        delete []arr3;
    }

    //printing the table
    cout << "-------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Insertion Sort - RANDOM" << endl;
    cout << "Array Size" << setw(wInt - 1) << "Elapsed Time" << setw(wInt) << "compCount" << setw(wInt) << "moveCount" << endl;

    for (int i = 1; i <= 6; i++){
            if (i == 1)
                cout << i * 5000 << setw(wInt + 1) << durationArr[i - 1] << " ms" << setw(wInt)
                    << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
            else
                cout << i * 5000 << setw(wInt) << durationArr[i - 1] << " ms" << setw(wInt)
                    << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
    }

    cout << "-------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Merge Sort - RANDOM" << endl;
    cout << "Array Size" << setw(wInt - 1) << "Elapsed Time" << setw(wInt) << "compCount" << setw(wInt) << "moveCount" << endl;

    for (int i = 7; i <= 12; i++){
        if (i == 7)
            cout << (i - 6) * 5000 << setw(wInt + 1) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
        else
            cout << (i -6) * 5000 << setw(wInt) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
    }

    cout << "-------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Quick Sort - RANDOM" << endl;
    cout << "Array Size" << setw(wInt - 1) << "Elapsed Time" << setw(wInt) << "compCount" << setw(wInt) << "moveCount" << endl;

    for (int i = 13; i <= 18; i++){
        if (i == 13)
            cout << (i - 12) * 5000 << setw(wInt + 1) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
        else
            cout << (i - 12) * 5000 << setw(wInt) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
    }

    // ALREADY SORTED
    index = 0;
    for (int i = 5000; i <= 30000; i += 5000, index++){
        int compCountI = 0;
        int compCountM = 0;
        int compCountQ = 0;

        int moveCountI = 0;
        int moveCountM = 0;
        int moveCountQ = 0;

        // creating three sorted dynamically allocated arrays
        createAlreadySortedArrays(arr1, arr2, arr3, i);

        // insertion sort
        Clock::time_point startTimeInsertion = Clock::now();
        insertionSort(arr1, i, compCountI, moveCountI);
        Clock::time_point endTimeInsertion = Clock::now();
        duration<double> timeSpanInsertion = duration_cast<duration<double>>(endTimeInsertion - startTimeInsertion);

        // merge sort
        Clock::time_point startTimeMerge = Clock::now();
        mergeSort(arr2, i, compCountM, moveCountM);
        Clock::time_point endTimeMerge = Clock::now();
        duration<double> timeSpanMerge = duration_cast<duration<double>>(endTimeMerge - startTimeMerge);

        // quick sort
        Clock::time_point startTimeQuick = Clock::now();
        quickSort(arr3, i, compCountQ, moveCountQ);
        Clock::time_point endTimeQuick = Clock::now();
        duration<double> timeSpanQuick = duration_cast<duration<double>>(endTimeQuick - startTimeQuick);

        durationArr[index] = timeSpanInsertion.count() * 1000;
        durationArr[index + 6] = timeSpanMerge.count() * 1000;
        durationArr[index + 12] = timeSpanQuick.count() * 1000;

        compCountArr[index] = compCountI;
        compCountArr[index + 6] = compCountM;
        compCountArr[index + 12] = compCountQ;

        moveCountArr[index] = moveCountI;
        moveCountArr[index + 6] = moveCountM;
        moveCountArr[index + 12] = moveCountQ;

        // delete the arrays
        delete []arr1;
        delete []arr2;
        delete []arr3;
    }

    //printing the table
    cout << "-------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Insertion Sort - SORTED" << endl;
    cout << "Array Size" << setw(wInt - 1) << "Elapsed Time" << setw(wInt) << "compCount" << setw(wInt) << "moveCount" << endl;

    for (int i = 1; i <= 6; i++){
            if (i == 1)
                cout << i * 5000 << setw(wInt + 1) << durationArr[i - 1] << " ms" << setw(wInt)
                    << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
            else
                cout << i * 5000 << setw(wInt) << durationArr[i - 1] << " ms" << setw(wInt)
                    << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
    }

    cout << "-------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Merge Sort - SORTED" << endl;
    cout << "Array Size" << setw(wInt - 1) << "Elapsed Time" << setw(wInt) << "compCount" << setw(wInt) << "moveCount" << endl;

    for (int i = 7; i <= 12; i++){
        if (i == 7)
            cout << (i - 6) * 5000 << setw(wInt + 1) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
        else
            cout << (i - 6) * 5000 << setw(wInt) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
    }

    cout << "-------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Quick Sort - SORTED" << endl;
    cout << "Array Size" << setw(wInt - 1) << "Elapsed Time" << setw(wInt) << "compCount" << setw(wInt) << "moveCount" << endl;

    for (int i = 13; i <= 18; i++){
        if (i == 13)
            cout << (i - 12) * 5000 << setw(wInt + 1) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
        else
            cout << (i - 12) * 5000 << setw(wInt) << durationArr[i - 1] << " ms" << setw(wInt)
                << compCountArr[i - 1] << setw(wInt) << moveCountArr[i - 1] << endl;
    }

    // delete the arrays
    delete []durationArr;
    delete []compCountArr;
    delete []moveCountArr;
}


