#include <iostream>
#include <ctime>
#include <string>
#include "windows.h"
#include "conio_yp.h"

using namespace std;

//! enumeration -> define custom struct
enum GameState
{
	MAIN_MENU = 0,
	CHARACTER_SELECTION,
	BATTLE,
	RESULT
};

GameState gameState = MAIN_MENU;

int choice = -1;

enum HeroType
{
	WARRIOR = 0,
	RANGER,
	MAGE,
	TOTAL_HERO_TYPE
};

class Hero
{
	public:
		string name;
		HeroType type;
		int health;
		int offense;
		int defense;
		
		Hero(string name)
		{
			this->name = name;
		}
		
		void InitializeStats()
		{
			if(type == WARRIOR)
			{
				health = rand()%20 +80;
				offense = rand()%20 + 30;
				defense = rand()%20 + 50;
			}
			else if (type == RANGER)
			{
				health = rand()%20 + 50;
				offense = rand()%20 + 80;
				defense = rand()%20 + 30;
			}
			else if (type == MAGE)
			{
				health = rand()%20 +30;
				offense = rand()%20 + 50;
				defense = rand()%20 + 80;
			}
		}
		
		string GetHeroTypeName()
		{
			if(type == WARRIOR)
			{
				return "Warrior";
			}
			else if (type == RANGER)
			{
				return "Ranger";
			}
			else if (type == MAGE)
			{
				return "Mage";
			}
		}
		
		void DisplayStats(int x, int y)
		{
			gotoxy(x,y);
			cout<<"Name: "<<name;
			gotoxy(x,y+1);
			cout<<"Class: " <<GetHeroTypeName();
			gotoxy(x, y+2);
			cout<<"Health: "<<health;
			gotoxy(x, y+3);
			cout<<"Offense: "<<offense;
			gotoxy(x, y+4);
			cout<<"Defense: "<<defense;
		}
};

Hero* player;
Hero* enemy;

void DisplayMainMenu()
{
	cout<<"==========================="<<endl;
	cout<<"            WELCOME        "<<endl;
	cout<<"                 to        "<<endl;
	textcolor(LIGHTRED);
	cout<<"       BATTLE SIMULATION   "<<endl;
	textcolor(WHITE);
	cout<<"==========================="<<endl;
	system("PAUSE");
	gameState = CHARACTER_SELECTION;
	choice = 0;
}

void DisplayCharacterSelection()
{
	string name;
	cout<<"==========================="<<endl;
	cout<<"Enter your character name: ";
	getline(cin, name);
	cout<<"==========================="<<endl;
	cout<< "Please select you character class"<<endl;
	cout<<"1. Warrior"<<endl;
	cout<<"2. Ranger"<<endl;
	cout<<"3. Mage"<<endl;
	cout<<"==========================="<<endl;
	cout<<"Your input: ";
	cin>>choice;
	
	if(cin.good())
	{
		player = new Hero(name);
		player->type = (HeroType)(choice -1);
		player->InitializeStats();
		
		enemy = new Hero("Rita Repulsa");
		enemy->type = (HeroType)(abs(rand()-choice)%TOTAL_HERO_TYPE);
		enemy->InitializeStats();
		gameState = BATTLE;
	}
	else
	{
		cout<<endl<<"Wrong Input!!!!!!"<<endl;
		system("PAUSE");
	}
	
	cin.clear();
	cin.ignore(1000, '\n');
}

void BattleSimulation()
{
	float playerBattleFormula = enemy->health / (player->offense *(1.0f - enemy->defense/150.0f));
	float enemyBattleFormula = player->health / (enemy->offense *(1.0f - player->defense/150.0f));
	cout<<endl<<endl;
	if(playerBattleFormula > enemyBattleFormula)
	{
		cout<<"You lose in " << enemyBattleFormula<<" turns"<<endl;
	}
	else
	{
		cout<<"You win in " << playerBattleFormula<<" turns"<<endl;
	}
}

void DisplayBattleScreen()
{
	player->DisplayStats(1,10);
	enemy->DisplayStats(30,10);
	
	BattleSimulation();
	
	cout<<"========================================"<<endl;
	cout<<"1. Try Again"<<endl;
	cout<<"2. Exit"<<endl;
	cin>>choice;
	if(cin.good())
	{
		if(choice == 1)
		{
			gameState = CHARACTER_SELECTION;
		}
		else if(choice == 2)
		{
			choice = -1;
		}
	}
	else
	{
		cout<<endl<<"Wrong Input!!!!!!"<<endl;
		system("PAUSE");
	}
	cin.clear();
	cin.ignore(1000, '\n');
	cout<<endl;
	system("PAUSE");
}

int main(int argc, char** argv) {
	
	system("mode con: cols=60 lines=35");
	
	srand(time(NULL));
	textcolor(WHITE);
	
	do
	{
		if(gameState == MAIN_MENU)
		{
			DisplayMainMenu();
		}
		else if(gameState == CHARACTER_SELECTION)
		{
			DisplayCharacterSelection();
		}
		else if(gameState == BATTLE)
		{
			DisplayBattleScreen();
		}
		system("CLS");		
	}while(choice != -1);
	
	return 0;
}
