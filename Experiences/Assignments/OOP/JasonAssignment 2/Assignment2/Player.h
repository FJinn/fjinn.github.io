#ifndef PLAYER_H
#define PLAYER_H

#include "DefaultHeaderFiles.h"

using namespace std;

class Player : public GameObject
{
public:
	string gender;
	
	Player(string g);
	string getGender();
	void displayGender();	
};

#endif
