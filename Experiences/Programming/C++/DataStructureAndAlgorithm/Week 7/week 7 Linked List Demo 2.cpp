#include <iostream>
#include "windows.h"

using namespace std;

struct Node
{
	int data;
	Node* next;
};

void InitializationNode(Node* head, int n)
{
	head->data = n;
	head->next = NULL;
}
//! appending -> add new node at the end of the list
void AddNode(Node* head, int n)
{
	Node* newNode = new Node;
	newNode->data = n;
	newNode->next = NULL;
	
	Node* current = head;
	while (current)
	{
		if(current->next == NULL)
		{
			current->next = newNode;
			return;
		}
		current = current->next;
	}
}

void InsertFront(Node** head, int n)
{
	Node* newNode = new Node;
	newNode->data = n;
	newNode->next = *head;
	*head = newNode;
}

Node* SearchNode(Node* head, int n)
{
	Node* cur = head;
	while(cur)
	{
		if(cur->data == n)
		{
			return cur;
		}
		cur = cur->next;
	}
	cout << "No Node " << n << " in list." << endl;
}

bool DeleteNode(Node** head, Node* ptrDel)
{
	Node* cur = *head;
	if (ptrDel == *head)
	{
		*head = cur->next;
		delete ptrDel;
		return true;
	}
	while(cur)
	{
		if(cur->next == ptrDel)
		{
			cur->next = ptrDel->next;
			delete ptrDel;
			return true;
		}
		cur = cur->next;
	}
	return false;
}

Node* Reverse(Node** head)
{
	Node* parent = *head;
	Node* me = parent->next;
	Node* child = me->next;
	
	parent->next = NULL;
	while(child)
	{
		me->next = parent;
		parent = me;
		me = child;
		child = child->next;
	}
	me->next = parent;
	*head = me;
	return *head;
}

void DeleteLinkList(Node** head)
{
	while (head)
	{
		Node* cur = *head;	
		*head = cur->next;		
		if (cur->next)
		{
			delete cur;
		}
		else
		{
			delete cur;
			delete *head;
			return;
		}	
	}
	
}
//! creating a copy of a linked list
void CopyLinkList(Node* head, Node** pNew)
{
	Node* oList = head;
	Node* nList = NULL;
	
	while (oList)
	{
		Node* newNode = new Node;	
		newNode->data = oList->data;
		newNode->next = NULL;
		
		if (!nList)
		{
			nList = newNode;
			*pNew = nList;
		}
		else
		{
			nList->next = newNode;
			nList = nList->next;
		}
		oList = oList->next;
	}
	
}
//!Compare two linked list
//! return value : same (1), different(0)
int CompareLinkList(Node* head1, Node* head2)
{
	if(head1 || head2)
	{
		if(head1->data == head2->data)
		return 1;
		else if (!head1 && head2)
		return 0;
		else if (!head2 && head1)
		return 0;
		else
		return 0;			
	}
	
	CompareLinkList(head1->next, head2->next);
}

void Display(Node* head)
{
	Node* cur = head;
	while(cur)
	{
		cout << cur->data << " ";
		cur = cur->next; 
	}
	cout << endl << endl;
}

int main()
{
	Node* newHead;
	Node* head = new Node;
	InitializationNode(head, 10);
	Display(head);

	AddNode(head, 20);
	Display(head);
	AddNode(head, 30);
	Display(head);
	AddNode(head, 35);
	Display(head);
	AddNode(head, 40);
	Display(head);		
	
	InsertFront(&head, 5);
	Display(head);
	
	//! remove 5
	//! perform searching
	int numDel = 5;
	Node* ptrDel = SearchNode(head,numDel);
	if(DeleteNode(&head, ptrDel))
	{
		cout << "Node " << numDel<< " deleted!" << endl;
	}
	Display(head);
	
	Reverse(&head);
	Display(head);
	
//	DeleteLinkList(&head);		
//	Display(head);		

	CopyLinkList(head, &newHead);
	Display(head);
	Display(newHead);
	
	if(CompareLinkList(head, newHead) == 1)
	{
		cout << "Both lists have the same contains!" << endl;
	}
	else
	{
		cout << "Both lists are not the same!!" << endl;
	}
	
	
	
	cout << endl;
	system("PAUSE");
	return 0;
}
