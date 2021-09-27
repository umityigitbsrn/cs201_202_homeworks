/*
 * Title: Homework - 3
 * Author: Umit Yigit Basaran
 * ID: 21704103
 * Section: 2
 * Assignment: 3
 * Description: main [simulator] file of the project
 */

#include <string>
#include <fstream>

double simulate(const string fileName, const int numDoctors, int*& doctorPrint,
                int*& patientPrint, int*& startTime, int*& waitingTime){
    fstream file(fileName, ios_base::in);

    int numSamples;
    file >> numSamples;

    int indexSamples = 0;
    Heap priorityQueue;

    // to check availability
    int generalTime = 0;
    int doctorsTime[numDoctors];
    for (int i = 0; i < numDoctors; i++)
        doctorsTime[i] = 0;

    int printIndex = 0; //hold the index of the below arrays

    int id;
    int priority;
    int arrivalTime;
    int execTime;

    file >> id;
    file >> priority;
    file >> arrivalTime;
    file >> execTime;
    while(indexSamples < numSamples || !priorityQueue.heapIsEmpty()){
        while (arrivalTime <= generalTime && indexSamples < numSamples){
            //cout << indexSamples << endl;
            HeapItem patient(id, priority, arrivalTime, execTime);
            priorityQueue.heapInsert(patient);
            file >> id;
            file >> priority;
            file >> arrivalTime;
            file >> execTime;
            indexSamples++;
        }

        for (int i = 0; i < numDoctors && !priorityQueue.heapIsEmpty(); i++){
            if (doctorsTime[i] <= generalTime){
                HeapItem rootItem;
                priorityQueue.heapDelete(rootItem);
                doctorsTime[i] = generalTime + rootItem.getExecTime();
                doctorPrint[printIndex] = i;
                patientPrint[printIndex] = rootItem.getId();
                startTime[printIndex] = generalTime;
                waitingTime[printIndex] = generalTime - rootItem.getArrivalTime();
                printIndex++;
            }
        }

        generalTime++;
    }

    int totalWaitingTime = 0;
    for (int i = 0; i < printIndex; i++)
        totalWaitingTime += waitingTime[i];
    return (double) totalWaitingTime/numSamples;
}

int getNumSamples(const string fileName){
    fstream file(fileName, ios_base::in);
    int result;
    file >> result;
    return result;
}

int main(int argc, char* argv[]){
    if (argc == 3){
        // taking parameters from arguements
        string fileName = argv[1];
        string stringAvTime = argv[2];
        int avTime = 0;
        for (int i = 0; i < stringAvTime.length(); i++){
            int tmpChar = stringAvTime[stringAvTime.length() - i - 1] - '0';
            for (int j = 0; j < i; j++)
                tmpChar *= 10;
            avTime += tmpChar;
        }

        int numSamples = getNumSamples(fileName);
        if (numSamples > 0){
            // To print the correct variables after calculation
            int* doctorPrint = new int[numSamples];
            int* patientPrint = new int[numSamples];
            int* startTime = new int[numSamples];

            // to calculate the average waiting time and print
            int* waitingTime = new int[numSamples];

            int minDoc = 1;
            double tmpTime = avTime + 1;
            while(tmpTime > avTime){
                tmpTime = simulate(fileName, minDoc, doctorPrint, patientPrint, startTime, waitingTime);
                minDoc++;
            }

            cout << "Minimum Number of doctors required: " << minDoc - 1 << endl;

            cout << "Simulation with " << minDoc - 1 << " doctors:" << endl;

            for (int i = 0; i < numSamples; i++){
                cout << "Doctor " << doctorPrint[i] << " takes patient " <<
                    patientPrint[i] << " at minute " << startTime[i] << " (wait: "
                    << waitingTime[i] << " mins)" << endl;
            }

            cout << "Average waiting time: " << tmpTime << endl;
            delete[] doctorPrint;
            delete[] patientPrint;
            delete[] startTime;
            delete[] waitingTime;
        }
        else{
            cout << "Number of samples is inappropriate." << endl;
        }
    }
    else{
        cout << "Please run program appropriately." << endl;
    }
}
