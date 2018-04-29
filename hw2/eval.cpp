#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result)
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.
{
	// Corner case: empty expression
	if (infix.size() == 0) 
		return 1;

	// Remove blanks in the expression
	std::string infixCompact;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] != ' ')
			infixCompact += infix[i];
	}
	// Corner case: empty expression
	if (infixCompact.size() == 0)
		return 1;

	// CONVERT INFIX TO POSTFIX
	// Check syntactically validity: 
	// 1. flags; 2. compatible neighbors (special cases for head and tail)
	// Initialization
	std::string  tempPostfix = ""; // empty string
	stack<char> operatorStack;
	int operandFlag = -1; // check #operand != 0
	int cl = 0, cr = 0; // check #left parenthesis == #right parenthesis
	// char-by-char convertion & check
	for (int i = 0; i < infixCompact.size(); i++)
	{
		char ch = infixCompact[i];

		if (islower(ch))
		{
			// check
			operandFlag = 0; 
			if (i > 0 && (islower(infixCompact[i - 1]) || infixCompact[i - 1] == ')'))
				return 1;
			// operation
			tempPostfix += ch;
		}
		else if (ch == '(')
		{
			// check
			cl++;
			if (i > 0 && (islower(infixCompact[i - 1]) || infixCompact[i - 1] == ')'))
				return 1;
			if (i == infixCompact.size() - 1)
				return 1;
			// operation
			operatorStack.push(ch);
		}		
		else if (ch == ')')
		{
			// check
			cr++;
			if (i == 0)
				return 1;
			else if (i > 0)
			{
				char j = infixCompact[i - 1];
				if (j == '(' || j == '+' || j == '-' || j == '*' || j == '/')
					return 1;
			}
			// operation
			while (operatorStack.top() != '(')
			{
				tempPostfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop();
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			// check
			if (i == 0 || i == infixCompact.size()- 1)
				return 1;
			else if (i > 0)
			{
				char j = infixCompact[i - 1];
				if (j == '(' || j == '+' || j == '-' || j == '*' || j == '/')
					return 1;
			}
			// operation
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				if ((ch == '*' || ch == '/') && (operatorStack.top() != '+' || operatorStack.top() != '-'))
					break;
				tempPostfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(ch);
		}
		else // other chars
			return 1; // invalid
	}
	// Final checks on #operand, #left parenthesis, #right parenthesis
	if (operandFlag != 0 || cl != cr)
		return 1;
	// Append remaining operators in the stack 
	while (!operatorStack.empty())
	{
		tempPostfix += operatorStack.top();
		operatorStack.pop();
	}
	// Assignment after convertion
	postfix = tempPostfix;

	// EVALUTION ON POSTFIX
	// Initialization
	stack<int> operandStack;
	for (int i = 0; i < postfix.size(); i++)
	{
		char ch = postfix[i];
		if (islower(ch))
		{
			if (values.contains(ch))
			{
				int v;
				values.get(ch, v);
				operandStack.push(v);
			}
			else
				return 2; // no matched int value
		}
		else
		{
			int v2 = operandStack.top();
			operandStack.pop();
			int v1 = operandStack.top();
			operandStack.pop();
			switch (ch)
			{ 
				case '+':
					operandStack.push(v1 + v2);
					break;
				case '-':
					operandStack.push(v1 - v2);
					break;
				case '*':
					operandStack.push(v1 * v2);
					break;
				case '/':
					if (v2 == 0)
						return 3; // devided by 0
					else
						operandStack.push(v1 / v2);
					break;			
			}
		}
	}
	result = operandStack.top(); // assignment for valid expression and matched operands
	operandStack.pop();
	return 0;
}

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+"  &&  answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*"  &&  answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+"  &&  answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/"  &&  answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	cout << "Passed all tests" << endl;
}