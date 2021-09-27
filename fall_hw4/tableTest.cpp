/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 4
*/

#include "HashTable.h"
#include <fstream>
#include <string>

int main(){
    const CollisionStrategy collisionStrategy = LINEAR;
    const string fileName = "exampleLinear.txt";
    const int tableSize = 13;

    fstream file(fileName, ios_base::in);

    char operation;
    int item;

    HashTable hashTable(tableSize, collisionStrategy);

    while((file >> operation) && (file >> item)){
        if (operation == 'I'){
            if (hashTable.insert(item))
                cout << item << " inserted" << endl;
            else
                cout << item << " not inserted" << endl;
        }
        else if(operation == 'R'){
            if (hashTable.remove(item))
                cout << item << " removed" << endl;
            else
                cout << item << " not removed" << endl;
        }
        else if(operation == 'S'){
            int numProbes;
            if (hashTable.search(item, numProbes))
                cout << item << " found after " << numProbes << " probes" << endl;
            else
                cout << item << " not found after " << numProbes << " probes" << endl;
        }
        else
            cout << "TEXT FILE IS NOT APPROPRIATE" << endl;
    }

   hashTable.display();

    double avSucc;
    double avUnsucc;
    hashTable.analyze(avSucc, avUnsucc);

    cout << "Average Successful Search: " << avSucc << endl;
    cout << "Average Unsuccessful Search: " << avUnsucc << endl;

    return 0;
}
