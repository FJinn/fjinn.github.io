#include <iostream>
#include <vector>
#include "windows.h"

using namespace std;

struct HighScore
{
	int score;
	string name;
};

vector <HighScore> HighScoreList;
vector <HighScore> Temp;

void Initialize()
{
	HighScoreList.resize(6);
	for (int k =0; k<5; k++)
	{
		HighScoreList[k].score = k;
	}
}

void Display()
{
	cout<< "XXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout<< "     HIGH SCORE LIST    " << endl;
	cout<< "------------------------" << endl;
	for (int j=0; j< 5; j++)
	{
	cout<<"  "<< HighScoreList[j].name<<" ---------------- "<< HighScoreList[j].score<< endl;
	}
	cout<< "XXXXXXXXXXXXXXXXXXXXXXXX"<< endl;
}

void Sorting()
{
	Temp.resize(1);
	bool isSorted = false;
	do
	{
		isSorted = true;
		for (int i =0; i < HighScoreList.size()-1; i++)
		{
			if (HighScoreList[i].score < HighScoreList[i+1].score)
			{
				Temp[0] = HighScoreList[i];
				HighScoreList[i] = HighScoreList[i+1];
				HighScoreList[i+1] = Temp[0]; 
				isSorted = false;
			}
		}
	}while (isSorted == false);
}

void InsertHighScore(string input, int num)
{
		HighScoreList[5].score = num;
		HighScoreList[5].name = input;
		Sorting();
}

void DoChoice(int choice, bool &isExit)
{
	if (choice == 1)
	{
		string input;
		int num;
		cout<< "Please Enter Your Name: ";
		cin>> input;
		cout<< "Please Enter Your Score: ";
		cin>> num;
		InsertHighScore(input, num);
		
	}
	else if (choice == 2)
	{
		HighScoreList.clear();
		Initialize();
	}
	else if (choice == 0)
	{
		isExit = true;
	}
}

int main()
{
	Initialize();
	bool isExit = false;
	int choice = -1;
	do
	{
		Display();
		cout<< "1. Enter New Score"<< endl;
		cout<< "2. Reset High Score List"<< endl;
		cout<< "0. Exit"<< endl;
		cout<< "Your Choice: ";
		cin>> choice;
		if (cin.good())
		{
			DoChoice(choice, isExit);
		}
		else
		{
			cout<< endl<< "Wrong input!!!"<< endl;
			system("PAUSE");	
		}
		cin.clear();
		cin.ignore(1000, '\n');
		system("CLS");
		
		
	}while (isExit == false);
	
	
	
	return 0;
}
