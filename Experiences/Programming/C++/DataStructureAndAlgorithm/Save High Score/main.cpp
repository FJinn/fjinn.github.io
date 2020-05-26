#include <iostream>
#include "windows.h"
#include <ctime>
#include "conio_yp.h"
#include <cmath>
#include <limits>
#include <fstream>
#include <string>

using namespace std;
//!GAME
bool isExit = false;
int choice = -1;

//!HIGHSCORE
const int maxPlayer = 5;
string names [maxPlayer];
int scores [maxPlayer];
ofstream myOutputFile;
ifstream myInputFile;


void displayScores(const int maxPlayer)
{
	int id = 0;
	string str;
	
	//! easy mode ranking
	gotoxy(6,8);
	cout << "==============" << endl;
	gotoxy(6,9);
	cout << " Easy Mode ";
	gotoxy(6,10);
	cout << "==============" << endl;
	myInputFile.open("easyHighScore.txt");
	for(int i=0; i<maxPlayer * 2; i++)
	{
		if(!myInputFile.eof())
		{
			if(i % 2 ==0)
			{
				id++;
				getline(myInputFile, str);
				gotoxy(6,12+i);
				cout << id << ". " << str << " : "; //! display name
			}
			else
			{
				getline(myInputFile, str);
				cout << str << endl << endl; //! display score
			}
		}
	}	
	myInputFile.close();
	
	//! normal mode ranking
	gotoxy(33,8);
	cout << "==============" << endl;
	gotoxy(33,9);
	cout << " Normal Mode ";
	gotoxy(33,10);
	cout << "==============" << endl;
	id = 0; //! reset counter for ranking
	myInputFile.open("normalHighScore.txt");
	for(int i=0; i<maxPlayer * 2; i++)
	{
		if(!myInputFile.eof())
		{
			if(i % 2 ==0)
			{
				id++;
				getline(myInputFile, str);
				gotoxy(33,12+i);
				cout << id << ". " << str << " : "; //! display name
			}
			else
			{
				getline(myInputFile, str);
				cout << str << endl << endl; //! display score
			}
		}
	}	
	myInputFile.close();
	
	//! hard mode ranking
	gotoxy(62,8);
	cout << "==============" << endl;
	gotoxy(62,9);
	cout << " Normal Mode ";
	gotoxy(62,10);
	cout << "==============" << endl;
	id = 0; //! reset counter for ranking
	myInputFile.open("hardHighScore.txt");
	for(int i=0; i<maxPlayer * 2; i++)
	{
		if(!myInputFile.eof())
		{
			if(i % 2 ==0)
			{
				id++;
				getline(myInputFile, str);
				gotoxy(62,12+i);
				cout << id << ". " << str << " : "; //! display name
			}
			else
			{
				getline(myInputFile, str);
				cout << str << endl << endl; //! display score
			}
		}
	}	
	myInputFile.close();
}

void sort(string names[], int scores[], const int maxPlayer)
{
	for(int i=0; i<maxPlayer-1; i++)
	{
		for(int j=i+1; j<maxPlayer; j++)
		{
			if(scores[i] > scores[j])
			{
				string storeName = names[i];
				int storeScore = scores[i];
				names[i] = names[j];
				scores[i] = scores[j];
				names[j] = storeName;
				scores[j] = storeScore;
			}
		}
	}
}

