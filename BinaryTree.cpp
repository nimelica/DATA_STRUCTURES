#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int newData) {
		data = newData;
		left = nullptr;
		right = nullptr;
	}
};

void destroyTree(TreeNode* root) {//postorder traversal deletion
	if (!root) return;
	if (root->left)  destroyTree(root->left);
	if (root->right) destroyTree(root->right);
	cout << "Destructor State: root value-> " << root->data << " deleting...\n";
	delete root;
	root = nullptr;
}

TreeNode* createTree(int newData) {
	TreeNode* newTree = new TreeNode(newData);
	newTree->right = nullptr;
	newTree->left = nullptr;
	return newTree;
}

void TEST_printInOrder(TreeNode* root) {
	if (!root) return;
	if (root->left) {
		cout << "Adding inorder recursive stack left val--> " << root->left->data << endl << endl;
		TEST_printInOrder(root->left);
	}
	cout << "current root printing------->[" << root->data << "] " << endl;
	if (root->right) {
		cout << "Adding inorder recursive stack right val --> " << root->right->data << endl << endl;
		TEST_printInOrder(root->right);
	}
}

void printInOrder(TreeNode* root) {
	if (!root) return;
	if (root->left) printInOrder(root->left);
	cout << root->data << " ";
	if (root->right) printInOrder(root->right);
}

TreeNode* TEST_searchNode(TreeNode* root, int searchKey) { //level order traversal
	if (!root) return nullptr;
	queue<TreeNode*>leaves;
	cout << "queue.push(" << root->data << ");->" << endl;
	leaves.push(root);
	TreeNode* out = nullptr;
	while (!leaves.empty()) {
		cout << "TreeNode pointer is getting the front data->[" << leaves.front()->data << "] " << endl << endl;
		TreeNode* temp = leaves.front();
		leaves.pop();
		if (temp->data == searchKey)
		{
			cout << " DATA FOUND!\n";
			out = temp;
		}
		if (temp->left) {
			cout << "Left child exists!->pushing into the queue!\n";
			leaves.push(temp->left);
		}
		else {
			cout << "node does NOT have a LEFT child->skip it!\n\n";
		}
		if (temp->right) {
			cout << "Right child exists!->pushing into the queue after left child!\n\n";
			leaves.push(temp->right);
		}
		else {
			cout << "node does NOT have a RIGHT child->skip it!\n\n";
		}
	}
	return out;
}

TreeNode* search(TreeNode* root, int searchVal) {
	if (!root) return nullptr;
	queue<TreeNode*>leaves;
	leaves.push(root);
	TreeNode* out = nullptr;

	while (!leaves.empty()) {
		TreeNode* temp = leaves.front(); leaves.pop();
		if (temp->data == searchVal) out = temp;
		if (temp->left) leaves.push(temp->left);
		if (temp->right)leaves.push(temp->right);
	}
	return out;
}

void insert_levelOrder(TreeNode* root, int val) { //always insert from left
	if(!root) createTree(val);
	TreeNode* newNode = createTree(val);
	queue<TreeNode*>offer;
	offer.push(root);

	while (!offer.empty()) {
		TreeNode* curr = offer.front(); offer.pop();
		if (!curr->left) {
			curr->left = newNode;
			return;
		}
		else if (!curr->right) { //if there is no place for left side, to prevent height, we need to add the node at right side
			curr->right = newNode;
			return;
		}
		else { //if there is not empty place, go to last level
			offer.push(curr->left);
			offer.push(curr->right);
		}
	}
}

void deleteDeepestRight(TreeNode* root, TreeNode* rightmost) {
	if (!root) return;
	if (root == rightmost) {
		delete rightmost;
		root = nullptr;
		return;
	}
	if (root->left == rightmost) {
		delete rightmost;
		root->left = nullptr;
		return;
	}
	if (root->right == rightmost) {
		delete rightmost;
		root->right = nullptr;
		return;
	}
	deleteDeepestRight(root->left, rightmost);
	deleteDeepestRight(root->right, rightmost);
}

void deleteNode(TreeNode* root, int key) {
	if (!root) return; //case 0) tree is not exists
	if (root->data == key && !root->left && !root->right) {//case 1) only one node and it has data
		delete root;
		root = nullptr;
	}
	TreeNode* rubbish = search(root, key); //case 2)find the node of the given value
	queue<TreeNode*>offer;
	offer.push(root);
	TreeNode* temp = nullptr;

	while (!offer.empty()) {
		temp = offer.front(); offer.pop();

		if (temp->left) offer.push(temp->left);
		if (temp->right) offer.push(temp->right);
	}
	if (rubbish != nullptr) { //rubbish found 
		//make the deepest data of the node that we need to delete
		int deepestData = temp->data;//temp is the rightmost node
		rubbish->data = deepestData;
		//delete rightost node
		deleteDeepestRight(root, temp);
		//delete temp
		temp = nullptr;
	}
}

