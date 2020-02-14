#include <iostream>
#include <ctime>
#include <string>
#include <vector>
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

enum CharAction
{
	ATTACK =0,
	BLOCK,
	DODGE,
	STUN,
	CRITICAL,
	HEAL,
	TOTAL_CHAR_ACTION	
};

enum HeroType
{
	WARRIOR = 0,
	RANGER,
	MAGE,
	TOTAL_HERO_TYPE
};

enum EnemyType
{
	MINION = 0,
	MINI_BOSS,
	BOSS,
	TOTAL_ENEMY_TYPE
};

class Character
{
	public:
		string name;
		int health;
		int offense;
		int defense;
		vector<CharAction> actionList;
		//! abstract method
//		virtual void InitializeState() = 0;

		Character(string name)
		{
			this->name = name;
		}
		
		string GetCharActionName(CharAction ca)
		{
			if(ca == ATTACK)
			{
				return "Attack";
			}
			else if(ca == BLOCK)
			{
				return "Block";
			}
			else if(ca == DODGE)
			{
				return "Dodge";
			}
			else if(ca == STUN)
			{
				return "Stun";
			}
			else if(ca == CRITICAL)
			{
				return "Critical";
			}
			else if(ca == HEAL)
			{
				return "Heal";
			}
		}
};

class Hero : public Character
{
	public:
//		string name;
		HeroType type;
		
		Hero(string name) : Character(name)
		{}
		
		virtual	void InitializeStats() = 0;
/*		{
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
*/		
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

class Warrior : public Hero
{
	public:
		Warrior(string name) : Hero(name)
		{
			type = WARRIOR;
			InitializeStats();
		}
		
		void InitializeStats()
		{
			health = rand()%20 +80;
			offense = rand()%20 + 30;
			defense = rand()%20 + 50;
			
			actionList.push_back(ATTACK);
			actionList.push_back(BLOCK);
			actionList.push_back(DODGE);
			actionList.push_back(STUN);
		}
};

class Ranger : public Hero
{
	public:
		Ranger(string name) : Hero(name)
		{
			type = RANGER;
			InitializeStats();
		}
		
		void InitializeStats()
		{
			health = rand()%20 + 50;
			offense = rand()%20 + 80;
			defense = rand()%20 + 30;
		
			actionList.push_back(ATTACK);
			actionList.push_back(BLOCK);
			actionList.push_back(DODGE);
			actionList.push_back(CRITICAL);
		}
};

class Mage : public Hero
{
	public:
		Mage(string name) : Hero(name)
		{
			type = MAGE;
			InitializeStats();
		}
		
		void InitializeStats()
		{
			health = rand()%20 +30;
			offense = rand()%20 + 50;
			defense = rand()%20 + 80;
		
			actionList.push_back(ATTACK);
			actionList.push_back(BLOCK);
			actionList.push_back(DODGE);
			actionList.push_back(HEAL);
		}
};

class Enemy : public Character
{
	public:
		string name;
		EnemyType type;
		
		Enemy(string name): Character(name)
		{
			this->name = name;
		}
		
		virtual	void InitializeStats() = 0;
	
		string GetEnemyTypeName()
		{
			if(type == MINION)
			{
				return "Minion";
			}
			else if (type == MINI_BOSS)
			{
				return "Mini Boss";
			}
			else if (type == BOSS)
			{
				return "Boss";
			}
		}
		
		void DisplayStats(int x, int y)
		{
			gotoxy(x,y);
			cout<<"Name: "<<name;
			gotoxy(x,y+1);
			cout<<"Class: " <<GetEnemyTypeName();
			gotoxy(x, y+2);
			cout<<"Health: "<<health;
			gotoxy(x, y+3);
			cout<<"Offense: "<<offense;
			gotoxy(x, y+4);
			cout<<"Defense: "<<defense;
		}
};

class Minion : public Enemy
{
	public:
		Minion(string name) : Enemy(name)
		{
			type = MINION;
			InitializeStats();
		}
		
		void InitializeStats()
		{
			health = rand()%20 +80;
			offense = rand()%20 + 30;
			defense = rand()%20 + 50;
			
			actionList.push_back(ATTACK);
			actionList.push_back(BLOCK);
			actionList.push_back(DODGE);
			actionList.push_back(STUN);
		}
};

class MiniBoss : public Enemy
{
	public:
		MiniBoss(string name) : Enemy(name)
		{
			type = MINI_BOSS;
			InitializeStats();
		}
		
		void InitializeStats()
		{
			health = rand()%20 + 50;
			offense = rand()%20 + 80;
			defense = rand()%20 + 30;
		
			actionList.push_back(ATTACK);
			actionList.push_back(BLOCK);
			actionList.push_back(DODGE);
			actionList.push_back(CRITICAL);
		}
};

class Boss : public Enemy
{
	public:
		Boss(string name) : Enemy(name)
		{
			type = BOSS;
			InitializeStats();
		}
		
