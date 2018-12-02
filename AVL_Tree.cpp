#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

class TreeNode {
public:
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;
	double key;
	double information;
	int height;
	
	TreeNode() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		key = NAN;
		information = NAN;
		height = NAN;
	}
	
	friend bool operator<(TreeNode &left, TreeNode &right);
	friend ostream &operator<<(ostream &os, const TreeNode &Node);
};

bool operator< (TreeNode &left, TreeNode &right) {
	return (left.key < right.key);
}

ostream &operator<<(ostream &os, const TreeNode &Node) {
	os << Node.key << "|" << Node.information << "|" << Node.height << "\n";
	return os;
}

class AVLTree {
private:

	int hight;
	TreeNode *root = new TreeNode;

public:

	void AddNode(TreeNode *NewNode) {
		if (root->key != root->key)
			root = NewNode;
		else
			PutNode(NewNode, root);
	} 
	
	void PutNode(TreeNode *NewNode, TreeNode *NodeInTree) {
		if ((NewNode->key) <= (NodeInTree->key))
			if (NodeInTree->left == nullptr) {
				NodeInTree->left = NewNode;
				NewNode->parent = NodeInTree;
				UpdateHeight(NewNode->parent);
				BalanceTree(NewNode->parent);
			}
			else
				PutNode(NewNode, NodeInTree->left);
		else
			if (NodeInTree->right == nullptr) {
				NodeInTree->right = NewNode;
				NewNode->parent = NodeInTree;
				UpdateHeight(NewNode->parent);
				BalanceTree(NewNode->parent);
			}
			else
				PutNode(NewNode, NodeInTree->right);
	}

