/*
 * Title: Homework - 3
 * Author: Umit Yigit Basaran
 * ID: 21704103
 * Section: 2
 * Assignment: 3
 * Description: maxHeap1 source file - [Heap and Heap Item classes]
 */

#include "maxHeap1.h"

// CLASS HEAP ITEM
HeapItem::HeapItem(int idCpy, int priorityCpy,
                   int arrivalTimeCpy, int execTimeCpy){
    id = idCpy;
    priority = priorityCpy;
    arrivalTime = arrivalTimeCpy;
    execTime = execTimeCpy;
}

HeapItem::HeapItem(const HeapItem& cpyItem){
    id = cpyItem.id;
    priority = cpyItem.priority;
    arrivalTime = cpyItem.arrivalTime;
    execTime = cpyItem.execTime;
}

HeapItem::~HeapItem(){}

void HeapItem::operator=(const HeapItem& rhs){
    id = rhs.id;
    priority = rhs.priority;
    arrivalTime = rhs.arrivalTime;
    execTime = rhs.execTime;
}

int HeapItem::getId(){ return id; }
double HeapItem::getPriority(){ return priority + (1.00/(arrivalTime + 1)); }
int HeapItem::getArrivalTime(){ return arrivalTime; }
int HeapItem::getExecTime(){ return execTime; }

void HeapItem::setId(int setId){ id = setId; }
void HeapItem::setPriority(int setPriority){ priority = setPriority; }
void HeapItem::setArrivalTime(int setArrivalTime){ arrivalTime = setArrivalTime; }
void HeapItem::setExecTime(int setExecTime){ execTime = setExecTime; }

void HeapItem::printHeapItem(){
    cout << "ID: " << id << " Priority: " << priority <<
        " Arrival Time: " << arrivalTime << " Execution Time: " << execTime;
    cout << endl;
}
//HEAP ITEM END

//CLASS HEAP
Heap::Heap():size(0){}

bool Heap::heapIsEmpty() const{ return (size == 0); }

void Heap::heapInsert(const HeapItem& newItem){
    // Place the new item at the end of the heap
	items[size] = newItem;

	// Trickle new item up to its proper position
	int place = size;
	int parent = (place - 1)/2;
	while ( (place > 0) && (items[place].getPriority() > items[parent].getPriority()) ) {
		HeapItem temp = items[parent];
		items[parent] = items[place];
		items[place] = temp;

		place = parent;
		parent = (place - 1)/2;
	}
 	++size;
}

void Heap::heapDelete(HeapItem& rootItem){
    if (!heapIsEmpty()){
        rootItem = items[0];
		items[0] = items[--size];
		heapRebuild(0);
    }
}

void Heap::heapRebuild(int root){
    int child = 2 * root + 1; 	// index of root's left child, if any
	if ( child < size ) {
		// root is not a leaf so that it has a left child
		int rightChild = child + 1; 	// index of a right child, if any
		// If root has right child, find larger child
		if ( (rightChild < size) &&
		     (items[rightChild].getPriority() > items[child].getPriority()) )
			child = rightChild; 	// index of larger child

		// If root’s item is smaller than larger child, swap values
		if ( items[root].getPriority() < items[child].getPriority() ) {
                HeapItem temp = items[root];
                items[root] = items[child];
                items[child] = temp;
			// transform the new subtree into a heap
			heapRebuild(child);
		}
	}
}

void Heap::printHeap(){
    for (int i = 0; i < size; i++)
        items[i].printHeapItem();
}
//HEAP END
