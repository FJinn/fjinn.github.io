#ifndef ITEM_H
#define ITEM_H

#include "AllHeaderFiles.h"

class Item: public GameObject
{
	public:
		bool isAlive;
		
		ITEM_TYPE itemType;
		int updateDelayTimer;
		int updateDelayDuration;
		
		BULLET_TYPE bulletType;
		
		int shootDelayDuration;
		
		Item(ITEM_TYPE itemType);
		void Update();
};

#endif
