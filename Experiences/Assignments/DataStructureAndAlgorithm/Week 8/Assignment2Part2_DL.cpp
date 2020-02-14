#include <iostream>
#include "windows.h"
#include <ctime>
#include <limits>

using namespace std;

//! class Node
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
//! class DoublyLinkedList
class DoublyLinkedList
{
	private:
		bool IsValid(int index)
		{
			return index >= 01;
		}
	public:
		Node* head;
		
		DoublyLinkedList()
		{
			head = NULL;
		}
		
		bool isEmpty()
		{
			return head == NULL;
		}
		
		Node* getNext()
		{
			if(isEmpty())
			{
				return head;
			}
			Node* current = head;
			while (current->next != NULL)
			{
				current = current->next;
			}
			return current;
		}
		
		void PushToBack(int value)
		{
			if(isEmpty())
			{
				head = new Node;
				head->value = value;
				head->next = NULL;
				head->prev = NULL;
			}
			else
			{
				Node* newNode = getNext();
				newNode->next = new Node;
				newNode->next->value = value;
				newNode->next->next = NULL;
				newNode->next->prev = newNode;				
			}
		}
		
		void PopFromBack()
		{
			Node* last = getNext();
			last->prev->next = NULL;
			delete last;
			
		}
		
		Node* GetNode(int index)
		{
			if (!IsValid(index))
			return NULL;
			
			if (isEmpty())
			return head;
			
			Node* current = head;
			
			for (int i=0; i<index-1; i++)
			{
				if (current != NULL)
				{
					current = current->next;
				}
				else
				{
					return NULL;
				}
			}
			return current;
		}
		
		void Insert(int index, int value) //! insert in between
		{
			//! index is the location that you plan to add in the new node
			//! value will assign to the newNode->value
			if (GetNode(index))
			{
				Node* newIns = new Node;
				newIns->value = value;
				if (GetNode(index)->prev)
				{
					newIns->next = GetNode(index);
					newIns->prev = GetNode(index)->prev;
					GetNode(index)->prev = newIns;
					GetNode(index-1)->next = newIns;				
				}
				else if (GetNode(index) == head)
				{
					head->prev = newIns;				
					newIns->next = head;
					head = head->prev;
					newIns->prev = NULL;
				}	
			}
			else
			{
				cout << "There is no this index number in the list!!" << endl;
			}
			
		}
		
		void Remove(int index) //! remove node (in between)  
		{
			//! index -> the location that you plan to remove from the list
			Node* R = GetNode(index);
			if (R)
			{
				if (R->prev && R->next)
				{
					R->prev->next = R->next;
					R->next->prev = R->prev;
					delete R;
						
				}
				else if (R == head)
				{
					head = head->next;
					R->next->prev = NULL;
					delete R;
				}
				else if (!R->next)
				{
					R->prev->next = NULL;
					delete R;
				}
			}
			else
			{
				cout << "There is no this index number in the list!!" << endl;
			}
			
		}
		
		void SwapNode(int index1, int index2)
		{
			//! search the two indexes value, and assign the swapA pointer and the swapB pointer
			if(index2 < index1) // so index1 is always smaller, thus swapA is always smaller and locates before swapB in the linked list
			{
				int tempI = index2;
				index2 = index1;
				index1 = tempI;
			}
			if (!GetNode(index1) || !GetNode(index2))
			{
				cout << "Please input correct index number!!" << endl;
				return;
			}
			
			Node* swapA = GetNode(index1);
			Node* swapB = GetNode(index2);
			Node* temp;
			
			//! not efficient
			if (swapA->prev != NULL)
			{
				swapA->prev->next = swapB;			
			}
			if (swapB->prev != swapA && swapA->next != swapB)
			{
				swapB->prev->next = swapA;			
				swapA->next->prev = swapB;				
			}
			if (swapB->next)
			{
				swapB->next->prev = swapA;				
			}
	
			if (swapA->prev)
			{
				temp = swapA->prev;	
			}
			else
			{
				temp = NULL;
			}

			if (swapB->prev != swapA && swapA->next != swapB)
			{
				swapA->prev = swapB->prev;
			}
			else
			{
				swapA->prev = swapB;
			}
			
			if (temp)
			{
				swapB->prev = temp;			
			}
			else
			{
				swapB->prev = NULL;
			}
			
			if (swapB->prev != swapA && swapA->next != swapB)
			{
				temp = swapA->next;	
			}
			else
			{
				temp = swapA;
			}
		
			if (swapB->next)
			{
				swapA->next = swapB->next;
			}
			else
			{
				swapA->next = NULL;
			}
			
			swapB->next = temp;
			
			if (!swapB->prev)
			{
				head = swapB;
			}
		}
	
