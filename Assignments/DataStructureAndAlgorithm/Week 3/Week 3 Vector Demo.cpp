#include <iostream>
#include "windows.h"
#include <vector>
#include <ctime>

using namespace std;
// declare a vector container - charVector(empty)
vector <char> charVector;

void VectorInitialize()
{
	// inserting to vector -> push_back
	for(int i=0; i<26; i++)
	{
		charVector.push_back(i+65);
	}
}

void DisplayVector()
{
	// vector total capacity is using the function call ->size()
	for(int i=0; i<charVector.size(); i++)
	{
		cout<< "["<< charVector[i]<< "]"<< endl;
	}
}

void DoChoice(int choice, bool& isExit)
{
	if(choice == 1)
	{
		char userInput;
		cout<< "Please enter a character: ";
		cin >> userInput;
		charVector.push_back(userInput);
	}
	else if(choice ==2)
	{
		char userInput;
		cout<< "Please enter a character: ";
		cin >> userInput;
		charVector.insert(charVector.begin(), userInput);
	}
	else if(choice ==3)
	{
		char userInput;
		cout<< "Please enter a character: ";
		cin >> userInput;
		int inputPosition;
		cout<< "Please enter char position: ";
		cin>> inputPosition;
		charVector.insert(charVector.begin()+(inputPosition-1), userInput);		
	}
	else if(choice ==4)
	{
		if(charVector.empty())
		{
			cout<< endl << "Vector is EMPTY!"<< endl;
			system("PAUSE");
		}
		else
		{
			charVector.pop_back();
		}
	}
	else if(choice ==5)
	{
		if(charVector.empty())
		{
			cout<< endl << "Vector is EMPTY!"<< endl;
			system("PAUSE");
		}
		else
		{
			charVector.erase(charVector.begin());
		}		
	}
	else if(choice ==6)
	{
		if(charVector.empty())
		{
			cout<< endl << "Vector is EMPTY!"<< endl;
			system("PAUSE");
		}
		else
		{
			int inputPosition;
			cout<< "Please enter char position: ";
			cin>> inputPosition;
			charVector.erase(charVector.begin()+(inputPosition-1));
		}	
	}
	else if(choice ==7)
	{
		if (charVector.size() >= 2)
		{
			int inputPosition;
			cout<< "Please enter first position: ";
			cin>> inputPosition;	
			int inputPosition2;
			cout<< "Please enter second position: ";
			cin>> inputPosition2;	
			iter_swap(charVector.begin()+ (inputPosition -1), charVector.begin()+ (inputPosition2 -1));
			/*
			char temp = charVector[inputPosition-1];
			charVector[inputPosition -1] = charVector[inputPosition2 -1];
			charVector[inputPosition2 -1] = temp;
			*/
			
		}
		else
		{
			cout<< "There is not enough char to swap!"<< endl;
			system ("PAUSE");
		}
	}
	else if(choice ==8)
	{
		if (charVector.size()>=2)
		{
			int Rand1;
			int Rand2;
			Rand1 = rand() % charVector.size();
			Rand2 = rand() % charVector.size();
			iter_swap(charVector.begin()+ (Rand1 -1), charVector.begin()+ (Rand2 -1));	
			cout<< " Characters "<< Rand1<< " and "<< Rand2 << " have swapped!"<< endl;
			system("PAUSE");
		}
		else
		{
			cout<< "There is not enough char to swap!"<< endl;
			system ("PAUSE");
		}
	}
	else if(choice ==9)
	{
		charVector.clear();
	}
	else if(choice ==10)
	{
		isExit = true;
	}
	
}

int main ()
{
	srand(time(NULL));
	VectorInitialize();
	
	int choice =-1;
	bool isExit = false;
	do
	{
		DisplayVector();
		cout<< "================" << endl;
		cout<< "1. Add character to the back"	<< endl;
		cout<< "2. Add character to the front"	<< endl;
		cout<< "3. Add character at specific index (position)"	<< endl;
		cout<< "4. Remove character at the back"	<< endl;
		cout<< "5. Remove character at the front"	<< endl;
		cout<< "6. Remove character at specific index (position)"	<< endl;
		cout<< "7. Swap character at specific indexes (positions)"	<< endl;
		cout<< "8. Swap two characters at random location"	<< endl;
		cout<< "9. Delete all characters"	<< endl;
		cout<< "10. Exit!"	<< endl;
		cout<< "Your Choice: ";
		cin>> choice;
		if(cin.good())
		{
			DoChoice(choice, isExit);
		}
		else
		{
			cout<< endl<< "Wrong Input !!!"<< endl;
			system("PAUSE");		
		}
		cin.clear();
		cin.ignore(1000, '\n');
		
		system("CLS");
	}while(!isExit);
	

	return 0;
}
