#include <iostream>
#include <ctime>
#include <cmath>

using std::cout;
using std::ostream;

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
	
	friend bool operator<(const TreeNode &left, const TreeNode &right);
	friend ostream &operator<<(ostream &os, const TreeNode &Node);
};

bool operator< (const TreeNode &left, const TreeNode &right) {
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

	//recursive function, that puts Node in the tree
	void PutNode(TreeNode *NewNode, TreeNode *NodeInTree) {
		if ((NewNode->key) <= (NodeInTree->key))
			if (NodeInTree->left == nullptr) {
				NodeInTree->left = NewNode;
				MakeChild(NewNode, NodeInTree);
			}
			else
				PutNode(NewNode, NodeInTree->left);
		else
			if (NodeInTree->right == nullptr) {
				NodeInTree->right = NewNode;
				MakeChild(NewNode, NodeInTree);
			}
			else
				PutNode(NewNode, NodeInTree->right);
	}

	//function that makes children
	void MakeChild(TreeNode *NewNode, TreeNode *NodeInTree) {
		NewNode->parent = NodeInTree;
		NewNode->height = 1;
		UpdateHeight(NewNode->parent);
		BalanceTree(NewNode->parent);
		return;
	}
	
	//function that update heights
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

	//in case of a == 2, this function shows if Tree needs to be balanced in this node, and a child with bigger height
	//in case of a == 1, this function shows just the child with bigger height ( the Tree probably don't need to be balanced in this node)
	int CompareChildren(TreeNode *Node, int a) {			
		if (Node->left == nullptr)							
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

	//function that rotates tree: swap(left_child, right_child)
	void Rotate(TreeNode *Node) {
		if (Node->left == nullptr and Node->right == nullptr)
			return;
		else if (Node->left != nullptr and Node->right == nullptr) {
			Node->right = Node->left;
			Node->left = nullptr;
			Rotate(Node->right);
		}
		else if (Node->left == nullptr and Node->right != nullptr) {
			Node->left = Node->right;
			Node->right = nullptr;
			Rotate(Node->left);
		}
		else {
			TreeNode *temp = Node->left;
			Node->left = Node->right;
			Node->right = temp;
			Rotate(Node->right);
			Rotate(Node->left);
		}
	}
	
	//function that can balance tree if only left child and left child of the left child have bigger heights
	void BalanceLeft(TreeNode *Node) {
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

	//function that prereform tree to unable function above
	void PreReform(TreeNode *Node) {
		Node->left->right->parent = Node;
		Node->left->parent = Node->left->right;
		if (Node->left->right->left != nullptr) {
			Node->left->right->left->parent = Node->left;
			Node->left->right = Node->left->right->left;
		}
		else
			Node->left->right = nullptr;
		Node->left->parent->left = Node->left;
		Node->left = Node->left->parent;
		Node->left->height += 1;
		Node->left->left->height -= 1;
		return;
	}

	//function that balance the tree
	void BalanceTree(TreeNode *Node) {
		if (CompareChildren(Node, 2) == 1) {
			if (CompareChildren(Node->left, 1) == 1)
				BalanceLeft(Node);
			else {
				PreReform(Node);
				BalanceLeft(Node);
			}
		}
		else if (CompareChildren(Node, 2) == 2) {
			if (CompareChildren(Node->right, 1) == 2) {
				Rotate(Node);
				BalanceLeft(Node);
				Rotate(Node->parent);
			}
			else {
				Rotate(Node);
				PreReform(Node);
				BalanceLeft(Node);
				Rotate(Node->parent);
			}
		}
		if (Node->parent != nullptr)
			BalanceTree(Node->parent);
	}

	//function that clear all nodes and connections
	bool Clear(TreeNode *Node) {
		//if it is Node without children - delete it
		if (Node->left == nullptr && Node->right == nullptr) {
			Node->parent = nullptr;
			Node->information = NAN;
			Node->key = NAN;
			Node->height = NAN;
			return 1;
		}
		//if not - go to it's children with recursion and delete them
		else {
			if(Node->left != nullptr)
				if (Clear(Node->left)) {
					Node->left = nullptr;
					Node->information = NAN;
					Node->key = NAN;
					Node->height = NAN;
					return 1;
				}
			if (Node->right != nullptr)
				if (Clear(Node->right)) {
					Node->right = nullptr;
					Node->information = NAN;
					Node->key = NAN;
					Node->height = NAN;
					return 1;
				}
		}

	}

public:

	//you can add nodes to the tree with this function
	void AddNode(TreeNode *NewNode) {
		if (root->key != root->key)
			root = NewNode;
		else
			PutNode(NewNode, root);
	} 

	void ClearTree(void) {
		if( Clear(root) )
		cout << "tree cleared";
		return;
	}

	friend void PrintTree(TreeNode *Node, int depth, int state);
	
	friend ostream &operator<<(ostream &os, const AVLTree &Tree);
};

void PrintTree(TreeNode *Node, int depth = 0, int state = 0) {			// I can't show special UNICODE symbols, like this "┌───" or this "└───"
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
	const int a = 10;
	TreeNode m[a];
	AVLTree Tree;
	for (int i = 0; i < a; i++) {
		m[i].key = rand() % 100;
		m[i].information = m[i].key;
		Tree.AddNode(&(m[i]));
		cout << Tree << "\n----------------------\n";
	}

	Tree.ClearTree();
	
	cout << "\n";
	system("pause");
	return 0;
}