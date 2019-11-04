#ifndef COMBATINTERFACE_H
#define CONBATINTERFACE_H

#include "Strategy.h"
#include "NPCDecorator.h"
#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class CombatInterface
{
public:
	CombatStrategy* cs = new CombatStrategy();
	int playerHealth;
	int defense;
	int strength;
	int num;
	EnemyA* enemyA = new EnemyA(new Decorator(new EnemyType()));;
	
	void getPlayerHealth(int playerHP)
	{
		playerHealth = playerHP;
	}
	
	void getPlayerStat(int defensePoint, int strengthPoint)
	{
		defense = defensePoint;
		strength = strengthPoint;
	}
	
	void combatMenu(int x, int y)
	{
		enemyA->setHealth();
		enemyA->setDamagePoint();
		cout<<enemyA->getDesc()<<endl;
		system("PAUSE");
		int choice = 0;
		bool outOfCombat = false;
		do
		{
			system("CLS");
			gotoxy(42,3);
			cout<<"Player Info";
			gotoxy(42,4);
			cout<<"============";
			gotoxy(42,5);
			cout<<"Health: "<<playerHealth;
			
			gotoxy(42,8);
			cout<<"Enemy Info";
			gotoxy(42,9);
			cout<<"============";
			gotoxy(42,10);
			cout<<"Health: "<<enemyA->health;
			
			if(choice == 0)
			{
				gotoxy(x, y);
				cout<<"1. Attack";
				gotoxy(x, y+1);
				cout<<"2. Defend";
				gotoxy(x, y+2);
				cout<<"3. Run";
				gotoxy(x, y+3);
				cin>>choice;
			}
			else if(choice == 1)
			{
				int attackChoice = 0;
				gotoxy(x, y+3);
				cout<<"1. Technical Attack";
				gotoxy(x, y+4);
				cout<<"2. All Out Attack";
				gotoxy(x, y+5);
				cout<<"3. Critical Attack";
				gotoxy(x, y+6);
				cout<<"4. Back";
				gotoxy(x, y+7);
				cout<<"Your Choice: ";
				cin>> attackChoice;
				
				if(attackChoice == 4)
				{
					choice = 0;
				}
				else
				{ 
					cs->setAttackBehaviour(attackChoice);
					num = cs->ab->getAttackNumber();
					enemyA->health -= num * strength;
					gotoxy(x, y+13);
					cout<<"You swing your fist at it with the goal of "<< cs->ab->getName();
					gotoxy(x, y+14);
					cout<<"You landed your attack, but it scratches you at the same time.";
					playerHealth -= enemyA->damagePoint - (defense/4);
					gotoxy(x, y+40);
					system("PAUSE");
				}
				
				choice = 0;
				
				if(enemyA->getHealth() <= 0 || playerHealth <= 0)
				{
					outOfCombat = true;
				}
			}
			else if (choice == 2)
			{
				int defendChoice = 0;
				gotoxy(x, y+3);
				cout<<"1. Block";
				gotoxy(x, y+4);
				cout<<"2. Dodge";
				gotoxy(x, y+5);
				cout<<"3. Withstand";
				gotoxy(x, y+6);
				cout<<"4. Back";
				gotoxy(x, y+7);
				cout<<"Your Choice: ";
				gotoxy(x, y+8);
				cin>> defendChoice;
				
				if(defendChoice == 4)
				{
					choice = 0;
				}
				else
				{
					cs->setDefendBehaviour(defendChoice);
					num = cs->db->getDefendNumber();
					gotoxy(x, y+13);
					cout<<"You are waiting for a good timing to attack.";
					gotoxy(x, y+14);
					cout<<"Before that, you "<< cs->ab->getName() << " enemy's attack.";
					gotoxy(x, y+15);
					cout<<"It happened too quick, but you managed to defend with your strategy.";
					playerHealth -= (enemyA->damagePoint- (num+defense));
					gotoxy(x, y+40);
					system("PAUSE");
				}
				
				choice = 0;
			}
			else if(choice == 3)
			{
				cs->setRunBehaviour();
				num = cs->rb->getRunNumber();
				gotoxy(x, y+3);
				cout<<"You have decided to run.";
				gotoxy(x, y+4);
				cout<<"Without hesitation, you run as fast as you can without looking back.";
				outOfCombat = cs->rb->getState();
				gotoxy(x, y+40);
				system("PAUSE");
				
			}
		}while(!outOfCombat);
		
	}
};

#endif
