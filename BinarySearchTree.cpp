#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
using namespace std;

template<typename Type>
struct Node {
	Type Data;
	Node<Type>* left = nullptr;
	Node<Type>* right = nullptr;
};

template<typename Type>
class BST {
protected:
	Node<Type>* root;

private:
	Node<Type>* GetRoot()const { return root; }

	Node<Type>* GetNode(Node<Type>* root, Type Item) {
		if (!root) return nullptr;
		if (Item == root->Data) return root;
		if (Item < root->Data) {
			if (root->left) return GetNode(root->left, Item);
		}
		else {
			if (root->right) return GetNode(root->right, Item);
		}
	}
	void DestroyTree(Node<Type>* root) {
		if (!root) return;
		if (root->left != nullptr) {
			DestroyTree(root->left);
		}
		if (root->right != nullptr) {
			DestroyTree(root->right);
		}
		delete root;
	}

	//SEARCH Data
	bool searchHelper(Node<Type>* root, const Type& Item) {
		if (!root) return false;
		if (Item == root->Data) return true;
		if (Item < root->Data) {
			if (!root->left) return false;
			else return searchHelper(root->left, Item);
		}
		else {
			if (!root->right) return false;
			else return searchHelper(root->right, Item);
		}

	}
	//ADD Data
	void insertHelper(Node<Type>* root, Type Item) {
		if (!root) root = CreateNode(root, Item);
		else {
			if (Item < root->Data) {
				if (!root->left) root->left = CreateNode(root, Item);
				else return insertHelper(root->left, Item);
			}
			else if (Item > root->Data) {
				if (!root->right) root->right = CreateNode(root, Item);
				else return insertHelper(root->right, Item);
			}
			else return;
		}
	}
	//Traversals
	void inorderHelper(Node<Type>* root) {
		if (!root) return;
		inorderHelper(root->left);
		cout << root->Data << " ";
		inorderHelper(root->right);
	}
	void postorderHelper(Node<Type>* root) {
		if (!root) return;
		if (root->left) inorderHelper(root->left);
		if (root->right) inorderHelper(root->right);
		cout << root->Data << " ";
	}
	void preorderHelper(Node<Type>* root) {
		if (!root) return;
		cout << root->Data << " ";
		if (root->left) inorderHelper(root->left);
		if (root->right) inorderHelper(root->right);
	}

	Node<Type>* getGreatest(Node<Type>* root) {
		if (!root) return nullptr;
		if (!root->right) return root;
		else return getGreatest(root->right);
	}

	Node<Type>* getSmallest(Node<Type>* root) {
		if (!root) return nullptr;
		if (!root->left) return root;
		else return getSmallest(root->left);
	}

	void removeHelper(Node<Type>* root, Type Item) {
		if (!root) return;
		if (Item < root->Data) removeHelper(root->left, Item);
		if (Item > root->Data) removeHelper(root->right, Item);
		else if (Item == root->Data) {
			if (!root->left and !root->right) {
				Node<Type>* oldRoot = root;
				root = nullptr;
				delete oldRoot;
			}
			else if (!root->right || !root->left) {
				Node<Type>* oldRoot = root;
				root = (root->left ? root->left : root->right);
				delete oldRoot;
			}
			else {
				Node<Type>* smallestRightNode = getSmallest(root->right);
				root->Data = smallestRightNode->Data;
				removeHelper(root->right, smallestRightNode->Data);
			}
		}
	}

	unsigned int TreeHeight(Node<Type>* root) { //max depth
		if (!root) return;
		return max(TreeHeight(root->left), TreeHeight(root->right)) + 1;
	}

	unsigned int MinDepth(Node<Type>* root) {
		if (!root) return 0;
		if (!root->left && !root->right) return 1;
		if (!root->right) return MinDepth(root->left) + 1;
		if (!root->left) return MinDepth(root->right) + 1;
		return 1 + min(MinDepth(root->left), MinDepth(root->right));
	}

	unsigned int NodeCount(Node<Type>* root) {
		if (!root) return 0;
		return (NodeCount(root->left) + 1 + NodeCount(root->right));
	}

public:
	Node<Type>* CreateNode(Node<Type>* root, Type newItem) {
		Node<Type>* newNode = new Node<Type>;
		newNode->Data = newItem;
		newNode->left = nullptr; newNode->right = nullptr;
		root = newNode;
		return root;
	}

	BST() {
		root = nullptr;
	}
	~BST() {
		if (root) DestroyTree(root);
	}

	bool search(const Type& searchItem) {
		searchHelper(root, searchItem);
	}

	void insert(Type newItem) {
		if (!root) root = CreateNode(root, newItem);
		insertHelper(root, newItem);
	}
	void remove(Type removeItem) {
		removeHelper(root, removeItem);
	}
	void inorder() {
		inorderHelper(root);
	}
	void preorder() {
		preorderHelper(root);
	}

	void postorder() {
		postorderHelper(root);
	}
};
#endif