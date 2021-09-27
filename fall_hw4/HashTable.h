/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 4
*/

#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <iostream>
using namespace std;

enum CollisionStrategy {LINEAR, QUADRATIC, DOUBLE};

class TableItem{
public:
    TableItem(int _item = 0){
        item = _item;
        tombStone = false;
    }
private:
    int item;
    bool tombStone;
    friend class HashTable;
};

class HashTable{
public:
    HashTable(const int tableSize, const CollisionStrategy option);
    ~HashTable();

    bool insert(const int item);
    bool remove(const int item);
    bool search(const int item, int& numProbes);
    void display();
    void analyze(double& numSuccProbes, double& numUnsuccProbes);
private:
    int hash(const int item);
    int function(const int item, const int prob);
    int secondHash(const int item);
    bool loopChecker(const int numProbes);

    int tableSize;
    int currentSize;
    TableItem** hashTable;
    CollisionStrategy option;
};
#endif // __HASH_TABLE_H
