#ifndef ENEMY_H
#define ENEMY_H

#include "AllHeaderFiles.h"

class Enemy: public GameObject
{
	public:
		bool isAlive;
		
		ENEMY_TYPE enemyType;
		int updateDelayTimer;
		int updateDelayDuration;
		int killScore;
		
		int shootDelayTimer;
		int shootDelayDuration;
		bool enableShooting;
		BULLET_TYPE bulletType;
		vector<Bullet> bulletList;
		
		bool second;
		
		int moveTimer;
		vector<MoveInfo> moveList;
		
		Enemy(ENEMY_TYPE enemyType);
		void Update();
		void AddMove(DIRECTION direction, int time);
		void UpdateMove();
		void shoot();
		
		
};

#endif
