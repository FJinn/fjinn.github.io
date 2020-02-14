#ifndef NPC_H
#define NPC_H

#include "DefaultHeaderFiles.h"

using namespace std;

class NPC : public GameObject
{
public:
	string type;

	NPC();
	
	string getType();
	void displayType();	
};

#endif
