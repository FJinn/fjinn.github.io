#ifndef ENEMY_MONSTER_H
#define ENEMY_MONSTER_H


#include "DefaultHeaderFiles.h"

using namespace std;

class EnemyMonster : public NPC
{
public:
	string mode;
	
	EnemyMonster();
	string getMode();
	void displayMode();
};

#endif