void setHighscore(int level, string pName, int score)
{
	string storeName;
	int storeScore;
	
	string storeName1;
	int storeScore1;
	bool isSetHighscore = false;
	
	if(level == 1)
	{
		int id = 0;
		int namesID = 0;
		int scoresID = 0;
		string str;
		string playername;
		playername = pName;
		myInputFile.open("easyHighscore.txt");
		//! get text from the txt file and set in the array 
		while(!myInputFile.eof())
		{
			getline(myInputFile, str);
			if(str.length() > 0)
			{
				if(id % 2 == 0)
				{
					names[namesID] = str;
					namesID++;
				}
				else
				{
					scores[scoresID] = atoi(str.c_str());
					scoresID++;
				}
				id++;
			}
		}
		myInputFile.close();
		
		//! compare with array and save score to TXT
		myOutputFile.open("easyHighscore.txt");
		for(int i=0; i<maxPlayer; i++)
		{
			if(score <= scores[i] && isSetHighscore == false)
			{
				storeScore = scores[i];
				storeName = names[i];
				scores[i] = score;
				gotoxy(1,46);
				names[i] = playername;
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
				isSetHighscore = true;
			}
			else if(storeScore <= scores[i])
			{
				storeName1 = names[i];
				storeScore1 = scores[i];
				
				scores[i] = storeScore;
				names[i] = storeName;
				
				//! save score to txt
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
				
				storeName = storeName1;
				storeScore = storeScore1;
			}
			else
			{
				//! save unsorted score to txt
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
			}
		}
		myOutputFile.close();
	}
	else if(level == 2)
	{
		int id = 0;
		int namesID = 0;
		int scoresID = 0;
		string str;
		string playername;
		playername = pName;
		myInputFile.open("normalHighscore.txt");
		//! get text from the txt file and set in the array 
		while(!myInputFile.eof())
		{
			getline(myInputFile, str);
			if(str.length() > 0)
			{
				if(id % 2 == 0)
				{
					names[namesID] = str;
					namesID++;
				}
				else
				{
					scores[scoresID] = atoi(str.c_str());
					scoresID++;
				}
				id++;
			}
		}
		myInputFile.close();
		
		//! compare with array and save score to TXT
		myOutputFile.open("normalHighscore.txt");
		for(int i=0; i<maxPlayer; i++)
		{
			if(score <= scores[i] && isSetHighscore == false)
			{
				storeScore = scores[i];
				storeName = names[i];
				scores[i] = score;
				gotoxy(1,46);
				names[i] = playername;
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
				isSetHighscore = true;
			}
			else if(storeScore <= scores[i])
			{
				storeName1 = names[i];
				storeScore1 = scores[i];
				
				scores[i] = storeScore;
				names[i] = storeName;
				
				//! save score to txt
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
				
				storeName = storeName1;
				storeScore = storeScore1;
			}
			else
			{
				//! save unsorted score to txt
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
			}
		}
		myOutputFile.close();
	}
	else if(level == 3)
	{
		int id = 0;
		int namesID = 0;
		int scoresID = 0;
		string str;
		string playername;
		playername = pName;
		myInputFile.open("hardHighscore.txt");
		//! get text from the txt file and set in the array 
		while(!myInputFile.eof())
		{
			getline(myInputFile, str);
			if(str.length() > 0)
			{
				if(id % 2 == 0)
				{
					names[namesID] = str;
					namesID++;
				}
				else
				{
					scores[scoresID] = atoi(str.c_str());
					scoresID++;
				}
				id++;
			}
		}
		myInputFile.close();
		
		//! compare with array and save score to TXT
		myOutputFile.open("hardHighscore.txt");
		for(int i=0; i<maxPlayer; i++)
		{
			if(score <= scores[i] && isSetHighscore == false)
			{
				storeScore = scores[i];
				storeName = names[i];
				scores[i] = score;
				gotoxy(1,46);
				names[i] = playername;
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
				isSetHighscore = true;
			}
			else if(storeScore <= scores[i])
			{
				storeName1 = names[i];
				storeScore1 = scores[i];
				
				scores[i] = storeScore;
				names[i] = storeName;
				
				//! save score to txt
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
				
				storeName = storeName1;
				storeScore = storeScore1;
			}
			else
			{
				//! save unsorted score to txt
				myOutputFile << names[i] << endl;
				myOutputFile << scores[i] << endl;
			}
		}
		myOutputFile.close();
	}
}

void HighScore()
{
	string choice = " ";
	system("CLS");
	gotoxy(17,3);
	cout << "==========================================================";
	gotoxy(17,4);
	cout << "~~**--===========~~*[ HiGH SCORE ] *~~==============--**~~";
	gotoxy(17,5);
	cout << "==========================================================";
	gotoxy(34,26);
	cout << "1 - Main Menu" << endl;
	gotoxy(34,27);
	displayScores(maxPlayer);
	gotoxy(34,27);
	cin >> choice;
	if(choice == "1")
	{
		
	} 
	system("CLS");
}

int main() 
{
	system("mode con: cols=80 lines=45");
	int option = 0;
	string pName;
	int score;
	int level;
	do
	{
		cout << "Option: " << endl;
		cout << "1.Set High Score" << endl;
		cout << "2.View High Score" << endl;
		cout << "3. Exit" << endl;
		cin >> option;
		if(option == 1)
		{
			cout << "Choose Your Level (1 for normal, 2 for easy, 3 for hard)" << endl;
			cin >> level;
			cout << "Enter your name: " << endl;
			cin >> pName;
			cout << "Enter your score: " << endl;
			cin >> score;
			setHighscore(level, pName, score);
		}
		else if(option == 2)
		{
			HighScore();
		}
		else if(option == 3)
		{
			isExit = true;
		}
		
		system("PAUSE");
		system("CLS");
	}while(!isExit);
	
	system("PAUSE");
	return 0;
}
