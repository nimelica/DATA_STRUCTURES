#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

template<typename Type>
class ArrayList
{
private:
	Type* list;
	int capacity;
	unsigned length;

	//Helper Functions
	bool isEmpty()const //O(1)
	{
		return (length == 0);
	}

	bool isFull()const //O(1)
	{
		return (length == capacity);
	}

public:
	//Constructor + Big Three
	ArrayList(int initSize = 100) //O(1)
	{
		capacity = initSize;
		if (capacity <= 0)
		{
			cerr << "Capacity must be positive!\n";
			capacity = 100;
		}
		length = 0;
		list = new Type[capacity];
	}
	~ArrayList() //O(1)
	{
		delete[]list;
	}
	ArrayList(const ArrayList& otherList) //O(N)
	{
		capacity = otherList.capacity;
		length = otherList.length;
		list = new Type[capacity];

		assert(list != nullptr); //if list is not empty
		for (size_t i = 0; i < length; i++) //copy data
		{
			list[i] = otherList.list[i];
		}
	}
	const ArrayList operator=(const ArrayList& otherList)
	{
		if (this != &otherList)
		{
			delete[]list;

			capacity = otherList.capacity;
			length = otherList.length;
			list = new Type[capacity];

			assert(list != nullptr); //if list is not empty
			for (size_t i = 0; i < length; i++) //copy data
			{
				list[i] = otherList.list[i];
			}
		}
		return *this;
	}

	//Accessors
	int getLength()const
	{
		return length;
	}

	int getCapacity()const
	{
		return capacity;
	}

	Type getElementAt(const int& pos)const
	{
		if (pos < 0 || pos >= length) {
			return Type();
		}
		else if (isEmpty()) {
			return Type();
		}
		else
			return list[pos];
	}

	void retrieveAt(int location, const Type& elemData)const //O(1)
	{
		if (location < 0 || location >= capacity) {
			cerr << "The postion of the item to be inserted is out of range." << endl;
		}
		else {
			elemData = list[location];
		}
	}

	//Display
	void printList()const //O(N)
	{
		for (size_t i = 0; i < length; i++)
		{
			cout << list[i] << " ";
		}
		cout << endl;
	}

	bool isItemAtEqual(const int& pos, const Type& elemData) //O(1)
	{
		return (list[pos] == elemData);
	}

	//Inserting Functions
	void insertAt(const int& location, const Type& elemData)
	{
		if (location < 0 || location >= capacity) {
			cerr << "The postion of the item to be inserted is out of range." << endl;
		}
		else
		{
			if (isFull()) //length >= capacity
			{
				cerr << "List is full!\n";
			}
			else
			{
				for (size_t i = length; i > location; i--) //shift the array elements from this position to one position forward
				{
					list[i] = list[i - 1];
				}
				list[location] = elemData;
				length++;
			}
		}
	}

	void insert(const Type& elemData)
	{
		int location;

		//case 1) array might be empty
		if (isEmpty()) {
			list[length++] = elemData;
		}
		//case 2) array might be full
		else if (isFull()) {
			cerr << "List is full!\n";
			//resize()
		}
		else
		{
			//search through the list if the data is already in the list
			location = search(elemData);
			if (location != -1) {
				cerr << "Data is already in the list at " << location << " index!\n";
			}
			else {
				list[length++] = elemData;
			}
		}
	}

	void insertLast(const Type& elemData)
	{
		if (isFull()) {
			cerr << "The list is full." << endl;
		}
		else
		{
			list[length] = elemData;
			length++;
		}
	}

	void resize()
	{
		Type* temp = new Type[capacity * 2];

		for (size_t i = 0; i < length; i++)
		{
			temp[i] = list[i];
		}
		delete[]list;
		list = temp;
		temp = nullptr;
		length = 0;
		capacity *= 2;
	}

	//Removing Functions
	void removeAt(const int& pos)
	{
		if (pos < 0 || pos >= length || pos >= capacity) {
			cerr << "The postion of the item to be inserted is out of range." << endl;
		}
		else {
			for (size_t i = pos; i < length - 1; i++)
			{
				list[i] = list[i + 1];
			}
			length--;
		}
	}

	void remove(const Type& elemData)
	{
		int location;
		if (isEmpty()) {
			cerr << "List is empty!\n";
		}
		else
		{   //check if the data in the array (you cannot delete a data if it is not exist)
			location = search(elemData);
			if (location != -1) {
				list[location] = list[length - 1];
			}
			else {
				//removeAt(location);
				cerr << "Data not found!\n";
			}
		}
	}

	//Neccessary
	int search(const Type& elemData)const
	{
		int location;
		bool found = false;

		for (location = 0; location < length; location++) //starts from index 0
		{
			if ((list[location] == elemData) && (location < length - 1))
			{
				found = true;
				break;
			}
		}
		if (found) {
			return location; //found index
		}
		return -1;
	}

	void replaceAt(int location, const Type& elemData)
	{
		if (location < 0 || location >= capacity) {
			cerr << "Out of index!\n";
		}
		else {
			list[location] = elemData;
		}
	}

	void clearList()
	{
		length == 0;
	}

};
#endif