vector<vector<int>>levelTraversal(TreeNode* root) {
	vector<vector<int>>result_levels;
	vector<int>level;
	queue<TreeNode*>Q;
	Q.push(root);

	while (!Q.empty()) {
		int size = Q.size();
		cout << "Size is : " << size << endl;
		for (int i = 0; i < size; i++) {
			TreeNode* curr = Q.front(); Q.pop();
			level.push_back(curr->data);
			if (curr->left) Q.push(curr->left);
			if (curr->right)Q.push(curr->right);
		}
		result_levels.push_back(level);
		level.clear();
	}
	return result_levels;
}

unsigned int maxDepth(TreeNode* root) {
	if (!root) return 0;
	else {
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
}

int countNodes(TreeNode* root) {
	if (!root) return 0;
	int rightSub = countNodes(root->right);
	cout << "Right sub-tree size is: " << rightSub << endl;
	int leftSub = countNodes(root->left);
	cout << "Left sub-tree size is: " << leftSub << endl;
	return (rightSub + leftSub) + 1;
}

int numberOfNodes(TreeNode* root) {
	if (!root) return 0;
	return (numberOfNodes(root->left) + 1 + numberOfNodes(root->right));
}

bool isComplete(TreeNode* root, int index, unsigned int size) {
	if (!root) return true; //->an empty tree is complete
	if (index >= size) return false;
	cout << "Index is: " << index << endl;
	return (isComplete(root->left, 2 * index + 1, size) && isComplete(root->right, 2 * index + 2, size));
}

int leftSubTreeDepth(TreeNode* root) {
	if (!root) return 0;
	int depth = 0;
	while (root) {
		depth++;
		root = root->left;
	}
	return depth;
}

bool isPerfectRef(TreeNode* root, int depth, int level = 0) {
	if (!root) return true;
	// If leaf node, then its depth must be same as
	// depth of all other leaves. ->height
	if (root->left == nullptr && root->right == nullptr) {
		return (depth == level + 1);
	}
	if (root->left == nullptr || root->right == nullptr) {
		return false;
	}
	return isPerfectRef(root->left, depth, level + 1) &&
		isPerfectRef(root->right, depth, level + 1);
}

bool isPerfect(TreeNode* root) {
	int depth = leftSubTreeDepth(root);
	isPerfectRef(root, depth);
}

TreeNode* removeLeafNode_postorder(TreeNode* root, int target) { //if you wanna do something with leaves->use postorder
	if (!root) return nullptr;
	root->left = removeLeafNode_postorder(root->left, target);
	root->right = removeLeafNode_postorder(root->right, target);
	if (root->left == nullptr && root->right == nullptr && root->data == target)
		return nullptr;
	return root;
}

void preorder_dfs(TreeNode* root, int& counter, int maxVal) { //if you wanna do something with parents ->do preorder
	if (!root) return;
	if (root->data >= maxVal) {
		counter++;
		maxVal = root->data; //update max value for each new root
	}
	if (root->left) preorder_dfs(root->left, counter, maxVal);
	if (root->right) preorder_dfs(root->right, counter, maxVal);
}

// a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.
int goodNodes(TreeNode* root) {
	//to check a parent, we need to use preorder
	//we should send "counter" as reference to manipulate it

	if (!root) return 0;
	int counter = 0;
	preorder_dfs(root, counter, INT_MIN);
	return counter;
}

bool isMirror(TreeNode* leftRoot, TreeNode* rightRoot) {
	if (!leftRoot && !rightRoot) return true;
	if (!leftRoot || !rightRoot) return false;
	if (leftRoot->data != rightRoot->data) return false;
	return isMirror(leftRoot->left, rightRoot->right) && isMirror(leftRoot->right, rightRoot->left);
}

bool isSymmetric(TreeNode* root) {
	return isMirror(root->left, root->right);
}


int main() {
	TreeNode* root = createTree(7);
	root->left = createTree(6);
	root->left->left = createTree(4);
	root->right = createTree(8);
	root->right->right = createTree(9);

	cout << "Creating a tree in-order values: " << endl;
	printInOrder(root);
	cout << "Inorder traversal process->\n";
	cout << "________________________________________________________________________\n";
	TEST_printInOrder(root);
	cout << "________________________________________________________________________\n";
	cout << endl << endl;
	cout << "SEARCH RIGHTMOST VALUE->9\n\n";
	//root = search(root, 9);
	cout << root->data << " ";
	cout << "________________________________________________________________________\n";
	cout << endl << endl;
	cout << "Max depth is: ";
	int max = maxDepth(root);
	cout << max << endl << endl;
	cout << "Number of nodes is: ";
	int num = numberOfNodes(root);
	cout << num << endl << endl;
	cout << "Is this tree is a complete tree? : ->" << endl;
	bool answer = isComplete(root, 0, num);
	cout << answer << " " << endl << endl;
	cout << "Depth of a leaf is: " << endl << endl << endl;
	int depth = leftSubTreeDepth(root);
	cout << depth << endl << endl;
	cout << "Destroy tree memory\n";
	destroyTree(root);

	return 0;
}

/*
  TREE VISUALIZATION
		 7
		/ \
	   6   8
	  /     \
	 4       9
*/