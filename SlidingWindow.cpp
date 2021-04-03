#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map> 
#include <unordered_set>
using namespace std;

int expandFromMiddle(string s, int left, int right)
{
	if (s.empty() || left > right) return 0;

	while (left >= 0 && right < s.size() && s[left] == s[right])
	{
		left--;
		right++;
	}
}

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
