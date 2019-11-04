#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

class FormationBehaviour
{
	public:
		virtual string formation() = 0;
		virtual string description() = 0;
		virtual int getStrikerNum() =0;
		virtual int getDefenderNum() =0;
		virtual int getMidNum() =0;
};

class Offensive : public FormationBehaviour
{
	string formation()
	{
		return "O formation";
	}
	string description()
	{
		return "Offensive = 4 3 3";
	}
	
	int getStrikerNum()
	{
		return 4;
	}
	
	int getDefenderNum()
	{
		return 3;
	}
	
	int getMidNum()
	{
		return 3;
	}
};

class Defensive : public FormationBehaviour
{
	string formation()
	{
		return "D formation";
	}
	string description()
	{
		return "Defensive = 1 4 5";
	}
	
	int getStrikerNum()
	{
		return 1;
	}
	
	int getDefenderNum()
	{
		return 5;
	}
	
	int getMidNum()
	{
		return 4;
	}
};

class Balance : public FormationBehaviour
{
	string formation()
	{
		return "B formation";
	}
	string description()
	{
		return "Balance = 4 2 4";
	}
	
	int getStrikerNum()
	{
		return 4;
	}
	
	int getDefenderNum()
	{
		return 4;
	}
	
	int getMidNum()
	{
		return 2;
	}
};

class FormationStrategy
{
private:
	FormationBehaviour* formationBehaviour;
public:
	FormationStrategy(){}
	void setBehaviour(FormationBehaviour* fb)
	{
		formationBehaviour = fb;
	}
	string getDescription()
	{
		return formationBehaviour->description();
	}
	string getFormation()
	{
		return formationBehaviour->formation();
	}
	
	int StrikerNum()
	{
		return formationBehaviour->getStrikerNum();
	}
	
	int DefenderNum()
	{
		return formationBehaviour->getDefenderNum();
	}
	
	int MidNum()
	{
		return formationBehaviour->getMidNum();
	}
};

class Team
{
private: 
	FormationStrategy* formationStrategy;
	
public:
	vector<Player*> playerList;
	Team(FormationStrategy* fs)
	{
		formationStrategy = fs;
	}
	
	void AddPlayer(Player* p)
	{
		playerList.push_back(p);
	}
	
	string Formation()
	{
		return formationStrategy->getFormation();
	}
	
	string Description()
	{
		return formationStrategy->getDescription();
	}
	
	int StrikerNum()
	{
		return formationStrategy->StrikerNum();
	}
	
	int DefenderNum()
	{
		formationStrategy->DefenderNum();
	}
	
	int MidNum()
	{
		formationStrategy->MidNum();
	}
};

#endif

