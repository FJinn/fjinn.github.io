#ifndef NPC_H
#define NPC_H

#include "DefaultHeaderFiles.h"

using namespace std;

class NPC : public GameObject
{
	public:
		string type;
		
		NPC(string n, string t) : GameObject(n);
		string getType();
		void displayType();
};

#endif
