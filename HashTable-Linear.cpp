#include <iostream>
#include <string>
using namespace std;

#define EmptySinceStart -1
#define EmptyAfterRemoval -2

struct Puppy {
	string name;
	string breed;
	int age = -1;
};

class HashTable {
	int count;
	Puppy* puppies;

public:
	HashTable(int tableSize = 101) {
		count = tableSize;
		puppies = new Puppy[count];
		for (int i = 0; i < count; i++) {
			puppies[i].age = EmptySinceStart;
		}
	}

	~HashTable() {
		delete[] puppies;
	}

	int length()const {
		return count;
	}

	bool insert(const Puppy& elem) {
		int index = elem.age % count;
		int probed = 0;
		while (probed < count) {
			if (puppies[index].age == EmptySinceStart || puppies[index].age == EmptyAfterRemoval) {
				puppies[index] = elem;
				return true;
			}
			else {
				index = (index + 1) % count;
				++probed;
			}
		}
		return false;
	}

	bool remove(const Puppy& elem) {
		int index = elem.age % count;
		int probed = 0;
		while (probed < count) {
			if (puppies[index].age != EmptySinceStart && puppies[index].age != EmptyAfterRemoval) {
				if (puppies[index].age == elem.age) {
					puppies[index].age = EmptyAfterRemoval;
					return true;
				}
			}
			index = (index + 1) % count;
			++probed;
		}
		return false;
	}

	bool search(const Puppy& elem) {
		int index = elem.age % count;
		int probed = 0;
		while (probed < count) {
			if (puppies[index].age != EmptySinceStart && puppies[index].age != EmptyAfterRemoval) {
				if (puppies[index].age == elem.age) {
					return true;
				}
			}
			index = (index + 1) % count;
			++probed;
		}
		return false;
	}

	int getIndex(const int& age) {
		int index = age % count;
		int probed = 0;
		while (probed < count) {
			if (puppies[index].age != EmptySinceStart && puppies[index].age != EmptyAfterRemoval) {
				if (puppies[index].age == age) {
					return index;
				}
			}
			index = (index + 1) % count;
			++probed;
		}
		return -1;
	}

	void printAll()const {
		for (auto i = 0; i < count; i++) {
			if (puppies[i].age != EmptyAfterRemoval || puppies[i].age != EmptySinceStart) {
				cout << i << ": " << puppies[i].name << " " << puppies[i].breed << " " << puppies[i].age;
			}
			cout << endl;
		}
	}
};
