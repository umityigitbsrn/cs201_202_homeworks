/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 4
*/

#include "HashTable.h"

HashTable::HashTable(const int tableSize, const CollisionStrategy option){
    this->tableSize = tableSize;
    currentSize = 0;
    hashTable = new TableItem*[tableSize];

    for (int i = 0; i < tableSize; i++)
        hashTable[i] = NULL;
    this->option = option;
}

HashTable::~HashTable(){
    for (int i = 0; i < tableSize; i++){
        if (hashTable[i] != NULL)
            delete hashTable[i];
    }

    delete []hashTable;
}

int HashTable::hash(const int item){return item % tableSize;}

int HashTable::secondHash(const int item){
    int tmp = item;
    int reverse = 0;
    int remain;
    while(tmp != 0){
        remain = tmp % 10;
        reverse = reverse * 10 + remain;
        tmp = tmp / 10;
    }
    return reverse;
}

int HashTable::function(const int item, const int prob){
    if (option == LINEAR){
        return prob;
    }
    else if (option == QUADRATIC){
        return prob * prob;
    }
    else if (option == DOUBLE){
        return prob * secondHash(item);
    }
    return -1;
}

bool HashTable::loopChecker(const int numProbes){
    if (option == LINEAR){
        if (numProbes == tableSize)
            return true;
        else
            return false;
    }
    else if (option == DOUBLE){
        if (numProbes == tableSize)
            return true;
        else
            return false;
    }
    else if(option == QUADRATIC){
        if (numProbes == ((tableSize/2) + 1))
            return true;
        else
            return false;
    }
    return false;
}

bool HashTable::insert(const int item){
    int numProbes;
    if (!(search(item, numProbes))){
        if (currentSize != tableSize){
            int calculatedIndex = hash(item);
            numProbes = 0;
            bool inserted = false;

            // If inserted before
            bool found = false;
            if (hashTable[calculatedIndex] != NULL &&
                !(hashTable[calculatedIndex]->tombStone))
                found = (hashTable[calculatedIndex]->item == item);

            bool loop = loopChecker(numProbes); //loop checker

            while((hashTable[calculatedIndex] != NULL &&
                  !(hashTable[calculatedIndex]->tombStone)) && !found && !loop){
                numProbes++;
                calculatedIndex = (hash(item) + function(item, numProbes)) % tableSize;

                loop = loopChecker(numProbes);

                if (hashTable[calculatedIndex] != NULL &&
                    !(hashTable[calculatedIndex]->tombStone))
                    found = (hashTable[calculatedIndex]->item == item);
            }

            if (!found && !loop){
                if ((hashTable[calculatedIndex] == NULL)){
                    TableItem* newItem = new TableItem(item);
                    hashTable[calculatedIndex] = newItem;
                }
                else if((hashTable[calculatedIndex]->tombStone)){
                    hashTable[calculatedIndex]->item = item;
                    hashTable[calculatedIndex]->tombStone = false;
                }

                currentSize++;
                inserted = true;
            }

            if (loop)
                cout << "BEAUSE OF LOOP" << endl;

            return inserted;
        }
        else
            return false;
    }
    else
        return false;
}

bool HashTable::remove(const int item){
    if (currentSize != 0){
        int calculatedIndex = hash(item);
        int numProbes = 0;
        bool removed = false;

        bool found = false;
        if (hashTable[calculatedIndex] != NULL)
            found = hashTable[calculatedIndex]->item == item &&
                !(hashTable[calculatedIndex]->tombStone);

        bool loop = loopChecker(numProbes); //loop checker

        while((hashTable[calculatedIndex] != NULL && !found && !loop)){
            numProbes++;
            calculatedIndex = (hash(item) + function(item, numProbes)) % tableSize;

            loop = loopChecker(numProbes); //loop checker

            if (hashTable[calculatedIndex] != NULL)
                found = hashTable[calculatedIndex]->item == item &&
                    !(hashTable[calculatedIndex]->tombStone);
        }

        if (found){
            hashTable[calculatedIndex]->tombStone = true;
            currentSize--;
            removed = true;
        }
        return removed;
    }
    else
        return false;
}

bool HashTable::search(const int item, int& numProbes){
    numProbes = 0;
    if (currentSize != 0){
        int calculatedIndex = hash(item);

        bool found = false;
        if (hashTable[calculatedIndex] != NULL)
            found = hashTable[calculatedIndex]->item == item &&
                !(hashTable[calculatedIndex]->tombStone);

        bool loop = loopChecker(numProbes); //loop checker

        while((hashTable[calculatedIndex] != NULL && !found && !loop)){
            numProbes++;
            calculatedIndex = (hash(item) + function(item, numProbes)) % tableSize;

            loop = loopChecker(numProbes); //loop checker

            if (hashTable[calculatedIndex] != NULL)
                found = hashTable[calculatedIndex]->item == item &&
                    !(hashTable[calculatedIndex]->tombStone);
        }

        if (!loop)
            numProbes++;

        return found;
    }
    else
        return false;
}

void HashTable::analyze(double& numSuccProbes, double& numUnsuccProbes){
    int tmpArr[currentSize];
    int tmpIndex = 0;

    //SUCCESSFULL SEARCH
    for (int i = 0; i < tableSize; i++){
        if (hashTable[i] != NULL && !(hashTable[i]->tombStone)){
            tmpArr[tmpIndex] = hashTable[i]->item;
            tmpIndex++;
        }
    }

    int totNumSuccProbes = 0;

    for (int i = 0; i < currentSize; i++){
        int tmpNumProbes = 0;
        search(tmpArr[i], tmpNumProbes);
        totNumSuccProbes += tmpNumProbes;
    }

    numSuccProbes = ((double) totNumSuccProbes / (double) currentSize);

    //UNSUCCESSFUL SEARCH
    if (option != DOUBLE){
        int totNumUnsuccProbes = 0;

        for (int i = 0; i < tableSize; i++){
            int tmpNumProbes;
            int sameIndex = i;
            while(search(sameIndex, tmpNumProbes))
                sameIndex += tableSize;

            totNumUnsuccProbes += tmpNumProbes;
        }

        numUnsuccProbes = ((double) totNumUnsuccProbes / (double) tableSize);
    }
    else{
        numUnsuccProbes = -1;
    }
}

void HashTable::display(){
    cout << "========================================" << endl;
    for (int i = 0; i < tableSize; i++){
        cout << i << ": ";
        if (hashTable[i] != NULL && !(hashTable[i]->tombStone))
            cout << hashTable[i]->item;

        cout << endl;
    }
    cout << "========================================" << endl;
}
