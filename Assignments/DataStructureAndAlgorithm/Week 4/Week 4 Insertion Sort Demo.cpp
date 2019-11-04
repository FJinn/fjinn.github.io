#include <iostream>
#include <vector>
#include <ctime>
#include "windows.h"

using namespace std;

vector <char> charList;

void RandomizeOrder()
{
	for (int i=0; i< charList.size(); i++)
	{
		int randomIndex;
		do
		{
			randomIndex = rand()% charList.size();
		}while(randomIndex == i);
		char temp = charList[i];
		charList[i] = charList[randomIndex];
		charList[randomIndex] = temp; 
	}
}

void InsertionSortAscending()
{
	for(int i=0; i<charList.size()-1; i++)
	{
		int currentIndex = i;
		while (charList[currentIndex]>charList[currentIndex+1])
		{
			char temp = charList[currentIndex];
			charList[currentIndex] = charList[currentIndex+1];
			charList[currentIndex+1] = temp;
			currentIndex--;
		}
	}
}

void InsertionSortDescending()
{
	for(int i= charList.size(); i>0; i--)
	{
		int currentIndex = i;
		while (charList[currentIndex]>charList[currentIndex-1] )
		{
			char temp = charList[currentIndex];
			charList[currentIndex] = charList[currentIndex-1];
			charList[currentIndex-1] = temp;
			currentIndex++;
		}
	}
}

void DisplayVector()
{
	for(int i=0; i< charList.size(); i++)
	{
		cout<< "["<< i << "}:"<<charList[i]<< endl;
	}
}

int main()
{	
	srand(time(NULL));
	bool isExit = false;
	int size = 10;
	for(int i=0; i<size; i++)
	{
		charList.push_back(i+65);
	}
	int choice = -1;
	do
	{
		DisplayVector();
		cout << "================================"<< endl;
		cout << "1. Randomize Order" << endl;
		cout << "2. Ascending Order" << endl;
		cout << "3. Descending Order" << endl;
		cout << "4. Exit!!!" << endl;
		cout << "================================"<< endl;
		cout << "Your Choice: ";
		cin>> choice;
		if (choice ==1)
		{
			RandomizeOrder();
		}
		else if (choice == 2)
		{
			InsertionSortAscending();
		}
		else if (choice == 3)
		{
			InsertionSortDescending();
		}
		else if (choice == 4)
		{
			isExit = true;
		}
		system("CLS");
		system("PAUSE");
	}while(!isExit);

	return 0;
}
