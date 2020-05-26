#ifndef PLAYER_H
#define PLAYER_H

#include "AllHeaderFiles.h"
#include "Bullet.h"

using namespace std;

class Player : public GameObject
{
	public:
		int shootDelayTimer;
		int shootDelayDuration;
		int health;
		int life;
		int score;
		BULLET_TYPE type;
		vector<Bullet> bulletList;
		
		Player();
		void Update();
		void Shoot(BULLET_TYPE type);
};

#endif
