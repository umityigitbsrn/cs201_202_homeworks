Umit Yigit Basaran
Homework - 3

In order to resolve the confusion, that is caused because of using same class names in order to test these classes in one simulator.cpp,
I add [#include "simulator.cpp"] commands to the end of the maxHeap1.h and maxHeap2.h header files  so that
I just wri:te "g++ maxHeap1.cpp -o simulator_Q1" and "g++ maxHeap2.cpp -o simulator_Q2" commands 
in the Makefile. Therefore, you don't need to comment or erase something in the simulator.cpp file. 
