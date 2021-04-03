#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map> 
#include <map>
#include <queue>
#include <unordered_set>
using namespace std;

//unordered_map is a Hash Table implementation that uses hash function to put data in unordered indexes
bool isAllUnique(string s)
{
	unordered_map<char, int>charMap;
	for (int i = 0; i < s.size(); i++)
	{
		if (charMap.find(s[i]) == charMap.end()) {
			charMap.insert({ s[i], 1 });
		}
		else return false;
	}
	return true;
}

bool isAnagram(string s, string t)
{
    unordered_map<char, int> charMap;
    for (auto it : s) charMap[it]++;
    for (auto it : t) charMap[it]--;
    for (auto it : charMap) if (it.second != 0) return false;
    return true;
}

void UniqueFruits()
{
    map<string, int>ordered_fruits;
    fstream fin("mapInput.txt");
    if (!fin) { cerr << "ERROR: FILE NOT FOUND!\n"; }
    int size{}; fin >> size;
    string fruit = "";

    for (size_t i = 0; i < size; i++) {
        fin >> fruit;
        auto freq = ordered_fruits.find(fruit);
        if (freq == ordered_fruits.end()) { //fruit count is only one since we do not encounter with same fruit again (all unique)
            ordered_fruits[fruit] = 1;
        }
        else { //we found same fruit
            //freq->second++;
            ordered_fruits[fruit]++;
            cout << freq->first << " is already exists, incrementing count->" << freq->second << " " << endl;
        }
    }
    map<string, int>::iterator it;
    it = ordered_fruits.begin();
    for (; it != ordered_fruits.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }

    for (auto& it : ordered_fruits) {
        cout << it.first << ": " << it.second << endl;
    }
}

bool uniqueOccurrences(vector<int>& arr)
{
    unordered_map<int, int>occurs;
    int size = arr.size();

    for (auto& num : arr) {
        occurs[num]++;
    }

    auto iter1 = occurs.begin();
    while (iter1 != occurs.end()) {
        auto iter2 = occurs.begin();
        while (iter2 != occurs.end()) {
            if (iter1 != iter2 && iter1->second == iter2->second) return false;
            iter2++;
        }
        iter1++;
    }
    return true;
}

vector<int> topKFrequent(vector<int>& nums, int k) {
    vector<int>results;
    unordered_map<int, int>MAP;
    for (auto x : nums) MAP[x]++;

    priority_queue<pair<int, int>>pq;
    for (auto x : MAP) pq.push({ x.second, x.first });

    while (k--) {
        results.push_back(pq.top().second);
        pq.pop();
    }
    return results;
}

/* bool uniqueOccurrences(vector<int>& arr)
    {
        map<int,int> m;
        map<int,int> c;
        for(int i=0;i<arr.size();i++)
        {
            m[arr[i]]++;
        }
        for(map<int,int>::iterator it=m.begin();it!=m.end();it++)
        {
            c[it->second]++;
            if(c[it->second]>1)
            {
                return false;
            }
        }
        return true;
    }*/

int lengthOfLongestSubstring(string s)
{
    if (s.size() < 2) return s.size();
    unordered_set<char>hash_set;
    int i = 0, j = 0, maxSet = 0;

    while (j < s.size())
    {
        if (hash_set.find(s[j]) == hash_set.end()) //if is not in the hash set already, add it
        {
            hash_set.insert(s[j]); j++; //pointer j continue
            maxSet = max(maxSet, (int)hash_set.size());
        }
        else { //if character in hash set already
            //remove all characters from the beginning
            hash_set.erase(s[i]); i++;
        }
    }
    return maxSet;
}

vector<int> twoSum(vector<int>& nums, int target)
{
	unordered_map<int, int>indices; //first int shows the value, second shows the index
	int diff;
	for (int i = 0; i < nums.size(); i++)
	{
		diff = target - nums[i];

		if (indices.find(diff) != indices.end()) //data found, note: same as saying indices.count(diff)
		{
			return vector<int>{i, indices[diff]}; //to insert multiple values in a vector
		}
		else {
			indices[i] = i; //fill up the map
		}
	}
	return {}; //same as saying NULL
}

int singleNumber(vector<int>& nums)
{
	unordered_map<int, int>freq; //frequencies

	for (int i = 0; i < nums.size(); i++) {
		freq[nums[i]]++;
	}
	unordered_map<int, int>::iterator it;
	for (it = freq.begin(); it != freq.end(); it++) {
		if (it->second == 1) {
			return it->first;
		}
	}
	return 0;
}

bool isHappy(int n)
{
    unordered_map<int, int>hash_table;

    //do summation of square of each digit and store the sum in hash table
    //stop when sum is 1
    //every time check if the value exists in hash table

    int sum = n;
    while (sum != 1)
    {
        //if value is not exist in map, add it, else; return false;
        //Because all elements in an unordered_map container are unique, the function can only 
        //return 1 (if the element is found) or zero (otherwise)

        if (hash_table.count(n) == 0) //data not added yet!
            hash_table[n]++;
        else
            return false;

        sum = 0;

        while (n)
        {
            //convert number into a single digit
            int digit = n % 10;
            sum += pow(digit, 2);
            n /= 10;
        }
        n = sum;
    }
    return true;
}

