#include <iostream>
#include "windows.h"

using namespace std;

class Node
{
public:
	int value;
	Node* left;
	Node* right;	
};

class BinaryTree
{
public:
	Node* root;
	BinaryTree()
	{
		root = NULL;
	}	
	void Insert(int value) //! inserting the first node to the tree
	{
		Insert(root, value);
	}
	void Insert(Node* &node, int value) //! inserting following node
	{
		//! if the node is null, create new root
		if (node == NULL)
		{
			node = new Node();
			node-> value = value;
			node-> left = NULL;
			node-> right = NULL;
			cout << "Node address : " << &node << endl;
			cout << "Node value : " << node->value << endl;
		}
		else if(value < node->value)
		{
			cout << value << " Left " << &(node->left) << endl;
			Insert(node->left, value);
		}
		else
		{
			cout << value << " Right " << &(node->right) << endl;
			Insert(node->right, value);	
		}
	}
	void DisplaySortedTree(Node* node, int id)
	{
		bool isDisplayed = false;
		//! 1. Always try to go left first
		//! 2. If there are no more left, then display the current node
		//! 3. Then try to go right first
		//! 4. If has not been displayed yet, then display the current node
		if(!node) return;
		DisplaySortedTree(node->left, id);
		id++;
		cout << node->value << endl;
		DisplaySortedTree(node->right, id);		
	}
	//!      search value, root that represent the binary tree
	Node* Search(int key, Node* root)
	{
		if(root != NULL)
		{
			//! search begin
			//! if block -> if the key equals with the node->value, return that node
			if(key == root->value)
			{
				return root; //! the node found
			}
			//! another if block -> if the key less than the node-> value, call again search function by passing in the node -> left
			if(key < root->value)
			{
				return Search(key, root->left);
			}
			//! else if the key more than node->value, call again search function by passing in the node-> right
			else 
			{
				return Search(key, root->right);
			}
		}
		else
		{
			return NULL;
		}
	}
	//! binary tree traversal
	void PreOrder(Node* root)
	{
		if(root == NULL)
		return;
		cout << root->value << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	
	void InOrder(Node* root)
	{
		if(root == NULL)
		return;
		InOrder(root->left);
		cout << root->value << " ";
		InOrder(root->right);		
	}	
	
	void PostOrder(Node* root)
	{
		if(root == NULL)
		return;	
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->value << " ";
		
	}	
	
};

int main()
{
	BinaryTree* bt1 = new BinaryTree();
	bt1->Insert(43);
	bt1->Insert(17);
	bt1->Insert(52);
	bt1->Insert(8);
	bt1->Insert(12);
	bt1->Insert(29);
	bt1->Insert(65);
	bt1->Insert(93);
	bt1->Insert(58);
	bt1->Insert(77);
	bt1->Insert(2);
	bt1->Insert(84);
	cout << endl << endl;
	
	bt1->DisplaySortedTree(bt1->root,0);
	cout << endl;
	
	Node* n = bt1->Search(93,bt1->root);
	if(n==NULL)
	{
		cout << "Not Found, Please Try Again." << endl;
	}
	else
	{
		cout << "Node Found! The Value Is: " << n->value << endl;
	}
	
	cout << endl << endl;
	
	cout << "Traversal by PreOrder: " << endl;
	bt1->PreOrder(bt1->root);
	cout << endl;
	
	cout << "Traversal by InOrder: " << endl;
	bt1->InOrder(bt1->root);
	cout << endl;
	
	cout << "Traversal by PostOrder: " << endl;
	bt1->PostOrder(bt1->root);	
	cout << endl;
	
	cout << endl << endl;
	system("PAUSE");
	return 0;
}
