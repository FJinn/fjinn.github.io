#ifndef STADIUM_H
#define _H

#include <string>
#include <iostream>
#include "windows.h"
#include "Team.h"

using namespace std;

class Stadium
{
public:
	Team* teams[2];
	string stadiumName;
	
	Stadium()
	{
		stadiumName = "";
	}	
	
	Stadium(string name)
	{
		stadiumName = name;
	}
	
	void DisplayName()
	{
		cout<<"Stadium "<< stadiumName<<endl;
		for(int i=0;i<2;i++)
		{
			cout<<"Team "<<i+1<< ": "<<teams[i]->getTeamName()<<endl;
		}
	}
};

#endif
