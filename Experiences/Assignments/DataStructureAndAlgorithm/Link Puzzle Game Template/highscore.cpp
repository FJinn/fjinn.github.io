#include "highscore.h"

using namespace std;
//!GAME
bool isBack = false;

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
	system("CLS");
	gotoxy(34,27);
	displayScores(maxPlayer);
}

void HighScoreMenu() 
{
	system("mode con: cols=80 lines=45");

	HighScore();
	
	cout << endl << endl << endl << endl;
	system("PAUSE");
	system("CLS");
}
