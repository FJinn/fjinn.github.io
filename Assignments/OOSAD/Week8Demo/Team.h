#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <iostream>
#include "windows.h"
#include <vector>
#include "Player.h"

using namespace std;

class Team
{
	public:
		vector<Player*> playerList;	
	
	string teamName;	
	Team()
	{
		teamName = "";
	}
	Team(string name)
	{
		teamName = name;
	}
	
	void AddPlayer(Player* player)
	{
		playerList.push_back(player);
	}
	
	void DisplayTeam()
	{
		cout<<"Team Name: "<<teamName<<endl;
		for(int i=0; i<playerList.size(); i++)
		{
			cout<<"Player "<<playerList[i]->getPlayerNumber()<<endl;
			cout<<"Player "<<playerList[i]->getRole()<<endl;
		}
	}
	
	string getTeamName()
	{
		return teamName;
	}
		
};

#endif
