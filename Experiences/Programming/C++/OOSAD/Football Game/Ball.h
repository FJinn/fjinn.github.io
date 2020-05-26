#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include <algorithm>
#include "StadiumBuilder.h"

using namespace std;

class Ball 
{
	public:
		vector<Player*> observerList;
		
		void Attach(Player* p)
		{
			observerList.push_back(p);
		}
		/*
		void Detach(Player* p)
		{
			observerList.erase(remove(observerList.begin(), observerList.end(),p), observerList.end());
		}
		*/
		
		void Notify(int x, int y, Stadium* stadium)
		{
			// similar to for (int i=0									; i<10						; i++)
			for(vector<Player*>::const_iterator iter = observerList.begin(); iter != observerList.end(); ++iter)
			{
				if(*iter != 0)
				{
					(*iter)->Update(x, y, stadium);
				}
			}
		}
};

class FootballState : public Ball
{
	public:
		void updateBallPosition(int x, int y, Stadium* stadium)
		{
			Notify(x, y, stadium);
		};
};

#endif
