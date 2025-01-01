#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

#define max 50
template<class ItemType>
class Stack {
private:
	int top;
	ItemType* items;
public:
	Stack()
	{
		top = -1;
		items = new ItemType[max];
	}

	void push(ItemType item)
	{
		if (isFull())
		{
			cout << "Overflow";
			return;
		}
		top++;
		items[top] = item;

	}
	ItemType pop() {
		if (isEmpty()) {
			cout << "Underflow ";
			exit(1);
		}
		ItemType item = items[top];
		top--;
		return item;
	}
	bool isFull()const
	{
		return(top == max - 1);
	}
	bool isEmpty()const
	{
		return(top == -1);

	}
	ItemType peek() {
		if (isEmpty()) {
			cout << "stack underflow!";
			return ItemType();
		}
		return items[top];
	}
	
		int prec(char op) 
		{
			if (op == '^')
				return 3;
			else if (op == '/' || op == '*' || op == '%')
				return 2;
			else if (op == '+' || op == '-')
				return 1;
			else if (op == '(' || op == '{' || op == '[' || op == ')' || op == '}' || op == ']')
				return -1;  
			
		}

	
	bool isAlpha(char ch)
	{
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			return true;
		else return false;
	}
	bool isDigit(char ch)
	{
		if (ch >= '0' && ch <= '9'){ return true; }
			
		else return false;
	}
	string convertToPostfix(string infix, Stack& s)
	{
		string postfix;
		for (size_t i = 0; i < infix.size(); i++)
		{
			if (infix[i] == ' ')
			{
				continue;
			}
			if (isAlpha(infix[i]))
			{
				postfix += infix[i]; continue;
			}
			if (isDigit(infix[i]))
			{
				postfix += infix[i]; continue;
			}
			else if (s.isEmpty() || infix[i] == '(' || infix[i] == '{' || infix[i] == '[')
			{
				s.push(infix[i]); continue;
			}
			else if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']')
			{
				if (infix[i] == ')')
				{
					while (s.items[s.top] != '(')
					{
						if (s.items[s.top] == '}' || s.items[s.top] == ']')
						{
							cout << "Invalid ";
							return postfix;
						}
						postfix += s.pop();
					}
					s.pop();
				}

				if (infix[i] == '}')
				{
					while (s.items[s.top] != '{')
					{
						if (s.items[s.top] == ')' || s.items[s.top] == ']')
						{
							cout << "Invalid ";
							return postfix;
						}
						postfix += s.pop();
					}
					s.pop();
				}

				if (infix[i] == ']')
				{
					while (s.items[s.top] != '[')
					{
						if (s.items[s.top] == '}' || s.items[s.top] == ')')
						{
							cout << "Invalid ";
							return postfix;
						}
						postfix += s.pop();
					}
					s.pop();
				}


			}

			else {
				while (!s.isEmpty() && prec(s.items[s.top]) >= prec(infix[i])) {
					postfix += s.pop();
				}
				s.push(infix[i]);
			}

		}
		while (s.isEmpty() == false) {

			if (!(s.peek() == '(' || s.peek() == '[' || s.peek() == '{')) {
				postfix += s.pop();
			}
		}
		return postfix;
	}
	string convertToPrefix(string infix)
	{
		reverse(infix.begin(), infix.end());
		Stack <char>s;
		string prefix;
		for (size_t i = 0; i < infix.size(); i++)
		{
			if (infix[i] == ' ')
			{
				continue;
			}
			if (isAlpha(infix[i]))
			{
				prefix += infix[i]; continue;
			}
			if (isDigit(infix[i])) { prefix += infix[i]; continue; }

			else if (s.isEmpty() || infix[i] == ')' || infix[i] == '}' || infix[i] == ']')
			{
				s.push(infix[i]); continue;
			}
			else if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[')
			{
				if (infix[i] == '(')
				{
					while (s.items[s.top] != ')')
					{
						if (s.items[s.top] == '{' || s.items[s.top] == '[')
						{
							cout << "Invalid ";
							return prefix;
						}
						prefix += s.pop();
					}
					s.pop();
				}

				if (infix[i] == '{')
				{
					while (s.items[s.top] != '}')
					{
						if (s.items[s.top] == '(' || s.items[s.top] == '[')
						{
							cout << "Invalid ";
							return prefix;
						}
						prefix += s.pop();
					}
					s.pop();
				}

				if (infix[i] == '[')
				{
					while (s.items[s.top] != ']')
					{
						if (s.items[s.top] == '{' || s.items[s.top] == '[')
						{
							cout << "Invalid ";
							return prefix;
						}
						prefix += s.pop();
					}
					s.pop();
				}


			}
			else if (prec(s.items[top]) >= prec(infix[i]))
			{
				prefix += s.pop();

			}
			else {
				while (!s.isEmpty() && prec(s.items[s.top]) >= prec(infix[i])) {
					prefix += s.pop();
				}
				s.push(infix[i]);
			}

		}
		while (s.isEmpty() == false) {

			if (!(s.peek() == ')' || s.peek() == ']' || s.peek() == '}')) {
				prefix += s.pop();
			}
		}
		reverse(prefix.begin(), prefix.end());
		return prefix;
	}
	double postfixEvaluation(string exp)
	{
		Stack<double> s; 
		double op1, op2;

		for (size_t i = 0; i < exp.size(); i++)
		{
			if (isDigit(exp[i]))
			{
				s.push(exp[i] - '0'); 
				continue;
			}

			if (isAlpha(exp[i])) {
				s.push(s.assignValuesAlpha(exp[i])); 
				continue;
			}

	
			op2 = s.pop();
			op1 = s.pop();

			switch (exp[i])
			{
			case '+':
				s.push(op1 + op2);
				break;
			case '-':
				s.push(op1 - op2);
				break;
			case '*':
				s.push(op1 * op2);
				break;
			case '/':
				if (op1 != 0) 
					s.push(op1 / op2);
				else {
					cout << "Error: Division by zero." << endl;
					return -1; 
				}
				break;
			default:
				cout << "Invalid operator: " << exp[i] << endl;
				return -1;
			}
		}
		double r = s.pop();
		return r;
	}
	int assignValuesAlpha(char ch) {
		if (ch >= 'a' && ch <= 'z') {
			return (ch - 'a' + 1);
		}
		else if (ch >= 'A' && ch <= 'Z') {
			return (ch - 'A' + 1);
		}
		else {
			cout << "Invalid character!" << endl;
			return 0;
		}
	}
	double prefixEvaluation(string exp, int size)
	{
		Stack <double>s;
		double op1 = 0, op2 = 0;

		for (int i=size-1;i>=0; i--)
		{

			if (isDigit(exp[i])) {
				s.push(static_cast<double>(exp[i] - '0'));
				continue;
			}
			if (isAlpha(exp[i])) {
				s.push(static_cast<double>(s.assignValuesAlpha(exp[i])));
				continue;
			}
			else {
				if (s.isEmpty()) {
					cout << " Stack Underflow" << endl;
					return -1;
				}
				op1 = s.pop();
				if (s.isEmpty()) {
					cout << " Stack Underflow" << endl;
					return -1;
				}
				op2 = s.pop();
				switch (exp[i]) {
				case '+':
					s.push(op1 + op2);
					break;
				case '-':
					s.push(op1 - op2);
					break;
				case '*':
					s.push(op1 * op2);
					break;
				case '%':
					s.push(static_cast<int>(op2) % static_cast<int>(op1));
					break;
				case '/':
					if (op2 == 0) {
						cout << "Error: Division by zero.\n";
						return -1;
					}
					s.push(op1 / op2);
					break;
				case '^':
					s.push(pow(op1, op2));
					break;
				default:
					cout << "Invalid operator: " << exp[i] << endl;
					return -1;
				}
			}
		}
		if (s.isEmpty()) {
			cout << "Error: No result available.\n";
			return -1; // Error case
		}
		return s.pop();
	}
};

