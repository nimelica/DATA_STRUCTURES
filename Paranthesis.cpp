#include <vector>
#include <sstream>
#include <stack>
#include <iostream>
using namespace std;

bool isValid(string s) {
    if (s.length() % 2 != 0) return false;

    stack<char>sc;
    for (auto x : s) {
        if (x == '(' or x == '[' or x == '{') sc.push(x);
        else if (x == ')' and !sc.empty() and sc.top() == '(') sc.pop();
        else if (x == '}' and !sc.empty() and sc.top() == '{') sc.pop();
        else if (x == ']' and !sc.empty() and sc.top() == '[') sc.pop();
        else return false;
    }
    return sc.empty() ? true : false;
}

string reverseWords(string s) {
    stringstream ss(s);
    string word = "";
    stack<string>words;

    while (ss >> word) {
        words.push(word);
    }
    string output = "";
    while (!words.empty()) {
        output += words.top() + " "; words.pop();
    }
    output.erase(output.end() - 1);
    return output;
}

string reverseString(string input)
{
    stack<string> s;
    int index = input.find(' ');
    while (index != -1)
    {
        s.push(input.substr(0, index));
        input = input.substr(index + 1);
        index = input.find(' ');
    }
    s.push(input.substr(0));
    string output;
    while (!s.empty())
    {
        if (output != "")
            output += " ";
        output += s.top();
        s.pop();
    }
    return output;
}

string reverseSentence(string input) {
    stack<string>storage;
    string temp = "";
    for (int i = 0; i < input.size(); i++) {
        if (temp == "")  while (input[i] == ' ') i++; //skip whitesapces
        if (!isspace(input[i])) temp += input[i];     //append characters into a string if they are not a space
        if (input[i] == ' ' || i == input.length() - 1) { //when you reach the end of the word/line;
            if (temp != "")   storage.push(temp); //if word is not empty, push it into the stack
            temp = "";  //reset string
        }
    }
    string output = "";
    while (!storage.empty()) {
        output += storage.top(); storage.pop();
        if (!storage.empty()) {
            output += ' ';
        }
    }
    return output;
}