#include <iostream>
#include <vector>
using namespace std;

template<typename Type>
void Swap(Type& from, Type& to) {
	auto holder = from;
	from = to;
	to = holder;
}


//bubble sort
template<typename Type>
void BubbleSort(Type* array, int size) {
	for (size_t i = 0; i < size; i++) { 
		for (size_t j = i; j < size; j++) {
			if (array[i] > array[j])
				Swap(array[i], array[j]);
		}
	}
}

//bubble sort
template<typename Type>
void OptimizedBubbleSort(Type* array, int size) {
	while (size--) { //same just like having an outer loop 
		bool swapped = false;
		for (size_t i = 0; i < size; i++) {
			if (array[i] > array[i + 1]) {
				Swap(array[i], array[i + 1]);
				swapped = true;
			}
		}if (!swapped) break; //break the outer loop if values are not swapped
	}
}

/*. Selection sort's runtime grows quadratically with the input size. 
If the input increases in size by X times, the runtime increases X times.*/

//selection sort
template<typename Type>
void SelectionSort(Type* array, int size) { 
	int smallest = 0;
	for (size_t i = 0; i < size-1; i++) { //if array is already sorted, only outer loops, size-1 times assigned (minimum)
		smallest = i;
		for (size_t j = i + 1; j < size; j++) { //find the smallest value in the inner loop
			if (array[smallest] > array[j]) 
				smallest = j;
		}
		Swap(array[i], array[smallest]);  //swap them in outer loop
	}
}

/*note: if outer loop i < size 
and the inner loop is j = i, it is same as saying
outer loop i < size -1 but inner j = i + 1
But, second one is liitle more optimized*/

//insertion sort
template<typename Type>
void InsertionSort(Type* arr, int size) { //if list is nearly sorted, O(N) times
	int me, you;
	me = 1; //selects the first unsorted element
	for (; me < size; me++) {
		you = me;
		while (you > 0 && arr[you] < arr[you - 1]) { //left side is always sorted, so j keeps going back and forth
			Swap(arr[you], arr[you - 1]);            // from index zero to i
			you--;                                   
		}
	}
}

// function to heapify the tree
template<typename Type>
void heapify(Type arr[], int size, int parent) //Bubble/Trickle Down Heapify
{
	int largest = parent; // root is the largest element
	int leftChild = 2 * parent + 1; // left = 2*root + 1
	int rightChild = 2 * parent + 2; // right = 2*root + 2

	// If left child is larger than root
	if (leftChild < size && arr[leftChild] > arr[largest])
		largest = leftChild;

	// If right child is larger than largest so far
	if (rightChild < size && arr[rightChild] > arr[largest])
		largest = rightChild;

	// If largest is not root
	if (largest != parent)
	{
		//swap root and largest
		Swap(arr[parent], arr[largest]);

		// Recursively heapify the sub-tree
		heapify(arr, size, largest);
	}
}

// implementing heap sort
template<typename Type>
void heapSort(Type arr[], int n){
	// build heap
	for (int i = n / 2 - 1; i >= 0; i--) //create root which is n/2-1
		heapify(arr, n, i);

	// extracting elements from heap one by one
	for (int i = n - 1; i >= 0; i--){
		// Move current root to end
		Swap(arr[0], arr[i]);

		// again call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}


//quck sort partition
//similar with selection sort (excepts find the pivot not the smallest)
template<typename Type>
int Partition(Type* arr, int start, int end) {
	Type pivot = arr[end]; //by using pivot we can find partition index (left side is smaller right side is smaller)
	int partitionIndex = start; //set partition index as start index initially

	for (int i = start; i < end; i++) {
		if (arr[i] <= pivot) //compare current index's value with pivot, if smaller, swap with partition index
		{
			swap(arr[i], arr[partitionIndex]); //swap if element is lesser than pivot
			partitionIndex++;
		}
	}
	swap(arr[partitionIndex], arr[end]); //change pivot (end) value at the end
	return partitionIndex;
}


//quick sort
template<typename Type>
void QuickSort(Type* arr, int start, int end){
	if (start >= end)return;
	int partition = Partition(arr, start, end);
	QuickSort(arr, start, partition - 1);  //left side
	QuickSort(arr, partition + 1, end);  //right side
}

/*The gap value specifies the number of interleaved lists.
The array size does not need to be a multiple of the gap value.*/
//shell sort -> different 
template<typename Type>
void ShellSort(Type* arr, int size) {
	int i, temp; //for swapping
	for (int gap = size / 2; gap > 0; gap /= 2) //example, if the size is 9, gap is 4
	{
		for (int j = gap; j < size; j++) //starts from index 4
		{
			temp = arr[j]; //temp value gets the value of index 4
			i = 0;

			for (i = j; i >= gap && arr[i - gap] > temp; i -= gap) //i=j so it is 4 and it is 4>=gap
			{                                                      //arr[4 - 4] > temp (arr[0] value should be bigger than arr[j] (index 4)
				arr[i] = arr[i - gap]; //swap arr[4] and arr[0] 
				arr[i] = temp;                                     //i-= means i is 4, 4-4 0
			}
		}
	}
}

//merge sort
template<typename Type>
void Merge(Type* arr, int left, int mid, int right) {
	int mergedSize = right - left + 1;
	int leftPos = left, rightPos = mid + 1;
	int mergePos = 0;
	Type* merged = new Type[mergedSize];

	while (leftPos <= mid and rightPos <= right) {
		if (arr[leftPos] <= arr[rightPos]) merged[mergePos] = arr[leftPos++];
		else merged[mergePos] = arr[rightPos++];
		mergePos++;
	}
	while (leftPos <= mid) merged[mergePos++] = arr[leftPos++];
	while (rightPos <= right) merged[mergePos++] = arr[rightPos++];

	for (int i = 0; i < mergedSize; i++) { //copy data into the original array
		arr[left + i] = merged[i];
	}
	delete[]merged;
}

template<typename Type>
void MergeSort(Type* arr, int left, int right) {
	if (left >= right) return;
	int mid = (right + left) / 2;
	MergeSort(arr, left, mid);
	MergeSort(arr, mid + 1, right);
	Merge(arr, left, mid, right);
}

//extra
//if you wanna merge two vectors
vector<int> MergeTwoVectors(vector<int>& vec1, vector<int>& vec2) {
	vector<int>finalRes;
	int pos1 = 0, pos2 = 0;
	while (pos1 < vec1.size() && pos2 < vec2.size())
	{
		if (vec1[pos1] < vec2[pos2]) finalRes.push_back(vec1[pos1++]);
		else finalRes.push_back(vec2[pos2++]);
	}
	while (pos1 < vec1.size()) finalRes.push_back(vec1[pos1++]);
	while (pos2 < vec2.size()) finalRes.push_back(vec2[pos2++]);

	return finalRes;
}

vector<int>MergeVectorSort(vector<int>sorted)
{
	if (sorted.size() <= 1) return sorted;

	auto left = sorted.begin();
	auto right = sorted.end();
	auto mid = sorted.begin() + sorted.size() / 2;

	vector<int>leftHalve(left, mid);
	vector<int>rightHalve(mid, right);
	MergeVectorSort(leftHalve);
	MergeVectorSort(rightHalve);
	MergeTwoVectors(leftHalve, rightHalve);
}

//radix sort