#pragma once
#include <sstream>
#include <stack>
#include "IntegerSet.h"

IntegerSet::IntegerSet() : root(nullptr)
{};

IntegerSet::IntegerSet(const IntegerSet& other)
{
	try {
		root = copy(other.root);
	}
	catch (...)
	{
		clear(root);
		throw std::bad_alloc();
	}
};

IntegerSet& IntegerSet::operator=(const IntegerSet& other)
{
	if (this != &other)
	{
		clear(root);
		try {
			root = copy(other.root);
		}
		catch (...)
		{
			clear(root);
			throw std::bad_alloc();
		}
		
		
    }
	return *this;
}

IntegerSet::~IntegerSet()
{
	clear(root);
}

size_t IntegerSet::size(Node* root) const
{
	if (!root) { return 0; }
	return 1 + size(root->left) + size(root->right);

}
size_t IntegerSet::size() const
{
	return size(root);
}

void IntegerSet::postOrderTraversal(Node*& node, std::stack<int>& resultStack) const
{
	if (!node)
	{
		return;
	}
	postOrderTraversal(node->right, resultStack);
	resultStack.push(node->value);
	postOrderTraversal(node->left, resultStack);

}

bool IntegerSet::equals(Node* root1,Node* root2) const
{

	if (!root1 && !root2) { return true; }
	if (root1 && !root2 || !root1 && root2) { return false; }
	std::stack<int> stack1;
	postOrderTraversal(root1, stack1);
	std::stack<int> stack2;
	postOrderTraversal(root2, stack2);

	while (!stack1.empty() && !stack2.empty())
	{
		if (stack1.top() == stack2.top())
		{
			stack1.pop();
			stack2.pop();
		}
		
		else
		{
			return false;
		}
	}
}

bool IntegerSet::equals(const IntegerSet& other) const
{
	return equals(this->root, other.root);
}

bool IntegerSet::contains(int elem, Node* root) const
{
	if (!root) { return false; }
	if (elem < root->value) { return contains(elem, root->left); }
	if (elem > root->value) { return contains(elem, root->right); }
	return true;
}
bool IntegerSet::contains(int elem) const
{
	return contains(elem, root);
}

bool IntegerSet::subsetOf(Node* root1,Node* root2) const
{
	if (!root1) { return true; }

	if (!root2) { return false; }

	std::stack<int> stack1;
	postOrderTraversal(root1, stack1);
	std::stack<int> stack2;
	postOrderTraversal(root2, stack2);
	while (!stack1.empty())
	{
		if (stack1.top() == stack2.top())
		{
			stack1.pop();
			stack2.pop();
		}
		else if (stack1.top() > stack2.top())
		{
			stack2.pop();
		}
		else
		{
			return false;
		}
	}
}
bool IntegerSet::subsetOf(const IntegerSet& other) const
{

	return subsetOf(root, other.root);
}

IntegerSet IntegerSet::getUnion(Node* root1, Node* root2) const
{
	std::stack<int> stack1;
	postOrderTraversal(root1, stack1);
	std::stack<int> stack2;
	postOrderTraversal(root2, stack2);
	IntegerSet result;
	while (!stack1.empty() && !stack2.empty())
	{
		if (stack1.top() == stack2.top())
		{
			result.insert(stack1.top());
			stack1.pop();
			stack2.pop();
		}
		else if (stack1.top() < stack2.top())
		{
			result.insert(stack1.top());
			stack1.pop();
		}
		else
		{
			result.insert(stack2.top());
			stack2.pop();
		}
	}

	while (!stack1.empty())
	{		
		result.insert(stack1.top());
		stack1.pop();
	}
	while (!stack2.empty())
	{
		
		result.insert(stack2.top());
		stack2.pop();
	}
	return result;
}
IntegerSet IntegerSet::getUnion(const IntegerSet& other) const
{
	return getUnion(this->root, other.root);
}


IntegerSet IntegerSet::getIntersection(Node* root1, Node* root2) const
{
	std::stack<int> stack1;
	postOrderTraversal(root1, stack1);
	std::stack<int> stack2;
	postOrderTraversal(root2, stack2);
	IntegerSet result;
	while (!stack1.empty() && !stack2.empty())
	{
		if (stack1.top() == stack2.top())
		{
			
			result.insert(stack1.top());
			stack1.pop();
			stack2.pop();
		}
		else if (stack1.top() < stack2.top())
		{
			stack1.pop();
		}
		else
		{
			stack2.pop();
		}
	}
	return result;
}

IntegerSet IntegerSet::getIntersection(const IntegerSet& other) const
{
	return getIntersection(this->root, other.root);
}

void IntegerSet::buildBalancedBST(Node*& root,std::vector<int>& values,int start,int end)
{
	if (start > end) {
		root = nullptr;
		return;
	}

	int mid = start + (end - start) / 2;
	root = new Node(values[mid]);

	buildBalancedBST(root->left, values, start, mid-1);
	buildBalancedBST(root->right, values, mid + 1, end);
}

void IntegerSet::deserialize(std::istream& in, Node*& root)
{
	while (!in.eof())
	{
		std::string token;
		in >> token;
		try {
			int number = std::stoi(token);
			if (number < 0)
			{
				continue;
			}
			else
			{
				std::vector<int> values;
				int value;

				for (size_t i = 0; i < number; i++)
				{
					in >> value;
					if (in.fail())
					{
						throw std::runtime_error("Non-integer in the sequence.");
					}
					values.push_back(value);
					if (i>0 && values[i] <= values[i - 1]) {
						throw std::runtime_error("Sequence is not strictly ascending.");
					}
				}
				if (values.size() != number)
				{
					throw std::runtime_error("Less numbers in the sequence than the specified number of elements.");
				}

				return buildBalancedBST(root, values, 0, values.size()-1);
			}
		}
		catch (const std::invalid_argument&) {
			continue;
		}
	}
	
}


void IntegerSet::deserialize(std::istream& in)
{
	deserialize(in, this->root);
}

void IntegerSet::serialize(const Node* root, std::ostream& out) const
{
	if (root)
	{
		serialize(root->left, out);
		out << " " << root->value;
		serialize(root->right, out);
	}
}
void IntegerSet::serialize(std::ostream& out) const
{
	out << size();
	serialize(root, out);
}
