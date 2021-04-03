#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

//Node Declaration
template<typename Type>
struct ListNode {
	Type data;
	ListNode<Type>* next = nullptr;
	ListNode<Type>* prev = nullptr;

	ListNode(Type inputData) {
		data = inputData;
		next = prev = nullptr;
	}
};

//List Class 
template<typename Type>
class LinkedList 
{
private:
	unsigned listSize{};
	ListNode<Type>* head;
	ListNode<Type>* tail;

	//Private helper functions
	bool isEmpty()const {
		return (listSize == 0);
	}

public:
	// Constructor/Destructor/Copy Constructor
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		listSize = 0;
	}

	~LinkedList()
	{
		Destroy_List();
	}

	LinkedList(const LinkedList& other)
	{
		head = nullptr;
		tail = nullptr;
		listSize = 0;

		ListNode<Type>* curr = other.head;
		for (int i = 0; i < other.listSize; i++) {
			Append_Node(curr->data);
			curr = curr->next;
		}
	}

	//Public helper functions
	bool Contains(const Type& itemFind)const //search the list
	{
		ListNode<Type>* curr = head;
		bool found = false;

		while (curr && curr->data!=itemFind) //or while(curr && !found)
		{
			//curr->data == itemFind ?
				//found = true :
				curr = curr->next;
		}
		if (!curr) {
			return false;
		}
		return true;
	}

	//Accessors
	int Get_List_Size()const {
		return listSize; 
	}
	int Get_Data_Index(const Type& data)const
	{
		ListNode<Type>* iter = head;
		int index = 0;
		while (iter)
		{
			if (iter->data == data)
				return index;
			iter = iter->next;
			index++;
		}
		return -1;
	}

	void Get_Max_Data()const
	{
		ListNode<Type>* curr = head;
		Type maxVal = head->data;

		while (curr) {
			if (curr->data > maxVal) {
				maxVal = curr->data;
			}
			curr = curr->next;
		}
		cout << "Max value in the list is " << maxVal << " " << endl;
	}

	void Get_Min_Data()const
	{
		ListNode<Type>* curr = head;
		Type minData = head->data;

		while (curr) {
			if (curr->data < minData) {
				minData = curr->data;
			}
			curr = curr->next;
		}
		cout << "Minimum value in the list is " << minData << " "<<endl;
	}

	ListNode<Type>* Get_Head()const {
		return head; 
	}

	ListNode<Type>* Get_Tail()const {
		return tail; 
	}

	Type Get_Data_At_Index(int pos)const
	{
		if (pos < 0 || pos >= listSize) {
			cerr << "Position is out of index!\n";
			return Type();
		}
		if (isEmpty()) {
			cerr << "List is empty!\n";
			return Type();
		}

		ListNode<Type>* curr = head;
		for (int i = 0; i < pos; i++) {
			curr = curr->next;
		}
		return curr->data;
	}

	ListNode<Type>* Get_Node_At_Index(const int& pos)const
	{
		if (pos < 0 || pos >= listSize) {
			cerr << "Position is out of index!\n";
			return nullptr;
		}
		if (isEmpty()) {
			cerr << "List is empty!\n";
			return nullptr;
		}

		int indexCount = 0;
		ListNode<Type>* iter = head;
		while (indexCount != pos)
		{
			iter = iter->next;
			indexCount++;
		}
		return iter;
	}

	ListNode<Type>* Get_Middle_Node() 
	{
		ListNode<Type>* slow = head;
		ListNode<Type>* fast = head;

		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	Type Get_Middle_Data()const
	{
		ListNode<Type>* fast = head;
		ListNode<Type>* slow = head;

		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow->data;
	}

	//Insertion Functions
	void Append_Node(const Type& newItem) 
	{
		//create new node
		ListNode<Type>* newNode = new ListNode<Type>(newItem);
		if (isEmpty())
		{
			head = newNode;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
		}
		tail = newNode;
		listSize++;
	}
	void Prepend_Node(const Type& newItem)
	{
		ListNode<Type>* newNode = new ListNode<Type>(newItem);

		if (isEmpty()) {
			tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
		}
		head = newNode;
		listSize++;
	}

	void Insert_At_Index(const int& pos, const Type& newItem)
	{
		if (pos > newItem || pos < 0) //position might be invalid
		{
			cerr << "Position is out of index!\n";
			return;
		}
		if (isEmpty() || pos == 0) //list is empty or position is 0
		{
			Prepend_Node(newItem);
			return;
		}
		else if (pos == listSize) //add from last index
		{
			Append_Node(newItem);
			return;
		}
		else //position middle of somewhere
		{
			ListNode<Type>* newNode = new ListNode<Type>(newItem);

			ListNode<Type>* prevCurr = Get_Node_At_Index(pos - 1);
			newNode->next = prevCurr->next;
			newNode->prev = prevCurr;
			prevCurr->next = newNode;
			newNode->next->prev = newNode; //we need to arrange next node's prev pointer

			listSize++;
		}
	}
	
	//Deletion Functions
	void Remove_Spesific_Item(const Type& itemFind)
	{
		ListNode<Type>* curr = head;
		ListNode<Type>* trail = nullptr;
		bool found = false;

		if (isEmpty()) {
			return;
		}
		else {
			while (curr && !found) //or just type while(curr && curr->data!=itemFind)
			{
				if (curr->data == itemFind)
				{
					found = true;
				}
				else
				{
					trail = curr;
					curr = curr->next;
				}
			}
			if (curr == nullptr) {
				cerr << "Data is not found!\n";
				return;
			}
			else {
				if (found)
				{
					if (head==curr && listSize == 1)
					{
						head = tail = nullptr;
					}
					else if (head == curr)
					{
						head = head->next;
					}
					else if (tail == curr)
					{
						tail = trail;
						trail->next = nullptr;
					}
					else
					{
						trail->next = curr->next;
					}
				}
			}
		}
		delete curr;
		listSize--;
	}

	void Remove_Head()
	{
		ListNode<Type>* curr = head;
		if (isEmpty()) {
			cerr << "List is empty!\n";
			return;
		}
		if (listSize == 1) {
			head = tail = nullptr;
		}
		else{
			head = head->next;
		}
		delete curr;
		listSize++;
	}

	void Remove_Tail()
	{
		//case 1) list can be empty (we do nothing)
		if (isEmpty()) {
			return;
		}
		ListNode<Type>* trash = tail;

		//case 2) list only have one node
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			tail = tail->prev;                                  //[node1] [node2] [tail]
			tail->next = nullptr;                               //[node1] [tail]  [null]
		}
		delete trash;
		listSize--;
	}

	void Remove_At_Index(const int& pos)
	{
		if (pos < 0 or pos >= listSize) {
			cerr << "Position is out of index!\n";
			return;
		}
		if (isEmpty()) {
			return;
		}
		if (pos == 0) {
			Remove_Head();
			return;
		}
		else if (pos == listSize - 1) {
			Remove_Tail();
			return;
		}
		else
		{
			ListNode<Type>* curr = Get_Node_At_Index(pos - 1);
			ListNode<Type>* rubbish = curr->next;
			//head c r t tail
			//....delete r....
			//head c  t tail
			curr->next = rubbish->next;
			rubbish->next->prev = curr;
			delete rubbish;
			listSize--;
		}
	}

	//Printing Functions
	void Print_List_Forward()const {
		ListNode<Type>* curr = head;
		while (curr) {
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}

	void Print_List_Backward()const
	{
		if (isEmpty()) {
			return;
		}
		ListNode<Type>* curr = tail;
		while (curr) {
			cout << curr->data << " ";
			curr = curr->prev;
		}
		cout << endl;
	}

	//Sorting Functions
	void Bubble_Sort_To_List()
	{
		if (!head || !head->next) {
			return;
		}
		ListNode<Type>* i = head;
		for (; i != nullptr; i = i->next) {
			ListNode<Type>* j = i;
			for (; j != nullptr; j = j->next) {
				if (i->data > j->data) 
					swap(i->data, j->data);
			}
		}
	}

	void Insertion_Sort_To_List()
	{
		if (!head || !head->next) {
			return;
		}
		ListNode<Type>* i = head->next; //outer loop iterator i starts from 1

		while (i)
		{
			ListNode<Type>* j = head; //previous
			ListNode<Type>* nextNode = i;

			while (j != i)
			{
				if (nextNode->data < j->data)
				{
					swap(nextNode->data, j->data);
				}
				j = j->next;
			}
			i = i->next;
		}
	}

	//Core functions
	void Destroy_List()
	{
		ListNode<Type>* killer = head;
		while (killer) {
			ListNode<Type>* dedective = killer;
			killer = killer->next;
			delete dedective;
		}
		head = nullptr;
		tail = nullptr;
		listSize = 0;
	}

	ListNode<Type>* Reverse_List(ListNode<Type>* head)
	{
		ListNode<Type>* previ = nullptr;
		while (head) {
			ListNode<Type>* nextOne = head->next;
			head->next = previ;
			previ = head;
			head = nextOne;
		}
		return previ;
	}

	//Applications with Linked Lists
	Type Sum_Of_All_Nodes()
	{
		Type sum{};
		ListNode<Type>* iter = head;
		for (; iter != nullptr; iter = iter->next)
		{
			sum += iter->data;
		}
		return sum;
	}

	void Remove_Duplicates() //remove all duplcates not only one
	{
		if (!head or !head->next) {
			return;
		}
		ListNode<Type>* curr = head;
		while (curr && curr->next)
		{
			if (curr->data == curr->next->data) 
			{
				ListNode<Type>* duplication = curr->next;
				curr->next = duplication->next; //we need to remove from the middle
				delete duplication;
				continue; //in order to delete multiple duplication
			}
			else {
				curr = curr->next; //continue to looking for
			}
		}
	}

	void Remove_Occurences(){
		if (!head or !head->next) {
			return;
		}
		ListNode<Type>* sentinel = new ListNode<Type>(-1);
		sentinel->next = head;
		ListNode<Type>* current = sentinel;

		while (head)
		{
			if (head->next!=nullptr and head->data == head->next->data) {
				while (head->next and head->data == head->next->data) {
					ListNode<Type>* temp = head;
					head = head->next;
					delete temp;
				}
				current->next = head->next;
			}
			else {
				current = current->next;
			}
			head = head->next; //we said while(head) so we need to move forward
		}
	}

	ListNode<Type>* Get_Intersection_Node(ListNode<Type>* headRef1, ListNode<Type>* headRef2)
	{
		ListNode<Type>* currA = headRef1;
		ListNode<Type>* currB = headRef2;
		int length1{}, length2{};

		while (currA) {
			currA = currA->next;
			length1++;
		}
		while (currB) {
			currB = currB->next;
			length2++;
		}

		int diff = abs(length1 - length2);
		
		if (length2 > length1) {
			swap(headRef2, headRef1);
		}

		while (diff--) {
			headRef1 = headRef1->next;
		}
		while (headRef1 != headRef2) {
			headRef1 = headRef1->next, headRef2 = headRef2->next;
		}
		return headRef1;
	}

	bool isPalindrome()
	{
		stack<Type>st;
		ListNode<Type>* curr = head;
		while (curr) {
			st.push(curr->data);
			curr = curr->next;
		}
		ListNode<Type>* iter = head;
		while (iter) 
		{
			if (st.top() == iter->data)
			{
				iter = iter->next;
				st.pop();
			}
			return false;
		}
		return true;
	}
};
