#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "windows.h"

using namespace std;

class Player
{
	public:
		int playerNumber;
		string role;
		
		Player()
		{
			playerNumber = 0;
			role = "";
		}
		
		Player(int num, string r)
		{
			playerNumber = num;
			role = r;
		}
		int getPlayerNumber()
		{
			return playerNumber;
		}	
		string getRole()
		{
			return role;
		}
};

#endif
