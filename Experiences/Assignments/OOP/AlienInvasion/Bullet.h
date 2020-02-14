#ifndef BULLET_H
#define BULLET_H

#include "AllHeaderFiles.h"

class Bullet : public GameObject
{
	public:
		BULLET_TYPE type;
		bool isAlive;
		DIRECTION direction; 
		bool isReverseDirection;
		
		Bullet(BULLET_TYPE type);
		void Update();
};

#endif