bool isEmptyOrNull(string& str) {
	for (char ch : str) {
		if (!isspace(ch)) {
			return false; // Found a non-whitespace character
		}
	}
	return true; // All characters were null
}
bool isBalanced(Stack<char> stack, string& infix)
{
	bool flag = true;
	flag = isEmptyOrNull(infix);
	if (flag) return false;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
			continue;
		if (infix[i] == '{' || infix[i] == '[' || infix[i] == '(')
		{
			stack.push(infix[i]);
		}
		if (infix[i] == '}' || infix[i] == ']' || infix[i] == ')')
		{
			if (stack.isEmpty()) { return false; }
			if (infix[i] == ')')
			{
				if (stack.peek() == '(')
				{
					stack.pop();
					continue;
				}
				else
				{
					return false;
				}
			}
			if (infix[i] == '}')
			{

				if (stack.peek() == '{')
				{
					stack.pop();
					continue;
				}
				else
				{
					return false;
				}

			}
			if (infix[i] == ']')
			{

				if (stack.peek() == '[')
				{
					stack.pop();
					continue;
				}
				else
				{
					return false;
				}
			}
		}

	}
	if (stack.isEmpty() == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}
int Multiplication(int number, int multiplier)
{
	if (multiplier == 1)
	{
		return number;
	}
	else
	{
		return(Multiplication(number, multiplier - 1) + number);
	}

}

