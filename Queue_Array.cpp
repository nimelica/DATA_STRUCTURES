#include <iostream>
#include <cassert>
using namespace std;

/*circular dynamic queue array implementation*/

template<typename Type>
class queue
{
	Type* list;
	int front;
	int rear;
	unsigned size;
	unsigned capacity;

public:
	queue(int maxSize = 100)
	{
		capacity = maxSize;
		if (capacity <= 0) {
			capacity = 100;
		}
		list = new Type[capacity];
		initVariables();
	}

	~queue() {
		delete[]list;
	}

	void initVariables()
	{
		front = size = 0;
		rear = capacity = -1;
	}

	bool isEmpty()const {
		return (size == 0);
	}

	bool isFull()const {
		return (size == capacity);
	}

	void enqueue(const Type& newItem)
	{
		if (isFull()) {
			cerr << "Queue is full!\n";
			return;
		}
		rear = (rear + 1) % capacity;
		list[rear] = newItem;
		size++;
	}

	void dequeue()
	{
		if (isEmpty()) {
			cerr << "Queue is empty!\n";
			return;
		}
		front = (front + 1) % capacity;
		size--;
	}

	Type& front()const
	{
		assert(!isEmpty());
		return list[front];
	}

	Type& back()const
	{
		assert(!isEmpty());
		return list[rear];
	}

	void printQueue()const {
		for (auto i = front; i < rear; i++) {
			cout << list[i] << " ";
		}
		cout << endl;
	}
};

