#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <stack>

class IntegerSet {
private:
	class Node {
	public:
		int value;
		Node* left;
		Node* right;
		Node(int value, Node* left = nullptr, Node* right = nullptr)
			: value(value)
			, left(left)
			, right(right)
		{}
		Node() = default;
	};
	Node* root;

	void clear(Node* root)
	{
		if (root)
		{
			clear(root->left);
			clear(root->right);
			delete root;
		}
		
	}

	Node* copy(Node* root)
	{
		if (root)
		{
			return new Node(root->value, copy(root->left), copy(root->right));
		}
		
			return nullptr;
	}

	void insert(Node*& root, const int value)
	{
		if (!root) {
			root = new Node(value);
		}
		else {
			insert(value < root->value ? root->left : root->right, value);
		}
	}

	

public:
  IntegerSet();
  IntegerSet(const IntegerSet&);
  IntegerSet& operator=(const IntegerSet&);
  ~IntegerSet();

public:

  void insert(const int value) { insert(root, value);}

  size_t size(Node* root) const;

  // Връща броя на елементите в множеството
  size_t size() const;

  bool equals(Node* root1,Node* root2) const;

  /// Проверява дали две множества се състоят от едни и същи елементи
  bool equals(const IntegerSet&) const;

  bool contains(int, Node*) const;

  /// Проверява дали елемент се съдържа в множеството
  bool contains(int) const;


  bool subsetOf(Node* root,Node* other) const;

  /// Проверява дали текущия обект е подмножество на друг
  bool subsetOf(const IntegerSet&) const;

  IntegerSet getUnion(Node* root1, Node* root2) const;

  /// Връща обединението на две множества
  IntegerSet getUnion(const IntegerSet&) const;

  void postOrderTraversal(Node*& node, std::stack<int>& resultQueue) const;

  IntegerSet getIntersection(Node* root1, Node* root2) const;

  /// Връща сечението на две множества
  IntegerSet getIntersection(const IntegerSet&) const;

  void buildBalancedBST(Node*& root,std::vector<int>& values, int start, int end);

  void deserialize(std::istream& in, Node*& root);

  /// Десериализира съдържанието на едно множество.
  /// Новата информация напълно заменя старата.
  void deserialize(std::istream&);


  void serialize(const Node* root, std::ostream& out) const;

  /// Сериализира съдържанието на едно множество
  void serialize(std::ostream&) const;
   
};

inline std::istream& operator>>(std::istream& in, IntegerSet& set)
{
  set.deserialize(in);
  return in;
}

inline std::ostream& operator<<(std::ostream& out, const IntegerSet& set)
{
  set.serialize(out);
  return out;
}
