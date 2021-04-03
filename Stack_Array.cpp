#include <iostream>
#include <cassert>
using namespace std;

template<typename Type>
class stack
{
private:
	Type* list;
	unsigned capacity;
	int stackTop;

	//Private helper functions
	bool isFull()const {
		return (stackTop == capacity);
	}

	void resize()const {
		Type* tempCopy = new Type[capacity * 2];

		for (int i = 0; i < capacity; i++)
		{
			tempCopy[i] = list[i];
		}
		delete[]list;
		list = tempCopy;
		tempCopy = nullptr;

		stackTop = 0;
		capacity *= 2;
	}

public:
	stack(int size = 100)
	{
		capacity = size;
		if (capacity <= 0) {
			cerr << "Size must be positive!\n";
			capacity = 100;
		}
		else
		{
			stackTop = 0;
			list = new Type[capacity];
		}
	}
	~stack()
	{
		delete[]list;
	}

	bool isEmpty()const {
		return (stackTop == 0);
	}

	void push(const Type& newItem) {
		//add from the top
		if (!isFull())
		{
			list[stackTop++] = newItem;
		}
		else
		{
			cerr << "Stack is full!\n";
		}

	}
	void pop() {
		if (!isEmpty())
		{
			stackTop--;
		}
		else {
			cerr << "Stack is empty!\n";
		}
	}

	Type top()const {
		if (!isEmpty())
		{
			return list[stackTop - 1];
		}
		else {
			cerr << "Stack is empty!\n";
		}
	}
};
