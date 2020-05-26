#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

class Node
{
	public:
		int value;
		Node* next;
		Node* prev;
		
		Node()
		{
			prev = NULL;
			next = NULL;
		}
};

class DoublyLinkedList
{
	public:
		Node* head;
		
		DoublyLinkedList()
		{
			head = NULL;
		}
		void PushToBack(int value)
		{
			Node* current = head;
			Node* previous = NULL;
			bool isAdded = false;
			do
			{
				if (current == NULL) // empty list
				{
					current = new Node();
					current->value = value;
					isAdded = true;
					//! linking all the nodes
					if(previous != NULL)
					{
						current->prev = previous;
						current->prev->next = current;
					}
					if (head == NULL)
					{
						head = current;
					}
				}
				else
				{
					previous = current;
					current = current->next;
				}
			}while(!isAdded);
		}
		
		void Display()
		{
			int counter = 0;
			Node* current = head;
			while (current != NULL)
			{
				cout << current->value << endl;
				current = current->next;
				counter++;
			}
			cout << "Total numbers in the linked list: " << counter << endl;
		}
};

int main()
{
	DoublyLinkedList* numberList = new DoublyLinkedList();
	numberList->PushToBack(11);
	numberList->PushToBack(12);
	numberList->PushToBack(13);
	numberList->PushToBack(14);
	numberList->Display();
	
	cout << endl;
	system("PAUSE");
	return 0;
}
