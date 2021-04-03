#include <iostream>
#include <string>
#include <vector>
using namespace std;


int LinearSearch(int array[], int size, int seachValue) {
    int count = 0; //count how many compostions happened

    for (int i = 0; i < size; i++) {
        count++;
        if (seachValue == array[i]) {
            return i;
        }
    }
    return -1;
}

int RecursiveBinarySearch(int array[], int left, int right, int key)
{
    if (left <= right) {
        int mid = (left + right) / 2;
        //or int midpoint = left + (right-left)/2

        if (mid == key) {
            return mid;
        }
        if (key < array[mid]) {
            return RecursiveBinarySearch(array, left, mid - 1, key);
        }
        else {
            return RecursiveBinarySearch(array, mid + 1, right, key);
        }
    }
    // We reach here when element is not 
    // present in array 
    return -1;
}

int binary_search(int A[], int N, int key) {
    int low, high, mid;
    low = 1;
    high = N;
    int count = 0;
    while (low <= high) {
        mid = (low + high) / 2; //or say low + (high-low)/2
        if (A[mid] == key) {
            return mid; // a match is found
        }
        else if (A[mid] < key) { // if middle element is less than the key 
            low = mid + 1;     // key will be right part if it exists
        }
        else  high = mid - 1;    // otherwise key will be in left part if it exists
        count++;
    }
    return -1; // indicating no such key exists 
}