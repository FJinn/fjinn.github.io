#include <iostream>
#include "windows.h"

using namespace std;

struct Node
{
	int value;
	Node* next;
};

int main()
{
	Node* root = new Node;
	root->value = 51;
	root->next = NULL;
//	cout << "Root value is: " << root->value << endl;

/*		root								secNode
		| 52				/--->|	 		52
		| 					/--->|			
		| next-> secNode	/--->|			next-> NULL
			
*/	
/*	Node* secNode = new Node;
	secNode->value = 52;
	secNode->next = NULL;
	
	root->next = secNode;
	
	cout << "Second Node value is: " << root->next->value << endl;
*/	//! pointer
	Node* conductor;
	conductor = root;
	
	while(conductor != NULL)
	{
		cout << "Value: " << conductor->value << endl;
		conductor = conductor->next;
	}	

	while(root != NULL)
	{
		cout << "Value: " << root->value << endl;
		root = root->next;
	}	
	
/*	conductor->next = new Node;
	conductor->value = 53;
	conductor->next = NULL;
	conductor = conductor->next;
	
*/
	
	cout << endl;
	system("PAUSE");
	return 0;
}
