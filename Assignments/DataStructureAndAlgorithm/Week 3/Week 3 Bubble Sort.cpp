#include <iostream>
#include "windows.h"
#include <vector>
#include <ctime>

using namespace std;

vector <char> Charlist;

void RandomOrder()
{
	for (int i=0; i<Charlist.size(); i++)
	{
		int randomIndex;
		do
		{
		randomIndex = rand () % Charlist.size();
		}while(randomIndex == i);
		char temp = Charlist[i];
		Charlist[i]= Charlist[randomIndex];
		Charlist[randomIndex]= temp;
	}
}
 
void BubbleSortAscending()
{
	bool isSorted;
	
	do
	{
		isSorted = true;
		for (int i=0; i<Charlist.size()-1; i++)
		{
			if(Charlist[i]>Charlist[i+1])
			{
				char temp = Charlist[i];
				Charlist[i] = Charlist[i+1];
				Charlist[i+1] = temp;
				isSorted = false;	
			}	
		}
		
	}while(!isSorted);
}

void BubbleSortDescending()
{
	bool isSorted;
	
	do
	{
		isSorted = true;
		for (int i=0; i<Charlist.size()-1; i++)
		{
			if(Charlist[i]<Charlist[i+1])
			{
				char temp = Charlist[i];
				Charlist[i] = Charlist[i+1];
				Charlist[i+1] = temp;
				isSorted = false;	
			}	
		}
		
	}while(!isSorted);
}

void DisplayVector()
{
	for(int i=0; i<Charlist.size(); i++)
	{
		cout<<"[" << i << "} : "<< Charlist[i]<< endl;
	}
}
 
int main ()
{
	srand(time(NULL));
	int size = 10;
	for (int i=0; i<size; i++)
	{
		Charlist.push_back(i+65);
	}
	int choice = -1;
	bool isExit = false;
	do
	{
		DisplayVector();
		cout << "===============" << endl;
		cout << "1. Randomize order"<< endl;
		cout << "2. Sort in ascending order"<< endl;
		cout << "3. Sort in descending order"<< endl;
		cout << "4. Exit!"<< endl;
		cout <<"==============="<< endl;
		cout <<"Your Choice : "<< endl;
		cin >> choice;
		
		if (choice == 1 )
		{
			RandomOrder();
		}
		else if (choice == 2)
		{
			BubbleSortAscending();
		}
		else if (choice == 3)
		{
			BubbleSortDescending();
		}
		else if (choice == 4)
		{
			isExit= true;
		}

	system("PAUSE");
	system("CLS");
	}while(!isExit);
	

	return 0;
}
