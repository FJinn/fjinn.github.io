#ifndef PLAYER_H
#define PLAYER_H

#include "DefaultHeaderFiles.h"

using namespace std;

class Player : public GameObject
{
	public:
		string gender;
		
		Player(string n, string g) : GameObject(n);
		string getGender();
		void displayGender();
};

#endif