		void Display()
		{
			Node* current = head;
			while (current != NULL)
			{
				cout << current->value << endl;
				current = current->next;
			}
		}
};

int GetValue()
{
	int i;
	cout << "Please input an integer value" << endl;
	while(true)
	{
		cout << "> ";
		cin >> i;
		if (cin.good())
		{
			cout << endl;
			return i;
		}
		else
		{
			cout << endl << "Wrong Input!" << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

int GetIndex()
{
	int i;
	cout << "Please input the index" << endl;
	while(true)
	{
		cout << "> ";
		cin >> i;
		if (cin.good())
		{
			cout << endl;
			return i;
		}
		else
		{
			cout << endl << "Wrong Input!" << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void DoChoice(DoublyLinkedList* nodeList, int choice)
{
	//! 8 cases + default
	int index;
	switch (choice)
	{
		case 0:
			cout << nodeList->head->value << endl;
			break;
			
		case 1:
			cout << nodeList->getNext()->value << endl;
			break;
		
		case 2:
			nodeList->PushToBack(GetValue());
			break;
			
		case 3:
			nodeList->PopFromBack();
			break;
			
		case 4:
			cout << nodeList->GetNode(GetIndex())->value << endl;
			break;
			
		case 5:
			nodeList->Insert(GetIndex(), GetValue());
			break;
			
		case 6:
			nodeList->Remove(GetIndex());
			break;
			
		case 7:
			nodeList->SwapNode(GetIndex(), GetIndex());
			break;
			
		default:
			
			break;			
	}
}

int main()
{
	srand(time(NULL));
	DoublyLinkedList* numberList = new DoublyLinkedList();
	cout << "#######################################" << endl;
	cout << "       	Doubly Linked List			" << endl;
	cout << "#######################################" << endl;
	cout << "Initialize Double Linked List ........." << endl;
	//! use for loop invoke PushToBack (int value) for 10 times
	for (int i=1; i<=10; i++)
	{
		numberList->PushToBack(i);
	}

	//! display the doubly linked list by invoke Display()
	numberList->Display();
	
	cout << endl;
	system("PAUSE");
	
	int choice = -1;
	do
	{
		system("CLS");
		cout << "#######################################" << endl;
		cout << "         Doubly Linked List			" << endl;
		cout << "#######################################" << endl;	
		
		//! display linked list
		numberList->Display();
		
		cout << endl;
		
		cout << "=======================================" << endl;
		cout << "0. GetHead()" << endl; // display first node
		cout << "1. GetBack()" << endl; // display last node
		cout << "2. PushToBack()" << endl; 
		cout << "3. PopFromBack()" << endl; 
		cout << "4. GetNode()->Search" << endl; 
		cout << "5. Insert()" << endl; 
		cout << "6. Remove()" << endl; 
		cout << "7. Swap()" << endl; 
		cout << endl;
		cout << "-1. Exit Program" << endl;
		cout << "=======================================" << endl;
		cout << "What would you like to do?" << endl;
		cout << "> ";
		cin >> choice;
		cout << endl;
		if(cin.good())
		{
			DoChoice(numberList, choice);
		}	
		else
		{
			cout << "Wrong Input!" << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("PAUSE");
	}while(choice != -1);

		
	cout << endl;
	return 0;
}