	void UpdateHeight(TreeNode *Node) {
		if (Node->left == nullptr)
			if (Node->right == nullptr)
				Node->height = 0;
			else
				Node->height = Node->right->height + 1;
		else
			if (Node->right == nullptr)
				Node->height = Node->left->height + 1;
			else
				if (Node->right->height >= Node->left->height)
					Node->height = Node->right->height + 1;
				else
					Node->height = Node->left->height + 1;
		if (Node->parent != nullptr)
			UpdateHeight(Node->parent);
	}
	int CompareChildren(TreeNode *Node, int a) {			//in case of a == 2, this function shows if Tree needs to be balanced in this node, and a child with bigger node
		if (Node->left == nullptr)							//in case of a == 1, this function shows just the child with bigger node ( the Tree probably don't need to be balanced in this node
			if (Node->right == nullptr)
				return 0;
			else
				if (Node->right->height > a - 1)
					return 2;
				else
					return 0;
		else
			if (Node->right == nullptr)
				if (Node->left->height > a - 1)
					return 1;
				else
					return 0;
			else
				if (Node->right->height >= Node->left->height + a)
					return 2;
				else if (Node->left->height >= Node->right->height + a)
					return 1;
				else
					return 0;
	}
	void BalanceTree(TreeNode *Node) {
			if (CompareChildren(Node, 2) == 1) {
				if (CompareChildren(Node->left, 1) == 1) {
					if (Node->parent == nullptr) {
						Node->left->parent = nullptr;
						root = Node->left;
					}
					else {
						if (Node->parent->left->information == Node->information)
							Node->parent->left = Node->left;
						else
							Node->parent->right = Node->left;
						Node->left->parent = Node->parent;
					}
					Node->parent = Node->left;
					if (Node->parent->right != nullptr) {
						Node->parent->right->parent = Node;
						Node->left = Node->left->right;
					}
					else
						Node->left = nullptr;
					Node->parent->right = Node;
					//change heights
					Node->height -= 2;
					UpdateHeight(Node->parent);
				}
				else {
					if (Node->parent == nullptr) {
						Node->left->right->parent = nullptr;
						root = Node->left->right;
					}
					else {
						if (Node->parent->left->information == Node->information)
							Node->parent->left = Node->left->right;
						else
							Node->parent->right = Node->left->right;
						Node->left->right->parent = Node->parent;
					}
					Node->parent = Node->left->right;
					Node->left->parent = Node->parent;
					if (Node->left->right->left != nullptr) {
						Node->left->right->left->parent = Node->left;
						Node->left->right = Node->left->right->left;
					}
					else
						Node->left->right = nullptr;
					Node->parent->left = Node->left;
					if (Node->parent->right != nullptr) {
						Node->parent->right->parent = Node;
						Node->left = Node->parent->right;
					}
					else
						Node->left = nullptr;
					Node->parent->right = Node;
					//change heights
					Node->height -= 2;
					Node->parent->height += 1;
					Node->parent->left->height -= 1;
					UpdateHeight(Node->parent);
				}
			}
			else if (CompareChildren(Node, 2) == 2) {
				if (CompareChildren(Node->right, 1) == 2) {
					if (Node->parent == nullptr) {
						Node->right->parent = nullptr;
						root = Node->right;
					}
					else {
						if (Node->parent->right->information == Node->information)
							Node->parent->right = Node->right;
						else
							Node->parent->left = Node->right;
						Node->right->parent = Node->parent;
					}
					Node->parent = Node->right;
					if (Node->parent->left != nullptr) {
						Node->parent->left->parent = Node;
						Node->right = Node->right->left;
					}
					else
						Node->right = nullptr;
					Node->parent->left = Node;
					//change heights
					Node->height -= 2;
					UpdateHeight(Node->parent);
				}
				else {
					if (Node->parent == nullptr) {
						Node->right->left->parent = nullptr;
						root = Node->right->left;
					}
					else {
						if (Node->parent->right->information == Node->information)
							Node->parent->right = Node->right->left;
						else
							Node->parent->left = Node->right->left;
						Node->right->left->parent = Node->parent;
					}
					Node->parent = Node->right->left;
					Node->right->parent = Node->parent;
					if (Node->right->left->right != nullptr) {
						Node->right->left->right->parent = Node->right;
						Node->right->left = Node->right->left->right;
					}
					else
						Node->right->left = nullptr;
					Node->parent->right = Node->right;
					if (Node->parent->left != nullptr) {
						Node->parent->left->parent = Node;
						Node->right = Node->parent->left;
					}
					else
						Node->right = nullptr;
					Node->parent->left = Node;
					//change heights
					Node->height -= 2;
					Node->parent->height += 1;
					Node->parent->right->height -= 1;
					UpdateHeight(Node->parent);
				}
			}
		if (Node->parent != nullptr)
			BalanceTree(Node->parent);
	}
	
	

	friend void PrintTree(TreeNode *Node, int depth, int state);
	
	friend ostream &operator<<(ostream &os, const AVLTree &Tree);
};

void PrintTree(TreeNode *Node, int depth = 0, int state = 0) {			// I can't show special UNICODE symbols(((
	if (Node->left != nullptr)
		PrintTree(Node->left, depth + 1, 1);
	for (int i = 0; i < depth; i++)
		cout << "     ";
	if (state == 1) {
		// left
		cout << "/---";
	}
	else if (state == 2) {
		// right
		cout << "\\---";
	}
	cout << "[" << Node->information << "]-(" << Node->key <<
		", " << Node->height << ")" << "\n";

	if (Node->right != nullptr)
		PrintTree(Node->right, depth + 1, 2);

}

ostream &operator<<(ostream &os, const AVLTree &Tree) {
	if ((Tree.root)->key != (Tree.root)->key)
		os << "empty";
	else
		PrintTree(Tree.root);
	return os;
}

int main(void) {
	srand(time(0));
	const int a = 20;
	TreeNode m[a];
	AVLTree Tree;
	for (int i = 0; i < a; i++) {
		m[i].key = rand() % 100;
		m[i].information = m[i].key;
		Tree.AddNode(&(m[i]));
		cout << Tree << "\n----------------------\n";
	}
	
	cout << "\n";
	system("pause");
	return 0;
}