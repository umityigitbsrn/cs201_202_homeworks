/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 5
*/

#ifndef __FRIENDNET_H_
#define __FRIENDNET_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Person{
public:
    Person(const int _id = 0, const string _name = "", const int _degree = 0);
    //~Person();

    void operator=(const Person& rhs);
    int getID();
    string getName();
    int getDegree();
    void setID(const int _id);
    void setName(const string _name);
    void setDegree(const int _degree);
    void printPerson();
private:
    int id;
    string name;
    int degree;
};

class List{
public:
    List();
    ~List();

    void insert(const int _id = 0);
    void setPerson(const int _id, const string _name, const int _degree);
    //bool remove(const int _id);
    bool retrieve(int index, Person& personCpy) const;
    int getLength() const;
    void printList();
private:
    struct PersonNode{
        Person person;
        PersonNode* next;
    };

    PersonNode* head;
    int listSize;
};

class Queue{
public:
    Queue(const int _queueSize);
    ~Queue();

    void enqueue(const Person person);
    void dequeue(Person& person);
    bool isEmpty();
    void printQueue();
private:
    Person* personQueue;
    int queueSize;
    int currentSize;
};

class FriendNet{
public:
    FriendNet(const string fileName); // constructor
    FriendNet(const FriendNet& aNet); // copy constructor
    ~FriendNet(); // destructor
    void listFriends(const string personName, const int hopNo);
    void displayAverageDegrees();
    void displayDiameters();
    void displayGraph();
private:
    List* graph;
    int graphSize;
    int* components;
    int componentNum;
    void recListFriends(const int id, const int hopNo, bool*& visited);
    int findID(const string personName);
    void DFT(const int id, bool*& visited, int component);
    int BFTMaxMin(const int component);
};

#endif // __FRIENDNET_H_