		void InitializeStats()
		{
			health = rand()%20 +30;
			offense = rand()%20 + 50;
			defense = rand()%20 + 80;
		
			actionList.push_back(ATTACK);
			actionList.push_back(BLOCK);
			actionList.push_back(DODGE);
			actionList.push_back(HEAL);
		}
};

Hero* player;
Enemy* enemy;

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
		if(choice == 1)
		{
			player = new Warrior(name);
		}
		else if (choice == 2)
		{
			player = new Ranger(name);
		}
		else if (choice == 3)
		{
			player = new Mage(name);
		}
		
		//! enemy
		choice = rand()%TOTAL_ENEMY_TYPE +1;
		if(choice ==1)
		{
			enemy = new Minion("Steven");
		}
		else if (choice == 2)
		{
			enemy = new MiniBoss("Steven");
		}
		else if(choice == 3)
		{
			enemy = new Boss("Steven");
		}
		
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

bool skip = false;
bool block = false;
void BattleSimulation(Character* actor, Character* target)
{
	if(actor->actionList[choice-1] == ATTACK)
	{
		int tempDamage = actor->offense * (1.0f - target->defense / 100.0f);
		target->health -= tempDamage;
		cout<<actor->name<<" Attack "<<target->name<<" with "<<tempDamage<<" damage!"<<endl;
	}
	else if(actor->actionList[choice-1] == BLOCK)
	{
		block = true;
		actor->health -= 1;
		cout<<actor->name<<" Block "<<target->name<<" damage and receive only 1 damage!"<<endl;
	}
	else if(actor->actionList[choice-1] == DODGE)
	{
		skip = true;
		cout<<actor->name<<" Dodge "<<target->name<<" damage!"<<endl;
	}
	else if(actor->actionList[choice-1] == STUN)
	{
		skip = true;
		int tempDamage = actor->offense * (1.0f - target->defense / 100.0f);
		target->health -= tempDamage;
		cout<<actor->name<<" Stun "<<target->name<<" and attack with "<<tempDamage<<" damage!"<<endl;
	}
	else if(actor->actionList[choice-1] == CRITICAL)
	{
		int tempDamage = actor->offense * (1.0f - target->defense / 100.0f);
		target->health -= tempDamage*3;
		cout<<actor->name<<" deal Critical Hit to "<<target->name<<" with "<<tempDamage*3<<" damage!"<<endl;
	}
	else if(actor->actionList[choice-1] == HEAL)
	{
		int tempDamage = actor->offense * (1.0f - target->defense / 100.0f);
		target->health += tempDamage*1.5;
		cout<<actor->name<<" Heal "<<target->name<<" with "<<tempDamage*1.5<<" health points!"<<endl;
	}
	
/*	float playerBattleFormula = enemy->health / (player->offense *(1.0f - enemy->defense/150.0f));
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
	*/
}

void ShowBattleResult()
{
	string resultText ="";
	if(player->health <= 0 && enemy->health<= 0)
	{
		resultText = "Both are daed. It is a draw Battle";
	}
	else if(player->health <= 0)
	{
		resultText = "You are dead. You LOST!";
	}
	else if(enemy->health <= 0)
	{
		resultText = "Enemy is dead. You win.";
	}
	cout<<"========================================"<<endl;
	cout<<resultText<<endl;
	
	cout<<"1. Continue your journey"<<endl;
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

void DisplayBattleScreen()
{
	player->DisplayStats(1,10);
	enemy->DisplayStats(30,10);
	
	cout<<"========================================"<<endl;
	cout<<"        Please choose an ACTION"<<endl;
	cout<<"========================================"<<endl;
	for(int i=0; i<player->actionList.size(); i++)
	{
		cout<<(i+1)<<"."<<player->GetCharActionName(player->actionList[i])<<endl;
	}
	cout<<"========================================"<<endl;
	cout<<"Your action selection: ";
	cin>>choice;
	BattleSimulation(player, enemy);
	if( skip == false && block == false)
	{
		cout<<"Enemy: "<<endl;
		choice = 1; // rand()%enemy->actionList.size()+1
		BattleSimulation(enemy, player);
	}
	else if(block == true && skip == false)
	{
		cout<<"Enemy deals damage to you but you blocked."<<endl;
		block = false;	
	}
	else if (skip == true)
	{
		cout<<"Enemy did nothing on this turn."<<endl;
		skip =  false;
	}
	cout<<endl;
	system("PAUSE");
	system("CLS");
	if(player->health <= 0 || enemy->health <= 0)
	{
		ShowBattleResult();
	}
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
