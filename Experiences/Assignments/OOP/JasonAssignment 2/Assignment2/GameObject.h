#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "DefaultHeaderFiles.h"

using namespace std;

class GameObject
{
protected:
	string name;
public:
	GameObject();
	string getName();
	void Display();
};

#endif
