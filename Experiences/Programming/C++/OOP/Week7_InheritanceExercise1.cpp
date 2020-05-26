#include <iostream>
#include "windows.h"
#include <string>
#include <typeinfo>

using namespace std;

class Hero
{
public:
	int hp;
	int damage;
	int level;
	
	Hero(int h, int d, int l)
	{
		hp = h;
		damage = d;
		level = l;
	}	
	
	virtual void Attack(Hero* temp) = 0;
};

class Archer : public Hero
{
public:
	int distance;
	Archer(int h, int d, int l, int t): Hero(h,d, l)
	{
		distance = t;
	}
	void Attack(Hero* temp)
	{
		temp->hp -= damage* (distance/100);
	}
};

class Warrior : public Hero
{
public:
	int skill;
	Warrior(int h, int d, int l, int s): Hero(h,d, l)
	{
		skill = s;
	}
	void Attack(Hero* temp)
	{
		temp->hp -= damage*skill;
	}	
};

int main()
{
	Hero* a1 = new Archer(100,5,1,800);
	Hero* w1= new Warrior(100,8,1,5);
	Hero* heroList[] = {a1, w1};
	
	bool isExit = false;
	
	do
	{
		if(heroList[0]->hp > 0 && heroList[1]->hp >0)
		{
			for(int i=0; i<2; i++)
			{
				if(typeid(*heroList[i]) == typeid(*a1) && heroList[i]->hp >0)
				{
					cout<<"Archer attacks Warrior."<<endl;
					heroList[i]->Attack(heroList[i+1]);
					cout<<"Archer HP: "<<heroList[i]->hp<<endl;
					cout<<"Warrior HP: "<<heroList[i+1]->hp<<endl;
				}
				else if (typeid(*heroList[i]) == typeid(*w1) && heroList[i]->hp >0)
				{
					cout<<endl<<"Warrior attacks Archer."<<endl;
					heroList[i]->Attack(heroList[i-1]);
					cout<<"Archer HP: "<<heroList[i-1]->hp<<endl;
					cout<<"Warrior HP: "<<heroList[i]->hp<<endl << endl;
				}
			}
		}
		else
		{
			if(heroList[1]->hp <0)
			{
				cout<<"Archer wins."<<endl;
			}
			else if( heroList[0]->hp <0)
			{
				cout<<"Warrior wins."<<endl;
			}
			
			isExit = true;
		}
		
	}while(!isExit);
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
