#include <iostream>
#include <cassert>
using namespace std;

template<typename Type>
class queue {
	template<typename Type>
	struct node {
		Type data;
		node<Type>* next = nullptr;
	};

	node<Type>* front = nullptr;
	node<Type>* tail = nullptr;
	unsigned size = 0;

public:
	queue() {
		front = nullptr;
		tail = nullptr;
		size = 0;
	}

	~queue() {
		node<Type>* curr = front;
		while (curr) {
			node<Type>* prev = curr;
			curr = curr->next;
			delete prev;
		}
		size = 0;
		front = tail = nullptr;
	}

	bool isEmpty()const {
		return size == 0;
	}

	int getSize()const {
		return size;
	}

	void push(const Type& newItem) { //append
		node<Type>* newNode = new node<Type>;
		newNode->data = newItem;

		if (isEmpty()) {
			front = newNode;
		}
		else {
			tail->next = newNode;
		}
		tail = newNode;
		size++;
	}

	void pop() {
		if (isEmpty()) return;
		if (!front->next) {
			delete front;
			front = tail = nullptr;
			return;
		}
		node<Type>* curr = front;
		while (curr->next->next) {
			curr = curr->next;
		}
		delete curr->next;
		curr->next = nullptr;
	}

	Type& getFront()const {
		if (isEmpty()) {
			return Type();
		}
		return front->data;
	}

	void printQueue()const {
		if (isEmpty()) {
			return;
		}
		node<Type>* curr = front;
		while (curr) {
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}
};