int Power(int number, int power)
{
	if (power == 0)
		return 1;
	else
		return(number * Power(number, power - 1));
}


int main() {
	Stack <char>stack;
	int choice;
	string infix;
	string postfix;
	string prefix;
	bool res;
	//char ch;
	do
	{
		cout << "Enter 1 to convert to postfix\nEnter 2 to convert to prefix\nEnter 3 for postfix evaluation\nEnter 4 for Prefix evaluation\nEnter 5 for Multipliaction\nEnter 6 for finding Power: ";
		cin >> choice;
		cin.ignore();
		if (choice == 1)
		{
			cout << "Enter Your String: ";
			getline(cin, infix);
			res = isBalanced(stack, infix);
			if (!res) { cout << "Invalid Expression";	return 0; }
			//sending char type stack which is ok
			postfix = stack.convertToPostfix(infix, stack);
			cout << "Postfix Expression: " << postfix << endl;
		}
		if (choice == 2)
		{
			cout << "Enter Your String: ";
			getline(cin, infix);
			bool res;
			//sending char type stack which is ok
			res = isBalanced(stack, infix);
			if (!res) { cout << "Invalid Expression";	return 0; }
			prefix = stack.convertToPrefix(infix);
			cout << "Prefix Expression: " << prefix << endl;
		}
		if (choice == 3) {
			cout << "Enter Your String in infix: ";
			getline(cin, infix);
			res = isBalanced(stack, infix);
			if (!res) {
				cout << "Invalid Expression";
				return 0;
			}

			postfix = stack.convertToPostfix(infix, stack);
			cout << "Postfix expression: " << postfix << endl;
			Stack<double> numStack;  
			cout << "Evaluated Value: ";
			double postValue = numStack.postfixEvaluation(postfix);  
			cout << postValue << endl;
		}

		if (choice == 4)
		{
			cout << "Enter Your String in infix: ";
			getline(cin, infix);
			res = isBalanced(stack, infix);
			if (!res) { cout << "Invalid Expression";	return 0; }
			string prefix = stack.convertToPrefix(infix);
			cout << "Prefix expression: " << prefix << endl;
			double v = 0;
			cout << "Evaluated Value: ";
			size_t i = prefix.size(); // Change from double to size_t
			v = stack.prefixEvaluation(prefix, static_cast<int>(i));
			cout << v << endl;
		}
		if (choice == 5)
		{
			int number = 0, multiplier = 0;
			cout << "Enter Number: ";
			cin >> number;
			cout << "Enter its multiplier: ";
			cin >> multiplier;
			cout << number << "*" << multiplier << "=" << Multiplication(number, multiplier) << endl << endl;
		}
		if (choice == 6)
		{
			int number = 0, pow = 0;
			cout << "Enter Number: ";
			cin >> number;
			cout << "Enter its power: ";
			cin >> pow;
			cout << number << "^" << pow << "=" << Power(number, pow) << endl << endl;
		}
	} while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6);
	return 0;
}