/**
* Author : Ümit Yiğit Başaran
* ID: 21704103
* Section : 2
* Assignment : 5
*/

#include "FriendNet.h"

//Person Class
Person::Person(const int _id, const string _name, const int _degree){
    id = _id;
    name = _name;
    degree = _degree;
}

//Person::~Person(){}

void Person::operator=(const Person& rhs){
    id = rhs.id;
    name = rhs.name;
    degree = rhs.degree;
}

int Person::getID(){return id;}
string Person::getName(){return name;}
int Person::getDegree(){return degree;}
void Person::setID(const int _id){id = _id;}
void Person::setName(const string _name){name = _name;}
void Person::setDegree(const int _degree){degree = _degree;}

void Person::printPerson(){
    cout << "==========================" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Degree: " << degree << endl;
    cout << "==========================" << endl;
}
//end of the Person Class

//List Class
List::List(){
    head = NULL;
    listSize = 0;
}

List::~List(){
    List::PersonNode* curr = head;
    while(curr != NULL){
        curr = curr->next;
        delete head;
        head = curr;
    }
}

int List::getLength() const{return listSize;}

void List::insert(const int _id){
    if (head == NULL){
        head = new List::PersonNode;
        (head->person).setID(_id);
        head->next = NULL;
    }
    else{
        List::PersonNode* curr = head;
        while(curr->next != NULL)
            curr = curr->next;

        List::PersonNode* newNode = new List::PersonNode;
        newNode->next = curr->next;
        curr->next = newNode;
        (newNode->person).setID(_id);
    }
    listSize++;
}

//bool List::remove(const int _id){}
bool List::retrieve(int index, Person& personCpy) const{
    List::PersonNode* curr = head;
    bool done = false;
    for (int i = 1; i <= listSize && curr != NULL && !done; i++){
        if (i == index){
            personCpy = (curr->person);
            done = true;
        }
        curr = curr->next;
    }
    return done;
}

void List::printList(){
    List::PersonNode* curr = head;
    while(curr != NULL){
        (curr->person).printPerson();
        curr = curr->next;
    }
}

void List::setPerson(const int _id, const string _name, const int _degree){
    List::PersonNode* curr = head;
    bool found = false;
    while(curr != NULL && !found){
        if((curr->person).getID() == _id){
            (curr->person).setName(_name);
            (curr->person).setDegree(_degree);
            found = true;
        }
        curr = curr->next;
    }
}
//end of the List Class

//Queue Class
Queue::Queue(const int _queueSize){
    queueSize = _queueSize;
    personQueue = new Person[queueSize];
    currentSize = 0;
}

Queue::~Queue(){
    if (personQueue != NULL)
        delete []personQueue;
}

void Queue::enqueue(const Person person){
    if (currentSize != queueSize){
        personQueue[currentSize] = person;
        currentSize++;
    }
}

void Queue::dequeue(Person& person){
    if (currentSize != 0){
        person = personQueue[0];
        currentSize--;
        for (int i = 0; i < currentSize; i++)
            personQueue[i] = personQueue[i + 1];
    }
}

bool Queue::isEmpty(){return (currentSize == 0);}

void Queue::printQueue(){
    for (int i = 0; i < currentSize; i++){
        personQueue[i].printPerson();
    }
    cout << endl;
}
//end of the Queue Class

//FriendNet Class
FriendNet::FriendNet(const string fileName){
    graphSize = 0;
    fstream file;
    file.open(fileName, ios_base::in);
    if (file.is_open()){
        file >> graphSize;
        graph = new List[graphSize];
        //cout << "GraphSize: " << graphSize << endl;
        for (int i = 0; i < graphSize; i++){
            int id = 0;
            string name = "";
            int degree = 0;
            int friendID = 0;
            file >> id;
            file >> name;
            file >> degree;
//            cout << "ID: " << id << endl;
//            cout << "NAME: " << name << endl;
//            cout << "DEGREE: " << degree << endl;
            graph[id].insert(id);
            graph[id].setPerson(id, name, degree);
            for (int j = 0; j < degree; j++){
                file >> friendID;
                graph[id].insert(friendID);
//                cout << "FRIENDID: " << friendID << endl;
            }
        }

        for (int i = 0; i < graphSize; i++){
            Person head;
            graph[i].retrieve(1, head);
            for (int j = 2; j <= head.getDegree() + 1; j++){
                Person friendPerson;
                graph[i].retrieve(j, friendPerson);
                int friendIDTmp = friendPerson.getID();
                graph[friendIDTmp].retrieve(1, friendPerson);
                graph[i].setPerson(friendIDTmp, friendPerson.getName(), friendPerson.getDegree());
            }
        }

    //    for (int i = 0; i < graphSize; i++){
    //        graph[i].printList();
    //    }
        components = new int[graphSize];

        bool* visited = new bool[graphSize];
        for (int i = 0; i < graphSize; i++)
            visited[i] = false;

        componentNum = 0;
        for (int i = 0; i < graphSize; i++){
            if (!visited[i]){
                DFT(i, visited, componentNum);
                componentNum++;
            }
        }
        delete []visited;
    }
    else{
        graph = NULL;
        componentNum = 0;
        components = NULL;
        cout << "Because the file name cannot be found the FriendNet is constructed as empty net." << endl;
    }
//    for (int i = 0; i < graphSize; i++)
//        cout << components[i] << " ";
//    cout << endl;
}

