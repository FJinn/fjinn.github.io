#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "DefaultHeaderFiles.h"

using namespace std;

class GameObject
{
	protected:
		string name;
	public:
		GameObject(string n);
		string getName();
		void Display();
};

#endif
