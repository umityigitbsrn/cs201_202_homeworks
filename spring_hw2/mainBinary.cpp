#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int binarySearch(int* arr, int arrSize, int key)
{
    int index = -1;
    time_point < system_clock > startTime;
    duration < double, milli > elapsedTime;
    startTime = system_clock::now();
    for (int i = 0; i < 10000000; i++) // in order to detail the execution time result
    {
        index = -1;
        int low = 0, high = arrSize - 1;
        while (low <= high && index == -1)
        {
            int mid = (low + high)/2;
            if (arr[mid] < key)
                low = mid + 1;
            else if (arr[mid] > key)
                high = mid - 1;
            else
            {
                index = mid;
            }
        }
    }
    elapsedTime = system_clock::now() - startTime;
    cout << "Execution Took: " << elapsedTime.count() << " milliseconds" << endl;
    // for creating the graphs it needs to be divided to 10000000
    return index;
}

int linearSearch(int* arr, int arrSize, int key)
{
    int index = -1;
    time_point < system_clock > startTime;
    duration < double, milli > elapsedTime;
    startTime = system_clock::now();
    for (int i = 0; i < 100000; i++) // in order to detail the execution time result
    {
        index = -1;
        for (int j = 0; j < arrSize && index == -1; j++)
        {
            if (arr[j] == key)
                index = j;
        }
    }
    elapsedTime = system_clock::now() - startTime;
    cout << "Execution Took: " << elapsedTime.count() << " milliseconds" << endl;
    // for creating the graphs it needs to be divided to 100000
    return index;
}

int main()
{
    //creating array - 101
    int* arrHun = new int[101];
    for (int i = 0; i < 101; i++)
        arrHun[i] = i;
    //creating array - 10001
    int* arrTenTho = new int[10001];
    for (int i = 0; i < 10001; i++)
        arrTenTho[i] = i;
    //creating array - 1000001
    int* arrMil = new int[1000001];
    for (int i = 0; i < 1000001; i++)
        arrMil[i] = i;
    //creating array - 1000000001
    int* arrBil = new int[10000001];
    for (int i = 0; i < 10000001; i++)
        arrBil[i] = i;
    /////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
    cout << endl;
    cout << "Sequential Search" << endl;
    //code block - 101 - close to beginning
    cout << "Array - 101" << endl;
    cout << "Begin" << endl;
    int found = linearSearch(arrHun, 101, 0);
    cout << found << endl;
    //close to the mid
    cout << "Mid" << endl;
    found = linearSearch(arrHun, 101, 50);
    cout << found << endl;
    //close to the end
    cout << "End" << endl;
    found = linearSearch(arrHun, 101, 101);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = linearSearch(arrHun, 101, -1);
    cout << found << endl;
    //////////////////////////////////////////////////////////////////////////
    //code block - 10001 - begin
    cout << "Array - 10001" << endl;
    cout << "Begin" << endl;
    found = linearSearch(arrTenTho, 10001, 0);
    cout << found << endl;
    //mid
    cout << "Mid" << endl;
    found = linearSearch(arrTenTho, 10001, 5000);
    cout << found << endl;
    //end
    cout << "End" << endl;
    found = linearSearch(arrTenTho, 10001, 10000);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = linearSearch(arrTenTho, 10001, 10001);
    cout << found << endl;
    ////////////////////////////////////////////////////////////////////////////
    //code block - 1000001 - begin
    cout << "Array - 1000001" << endl;
    cout << "Begin" << endl;
    found = linearSearch(arrMil, 1000001, 0);
    cout << found << endl;
    //mid
    cout << "Mid" << endl;
    found = linearSearch(arrMil, 1000001, 500000);
    cout << found << endl;
    //end
    cout << "End" << endl;
    found = linearSearch(arrMil, 1000001, 1000000);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = linearSearch(arrMil, 1000001, 1000001);
    cout << found << endl;
    ////////////////////////////////////////////////////////////////////////////
    //code block - 1000000001 - begin
    cout << "Array - 10000000" << endl;
    cout << "Begin" << endl;
    found = linearSearch(arrBil, 10000001, 0);
    cout << found << endl;
    //mid
    cout << "Mid" << endl;
    found = linearSearch(arrBil, 10000001, 5000000);
    cout << found << endl;
    //end
    cout << "End" << endl;
    found = linearSearch(arrBil, 10000001, 10000000);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = linearSearch(arrBil, 10000001, 10000001);
    cout << found << endl;
    /////////////////////////////////////////////////////////////////////////////
    cout << endl;
    cout << "Binary Search" << endl;
    //code block - 101 - close to beginning
    cout << "Array - 101" << endl;
    cout << "Begin" << endl;
    found = binarySearch(arrHun, 101, 0);
    cout << found << endl;
    //close to the mid
    cout << "Mid" << endl;
    found = binarySearch(arrHun, 101, 50);
    cout << found << endl;
    //close to the end
    cout << "End" << endl;
    found = binarySearch(arrHun, 101, 100);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = binarySearch(arrHun, 101, -1);
    cout << found << endl;
    ////////////////////////////////////////////////////////////////////////////
    //code block - 10001 - begin
    cout << "Array - 10001" << endl;
    cout << "Begin" << endl;
    found = binarySearch(arrTenTho, 10001, 0);
    cout << found << endl;
    //mid
    cout << "Mid" << endl;
    found = binarySearch(arrTenTho, 10001, 5000);
    cout << found << endl;
    //end
    cout << "End" << endl;
    found = binarySearch(arrTenTho, 10001, 10000);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = binarySearch(arrTenTho, 10001, -1);
    cout << found << endl;
    ////////////////////////////////////////////////////////////////////////////
    //code block - 1000001 - begin
    cout << "Array - 1000001" << endl;
    cout << "Begin" << endl;
    found = binarySearch(arrMil, 1000001, 0);
    cout << found << endl;
    //mid
    cout << "Mid" << endl;
    found = binarySearch(arrMil, 1000001, 500000);
    cout << found << endl;
    //end
    cout << "End" << endl;
    found = binarySearch(arrMil, 1000001, 1000000);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = binarySearch(arrMil, 1000001, -1);
    cout << found << endl;
    ////////////////////////////////////////////////////////////////////////////
    //code block - 10000001 - begin
    cout << "Array - 10000001" << endl;
    cout << "Begin" << endl;
    found = binarySearch(arrBil, 10000001, 0);
    cout << found << endl;
    //mid
    cout << "Mid" << endl;
    found = binarySearch(arrBil, 10000001, 5000000);
    cout << found << endl;
    //end
    cout << "End" << endl;
    found = binarySearch(arrBil, 10000001, 10000000);
    cout << found << endl;
    //not found
    cout << "Not Found" << endl;
    found = binarySearch(arrBil, 10000001, -1);
    cout << found << endl;
    ///////////////////////////////////////////////////////////////////////////
    // deleting array in order to prevent from memory leak
    delete []arrHun;
    delete []arrTenTho;
    delete []arrMil;
    delete []arrBil;
    return 0;
}