void FriendNet::DFT(const int id, bool*& visited, int component){
    Person startingVertex;
    graph[id].retrieve(1, startingVertex);
    visited[id] = true;
    components[id] = component;
    for (int i = 2; i <= startingVertex.getDegree() + 1; i++){
        Person friends;
        graph[id].retrieve(i, friends);
        if (!visited[friends.getID()])
            DFT(friends.getID(), visited, component);
    }
}
FriendNet::FriendNet(const FriendNet& aNet){
    if (aNet.graph != NULL){
        graphSize = aNet.graphSize;
        graph = new List[graphSize];
        for (int i = 0; i < graphSize; i++){
            Person tmpPerson;
            aNet.graph[i].retrieve(1, tmpPerson);
            graph[i].insert(tmpPerson.getID());
            graph[i].setPerson(tmpPerson.getID(), tmpPerson.getName(), tmpPerson.getDegree());
            for (int j = 2; j <= tmpPerson.getDegree() + 1; j++){
                Person tmpPersonAdj;
                aNet.graph[i].retrieve(j, tmpPersonAdj);
                graph[i].insert(tmpPersonAdj.getID());
                graph[i].setPerson(tmpPersonAdj.getID(), tmpPersonAdj.getName(), tmpPersonAdj.getDegree());
            }
        }

        componentNum = aNet.componentNum;
        components = new int[graphSize];
        for (int i = 0; i < graphSize; i++)
            components[i] = aNet.components[i];
    }
    else{
        graph = NULL;
        componentNum = 0;
        components = NULL;
    }
}

FriendNet::~FriendNet(){
    if (graph != NULL)
        delete []graph;

    if (components != NULL)
        delete []components;
}

int FriendNet::findID(const string personName){
    Person personTmp;
    bool found = false;
    int id = -1;
    for (int i = 0; i < graphSize && !found; i++){
        graph[i].retrieve(1, personTmp);
        if ((personTmp.getName()).compare(personName) == 0){
            found = true;
            id = personTmp.getID();
        }
    }
    return id;
}

void FriendNet::recListFriends(const int id, const int hopNo, bool*& visited){
    if (hopNo != -1){
        Person startingVertex;
        graph[id].retrieve(1, startingVertex);
        visited[id] = true;
        for (int i = 2; i <= startingVertex.getDegree() + 1; i++){
            //cout << id << "-TEST" << endl;
            Person friends;
            graph[id].retrieve(i, friends);
            recListFriends(friends.getID(), hopNo - 1, visited);
        }
    }
}

void FriendNet::listFriends(const string personName, const int hopNo){
    int id = findID(personName);
    if (id != -1){
        Person personTmp;
        graph[id].retrieve(1, personTmp);
        cout << "People accessible from " << personName << " within " << hopNo << " hops: ";
        if (hopNo > 0 && personTmp.getDegree() > 0){
            bool* visited = new bool[graphSize];
            for (int i = 0; i < graphSize; i++)
                visited[i] = false;
            recListFriends(id, hopNo, visited);
            int printComma = 0;
            for (int i = 0; i < graphSize; i++){
                if (visited[i] && i != id){
                    Person toPrint;
                    graph[i].retrieve(1, toPrint);
                    if (printComma != 0)
                        cout << ", ";
                    cout << toPrint.getName();
                    printComma = 1;
                }
            }
            cout << endl;
            delete []visited;
        }
        else{
            cout << "NOBODY" << endl;
        }
    }
    else{
        cout << personName << " does not exist in the network." << endl;
    }
}

void FriendNet::displayAverageDegrees(){
    cout << "There are " << componentNum << " connected components. The average degrees are: " << endl;
    for(int i = 0; i < componentNum; i++){
        cout << "For component " << i << ": ";
        int totalNumDegrees = 0;
        int numOfThatComponent = 0;
        for (int j = 0; j < graphSize; j++){
            if (components[j] == i){
                Person tmpPerson;
                graph[j].retrieve(1, tmpPerson);
                totalNumDegrees += tmpPerson.getDegree();
                numOfThatComponent++;
            }
        }
        double average = (double) totalNumDegrees / (double) numOfThatComponent;
        //cout << fixed;
        cout << fixed << setprecision(2) << average << endl;
    }
}

int FriendNet::BFTMaxMin(const int component){
    int result = 0;
    for (int compIndex = 0; compIndex < graphSize; compIndex++){
        if (components[compIndex] == component){
            Person startingVertex;
            graph[compIndex].retrieve(1, startingVertex);

            int* path = new int[graphSize];
            for (int i = 0; i < graphSize; i++)
                path[i] = -1;

            bool* visited = new bool[graphSize];
            for (int i = 0; i < graphSize; i++)
                visited[i] = false;

            Queue BFTQueue(graphSize);

            visited[startingVertex.getID()] = true;
            path[startingVertex.getID()] = 0;
            BFTQueue.enqueue(startingVertex);
            while(!BFTQueue.isEmpty()){
                Person friends;
                BFTQueue.dequeue(friends);
                for (int i = 2; i <= friends.getDegree() + 1; i++){
                    Person adjacent;
                    graph[friends.getID()].retrieve(i, adjacent);
                    if (!visited[adjacent.getID()]){
                        path[adjacent.getID()] = path[friends.getID()] + 1;
                        visited[adjacent.getID()] = true;
                        BFTQueue.enqueue(adjacent);

                        if (path[adjacent.getID()] > result)
                            result = path[adjacent.getID()];
                    }
                }
            }

            delete []visited;
            delete []path;
        }
    }
    return result;
}

void FriendNet::displayDiameters(){
    cout << "There are " << componentNum << " connected components. The diameters are:" << endl;
    for (int i = 0; i < componentNum; i++){
        cout << "For component " << i << ": " << BFTMaxMin(i) << endl;
    }
}

void FriendNet::displayGraph(){
    for(int i = 0; i < graphSize; i++){
        graph[i].printList();
    }
}
//end of the FriendNet Class
