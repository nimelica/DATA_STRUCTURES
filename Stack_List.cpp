#include <iostream>
#include <cassert>
using namespace std;

template<typename Type>
class stack {
	template<typename Type>
	struct node {
		Type data;
		node<Type>* next = nullptr;
	};

	node<Type>* top = nullptr;
	unsigned size = 0;

public:
	stack() {
		top = nullptr;
		size = 0;
	}

	~stack() {
		node<Type>* curr = top;
		while (curr) {
			node<Type>* prev = curr;
			curr = curr->next;
			delete prev;
		}
		size = 0;
		top = nullptr;
	}

	bool isEmpty()const {
		return size == 0;
	}

	int getSize()const {
		return size;
	}

	void push(const Type& newItem) { //prepend
		node<Type>* newNode = new node<Type>;
		newNode->data = newItem;
		
		newNode->next = top;
		top = newNode;
		size++;
	}

	void pop() {
		node<Type>* curr = top;
		if (isEmpty()) {
			return;
		}
		if (size == 1) {
			top = nullptr;
		}
		else {
			top = top->next;
		}
		delete curr;
		size--;
	}

	Type& getTop()const {
		if (isEmpty()) {
			return Type();
		}
		return top->data;
	}

	void printStack()const {
		if (isEmpty()) {
			return;
		}
		node<Type>* curr = top;
		while (curr) {
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}
};