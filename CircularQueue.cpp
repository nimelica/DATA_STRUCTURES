#include <iostream>
#include <cassert>
using namespace std;

/*Circular queue using static array*/

class MyCircularQueue {
private:
    int store[1000];
    int front = 0;
    int size = 0;
    int capacity;

public:
    MyCircularQueue(int k){
        capacity = k;
    }

    void enQueue(int value){
        assert(!isFull());
        store[front + size++] = value;
    }

    void deQueue(){
        assert(!isEmpty());
        front++; size--;
    }

    int Front(){
        assert(!isEmpty());
        return store[front];
    }

    int Rear(){
        assert(!isEmpty());
        return store[front + size];
    }

    bool isEmpty(){
        return (size == 0);
    }

    bool isFull(){
        return (size == capacity);
    }

};