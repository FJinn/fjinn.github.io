#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "StadiumBuilder.h"

using namespace std;

class Referee
{
	private:
		string name = "R";
	public:
		Referee(){};
		
		string getName()
		{
			return name;
		}
};

class Observer
{
	public:
		
		virtual void Update(int x, int y, Stadium* stadium) = 0;
};

class Player : public Observer
{
	public:
		int number;
		string name;
		int positionX;
		int positionY;
		
		void addName(string n)
		{
			name = n;
		}
		
		int getNumber()
		{
			return number;
		}
		
		void setPosition(int x, int y)
		{
			positionX = x;
			positionY = y;
		}
		
		int getPositionX()
		{
			return positionX;
		}
		
		int getPositionY()
		{
			return positionY;
		}
		
		string getName()
		{
			return name;
		}
		
		void Update(int x, int y, Stadium* stadium)
		{
			for(int i=y-2; i<=y+2; i++)
			{
				for(int j=x-2; j<=x+2; j++)
				{
					if(positionX == j && positionY == i)
					{
						cout<<"Name: "<<name<<" at "<<stadium->map[positionY][positionX]<<" : "<<"The ball is at x position: "<<x+1<<", and y position: " <<y+1<<"."<<endl;
						cout<<"Row: "<<y+1<<", Column: "<<x+1<<"."<<endl;
						cout<<endl;
					}
				}
			}
		}
		
		virtual string getDetails() = 0;
		
};

class Substitute : public Player
{
	public:
		string getDetails()
		{
			return "He is a substitute.";
		}
		
};

class StartingLineUp : public Player
{
	public:
		string getDetails()
		{
			return "He is a starting line up.";
		}
};

class Decorator : public Player
{
	protected:
		Player* player;
	public:
		Decorator(Player* p)
		{
			player = p;
		}
		
		string getDetails()
		{
			return player->getDetails();
		}
		
};

class Striker : public Decorator
{
	private:
		string description()
		{
			return "He plays striker position.";
		}
	public:
		Striker(Player* p): Decorator(p){};
		
		string getDetails()
		{
			return Decorator::getDetails().append(description());
		}
};

class Defender : public Decorator
{
	private:
		string description()
		{
			return "He plays defender position.";
		}
	public:
		Defender(Player* p): Decorator(p){};
		string getDetails()
		{
			return Decorator::getDetails().append(description());
		}
};

class MidField : public Decorator
{
	private:
		string description()
		{
			return "He plays midField position.";
		}
	public:
		MidField(Player* p): Decorator(p){};
		string getDetails()
		{
			return Decorator::getDetails().append(description());
		}
};

class GoalKeeper : public Decorator
{
	private:
		string description()
		{
			return "He is goal keeper.";
		}
	public:
		GoalKeeper(Player* p): Decorator(p){};
		string getDetails()
		{
			return Decorator::getDetails().append(description());
		}
		
};

#endif
