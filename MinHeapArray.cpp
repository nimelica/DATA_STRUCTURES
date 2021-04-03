#include <iostream>
#include <cassert>
using namespace std;

/*MIN HEAP IMPLEMENTATION USING DYNAMICALLY ALLOCATED ARRAY*/

template<typename Type>
class HeapArray {
	Type* array = nullptr;
	int capacity = 0;
	int lastPosition = 0;

private:
	void swap(int& from, int& to) {
		auto holder = array[from];
		array[from] = array[to];
		array[to] = holder;
	}

	void resize() {
		Type* newArray = new Type[2 * capacity];
		for (int i = 0; i < lastPosition; i++) {
			newArray[i] = array[i];
		}
		if (array != nullptr)
			delete[]array;
		array = newArray;
		newArray = nullptr;
		capacity *= 2;
	}

	void TrickleUp(int position) { //recursive heapify up solution
		if (position == 0) return;
		int parent = (position - 1) / 2;
		if (array[position] < array[parent]) {
			swap(position, parent);
			TrickleUp(parent);
		}
	}

	void TrickleDown(int parent) { //recursive heapify down solution
		int leftChild = 2 * parent + 1;
		int rightChild = 2 * parent + 2;
		int smallest = parent;

		if (leftChild < lastPosition && array[leftChild] < array[parent])
			smallest = leftChild;
		if (rightChild < lastPosition && array[rightChild] < array[parent])
			smallest = rightChild;
		if (smallest != parent) {
			auto temp = array[parent];
			swap(parent, smallest);
			TrickleDown(smallest);
		}
	}

public:
	HeapArray(int defSize = 100) {
		capacity = defSize;
		if (capacity <= 0) {
			capacity = 100;
		}
		lastPosition = 0;
		array = new Type[capacity];
	}

	~HeapArray() {
		delete[]array;
	}

	HeapArray(const HeapArray& other) {
		lastPosition = other.lastPosition;
		capacity = other.capacity;
		array = new Type[other.capacity];
		for (int i = 0; i < other.lastPosition; i++) {
			array[i] = other.array[i];
		}
	}

	int getCapacity()const {
		return capacity;
	}

	int getLength()const {
		return lastPosition;
	}

	bool isEmpty()const {
		return (lastPosition == 0);
	}

	bool isFull()const {
		return (lastPosition == capacity);
	}

	Type getElementAt(const int& index)const {
		assert(!isEmpty());
		return array[index];
	}

	Type getMIN()const {
		assert(!isEmpty());
		return array[0];
	}

	void push(const Type& newItem) {
		if (isFull()) {
			cerr << "Array is full->resizing it!\n";
			//resize();
			return;
		}
		array[lastPosition++] = newItem;
		TrickleUp(lastPosition); //or TrickleUP
	}

	void HeapSort(int currSize)
	{
		int n = currSize;
		for (int i = n / 2 - 1; i >= 0; i--) {
			TrickleDown(i);
		}
		for (int i = n - 1; i >= 0; i--) {
			swap(i, 0);
			TrickleDown(i);
		}
	}

	void pop() { //always removes the root
		if (lastPosition > 0) {
			array[0] = array[lastPosition - 1];
			lastPosition--;
			TrickleDown(0);
		}
	}

	int extractMin() {
		int max = array[0];
		array[0] = array[lastPosition - 1];
		lastPosition--;
		TrickleDown(max);
		return max;
	}

	void printHeap()const {
		for (int i = 0; i < lastPosition; i++) {
			cout << array[i] << " ";
		}
		cout << endl;
	}
};