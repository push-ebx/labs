#include <iostream>
#include <string>
#include <vector>
#include <queue>

using std::cout;
using std::cin;
using std::endl;
using std::queue;
using std::string;
using std::vector;

#define is_operator(c) (c == '&' || c == '|' || c == '!')
#define is_operand(c) (c == '1' || c == '0' || c == 'x' || c == 'X')

struct Node;
int get_priority(char op);
string remove_extra(string expr);
bool op_left_assoc(const char c);
queue<char> generate_postfix_exp(string expr);
int get_operand(int x, char oper);
int calculate_simple_expr(char op, char op1_c, char op2_c, int x);
char calculate(string expression, int x);
Node *create_tree(string expression);
void tree_print(Node *node);
void print_postfix(queue<char> _queue);
bool checking_for_emptiness(string expr);

struct Node
{
	char value;
	Node *left = NULL;
	Node *right = NULL;
};

int main()
{
	string expression;
	int x;
	cout << "Enter expression: ";
	cin >> expression;
	cout << "Enter x: ";
	cin >> x;
	cout << calculate(remove_extra(expression), x) << endl;
	return 0;
}

bool checking_for_emptiness(string expr)
{
	for (size_t i = 0; i < expr.size(); i++)
		if (expr[i] != ' ' && expr[i] != '(' && expr[i] != ')')
			return false;
	return true;
}

void print_postfix(queue<char> _queue)
{
	int size_q = _queue.size();
	for (size_t i = 0; i < size_q; i++)
	{
		cout << _queue.front();
		_queue.pop();
	}
	cout << endl;
}

int get_priority(char op)
{
	switch (op)
	{
	case '!':
		return 3;
	case '&':
		return 2;
	case '|':
		return 1;
	}
	return 0;
}

string remove_extra(string expr)
{
	string new_expr = "";
	for (size_t i = 0; i < expr.size(); i++)
	{
		if (expr[i] == '|' || expr[i] == '&')
			i++;
		new_expr += expr[i]; 
	}
	return new_expr;
}

bool op_left_assoc(const char c)
{
	switch (c)
	{
	case '*':
	case '/':
	case '%':
	case '+':
	case '-':
	case '=':
		return true;
	case '!':
		return false;
	}
	return false;
}

queue<char> generate_postfix_exp(string expr)
{
	queue<char> _queue;
	vector<char> _stack;

	for (size_t i = 0; i < expr.size(); i++)
	{
		char op = expr[i];
		if (is_operand(op))
			_queue.push(op);
		if (is_operator(op))
		{
			if (!_stack.empty())
			{
				while (is_operator(_stack.back()) && (op_left_assoc(op) &&
							get_priority(_stack.back()) >= get_priority(op)) ||
							!op_left_assoc(op) &&
							get_priority(_stack.back()) > get_priority(op))
				{

					_queue.push(_stack.back());
					_stack.pop_back();
				}
			}
			_stack.push_back(op);
		}
		if (op == '(')
			_stack.push_back(op);
		if (op == ')')
		{
			while (_stack.back() != '(')
			{
				_queue.push(_stack.back());
				_stack.pop_back();
			}
			_stack.pop_back();
		}
	}

	for (size_t i = 0; !_stack.empty(); i++)
	{
		_queue.push(_stack.back());
		_stack.pop_back();
	}
	return _queue;
}

int get_operand(int x, char oper)
{
	if (oper == 'x')
		return x;
	else if (oper == '1')
		return 1;
	else if (oper == '0')
		return 0;
	return -1;
}

int calculate_simple_expr(char op, char op1_c, char op2_c, int x)
{
	int op1 = get_operand(x, op1_c);
	int op2 = get_operand(x, op2_c);

	if (op == '&')
		return op1 && op2;
	else if (op == '|')
		return op1 || op2;
	else if (op == '!')
		return !op1;
	return 0;
}

void calculate_tree(Node *node, int x)
{
	char op, op1, op2;

	if (node != NULL)
	{
		calculate_tree(node->left, x);
		calculate_tree(node->right, x);
		op = node->value;
		if (is_operator(op))
		{
			if (op != '!')
				op2 = node->right->value;
			else
				op2 = 0;
			op1 = node->left->value;
			node->value = calculate_simple_expr(op, op1, op2, x) + '0';
		}
	}
}

char calculate(string expression, int x)
{	
	if (checking_for_emptiness(expression)){
		cout << "The expression is empty";
		return 0;
	}
	vector<char> _stack;
	Node *root = create_tree(expression);
	calculate_tree(root, x);
	return root->value;
}

Node *create_tree(string expression)
{
	queue<char> postfix_expr = generate_postfix_exp(expression);
	int queue_size = postfix_expr.size();
	vector<Node *> _stack;
	char op;

	for (size_t i = 0; i < queue_size; i++)
	{
		op = postfix_expr.front();
		if (is_operand(op))
		{
			Node *node = new Node;
			node->value = op;
			_stack.push_back(node);
		}
		else if (is_operator(op))
		{
			Node *node = new Node;
			if (op != '!')
			{
				node->right = _stack.back();
				_stack.pop_back();
			}
			node->left = _stack.back();
			_stack.pop_back();
			node->value = op;

			_stack.push_back(node);
		}
		postfix_expr.pop();
	}
	return _stack.at(0);
}

void tree_print(Node *node)
{
	if (node != NULL)
	{
		tree_print(node->left);
		tree_print(node->right);
		cout << node->value;
	}
}
