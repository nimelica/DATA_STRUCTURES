#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool isOperand(const char& ch)
{
	if (ch >= '0' && ch <= '9')return true;
	if (ch >= 'a' && ch <= 'z')return true;
	if (ch >= 'A' && ch <= 'Z')return true;
	return false;
}

bool isOperator(const char& ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	return false;
}

bool isOpening(char ch)
{
	if (ch == '(' || ch == '{' || ch == '[') return true;
	return false;
}

int getPrecedence(const char& ch)
{
	if (ch == '/' || ch == '*')
		return 1;
	else
		return 0;
}

bool hasHigherPrecedence(const char& val1, const char& val2)
{
	int op1 = getPrecedence(val1);
	int op2 = getPrecedence(val2);

	if (op1 >= op2)
		return true;
}

int PerformOperation(char operation, int operand1, int operand2)
{
	if (operation == '+') return operand1 + operand2;
	else if (operation == '-') return operand1 - operand2;
	else if (operation == '*') return operand1 * operand2;
	else if (operation == '/') return operand1 / operand2;

	else cout << "Unexpected Error \n";
	return -1;
}

string InfixToPostfix(string infix)
{
	stack<char>ops;
	string postfix = "";
	char ch;

	for (int i = 0; i < infix.size(); i++) //(A + B) * C"
	{
		ch = infix[i];

		if (ch == ' ') {
			continue;
		}
		else if (ch == '(') { //stack -> (
			ops.push(ch);
		}
		else if (isOperand(ch))
		{
			postfix += ch; //A, AB
		}
		else if (isOperator(ch)) // ) is not operator
		{
			//ops.push(ch); //you can also push it here
			while (!ops.empty() && !hasHigherPrecedence(ch, ops.top())) //in the first operator loop does not work cuz stack is empty
			{
				postfix += ops.top();
				ops.pop();
			}
			ops.push(ch); // + (
		}
		else if (ch == ')') //don't push closing paranthesis
		{
			while (!ops.empty() && ops.top() != '(')
			{
				postfix += ops.top(); //AB+
				ops.pop();
			}
			ops.pop(); //remove '(' from the stack
		}
	}
	while (!ops.empty())
	{
		postfix += ops.top();
		ops.pop();
	}
	return postfix;
}

string PrefixToPostfix(string prefix)
{
	stack<string>oper;
	string postfix = "";
	char ch;
	//to postfix -> APPEND -> start from end
	//if operand->push into stack 
	//if operator->append string
	for (int i = prefix.length() - 1; i >= 0; i--)
	{
		ch = prefix[i];

		if (ch == ' ') {
			continue;
		}
		else if (isOperand(ch))
		{
			oper.push(string(1, ch));
		}
		else if (isOperator(ch))
		{
			string op1 = oper.top(); oper.pop();
			string op2 = oper.top(); oper.pop();

			postfix = op1 + op2 + ch;
			oper.push(postfix);
		}
		else {
			cerr << "Invalid input!\n";
		}
	}
	return oper.top();
}

string PostfixToPrefix(string postfix)
{
	//Prepend char operator -> start from the beginning (reverse order operand)
	//operands into the stack
	stack<string>oper;
	char ch;
	string prefix;

	for (int i = 0; i < postfix.length(); i++)
	{
		ch = postfix[i];

		if (ch == ' ') {
			continue;
		}
		else if (isOperator(ch))
		{
			oper.push(string(1, ch));
		}
		else if (isOperand(ch))
		{
			string op2 = oper.top(); oper.pop();
			string op1 = oper.top(); oper.pop();

			prefix = ch + op1 + op2;
			oper.push(prefix);
		}
		else {
			cerr << "Invalid input!\n";
		}
	}
	return oper.top();
}

int EvaluateSingleDigitPostfix(string exp)
{
	// create an empty stack
	stack<int> stack;
	char ch;

	// traverse the given expression
	for (int i = 0; i < exp.length(); i++)
	{
		ch = exp[i];
		// if the current character is an operand, push it into the stack
		if (ch == ' ')continue;
		else if (ch >= '0' && ch <= '9') {
			stack.push(ch - '0');
		}
		// if the current character is an operator
		else {
			// remove the top two elements from the stack
			int second = stack.top();
			stack.pop();

			int first = stack.top();
			stack.pop();

			// evaluate the expression `x op y`, and push the
			// result back to the stack
			int result = PerformOperation(ch, first, second);
			stack.push(result);
		}
	}
	// At this point, the stack is left with only one element, i.e.,
	// expression result
	return stack.top();
}

int EvaluateMultiDigitPostfix(string postfix_notation)
{
	int spaceIndex = postfix_notation.find(' '); //returns the index of the digit we looking for
	stack<int> s;
	bool last = true;
	while (spaceIndex != -1 || last) //if it is -1, it means space not found
	{
		string s_now;
		if (spaceIndex == -1)
		{
			last = false;
			s_now = postfix_notation;
		}
		else
		{
			s_now = postfix_notation.substr(0, spaceIndex);
			postfix_notation = postfix_notation.substr(spaceIndex + 1);
			spaceIndex = postfix_notation.find(' ');
		}
		if (s_now.at(0) < '0' || s_now.at(0) > '9')
		{
			//s_now is an operator
			int second = s.top();
			s.pop();
			int first = s.top();
			s.pop();
			int result;
			switch (s_now.at(0))
			{
			case '+':
				result = first + second;
				break;
			case '-':
				result = first - second;
				break;
			case '*':
				result = first * second;
				break;
			case '/':
				result = first / second;
				break;
			}
			s.push(result);
		}
		else
		{
			int now = stoi(s_now);
			s.push(now);
		}
	}
	int final_result = s.top();
	return final_result;
}

int evalRPN(vector<string>& tokens) {
	stack<int> st;
	int val1 = 0, val2 = 0;
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i] == "+") {
			val2 = st.top(); st.pop();
			val1 = st.top(); st.pop();
			st.push(val1 + val2);
		}
		else if (tokens[i] == "-") {
			val2 = st.top(); st.pop();
			val1 = st.top(); st.pop();
			st.push(val1 - val2);
		}
		else if (tokens[i] == "*") {
			val2 = st.top(); st.pop();
			val1 = st.top(); st.pop();
			st.push(val1 * val2);
		}
		else if (tokens[i] == "/") {
			val2 = st.top(); st.pop();
			val1 = st.top(); st.pop();
			st.push(val1 / val2);
		}
		else {
			st.push(stoi(tokens[i]));
		}
	}
	return st.top();
}

bool isValid(string s)
{
	stack<char>brackets;
	unordered_map<char, char>match{ {'(' ,')'}, {'{','}'}, {'[',']'} };

	for (auto ch : s)
	{
		if (isOpening(ch))
			brackets.push(ch);
		else {
			if (brackets.empty()) return false; //we have closing, but it does not have opening bracket to match in stack 

			if (match[brackets.top()] == ch) {
				brackets.pop();
			}
			else {
				return false;
			}
		}
	}
	//is stack is fully empty
	return brackets.empty();
}

string reverseString(string input) {
	stack<string>st;
	string res = "";

	int spacePos = input.find(' ');
	while (spacePos != -1) {
		res = input.substr(0, spacePos);
		st.push(res);
		input = input.substr(spacePos + 1);
		spacePos = input.find(' ');
	}
	st.push(input.substr(0));
	string output = "";
	while (!st.empty()) {
		if (output != "")
			output += " ";
		output += st.top(); st.pop();
	}
	return output;
}
