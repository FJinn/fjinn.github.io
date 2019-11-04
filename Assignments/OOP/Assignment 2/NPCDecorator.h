#ifndef NPCDECORATOR_H
#define NPCDECORATOR_H

#include <iostream>
#include <string>

using namespace std;

class NPC
{
	public:
		string name;
		int hpCount = 0;
		int health = 0;
		int damagePoint = 0;
		
		int getHpCount()
		{
			return hpCount;
		}
		
		int getHealth()
		{
			return health;
		}
		
		virtual string getDesc() = 0;
		virtual void effect()
		{
			hpCount = 0;
		} 
		virtual void setHealth()
		{
			health = 0;
		}
		virtual void setDamagePoint()
		{
			damagePoint = 0;
		}
};

class EnemyType : public NPC
{
	public:
		string getDesc()
		{
			return "A despicable creature appears in front of you.";
		}
};

class DeadNPC : public NPC
{
	public:
		string getDesc()
		{
			return "Seems like it's been dead for quite some time.\n";
		}
};

class Decorator : public NPC
{
	private:
		NPC* npc;
		
	public:
		Decorator(NPC* npc)
		{
			this->npc = npc;
		}
		
		string getDesc()
		{
			return npc->getDesc();
		}
};

class EnemyA: public Decorator
{
	private:
	string Desc()
	{
		return "Your head feels heavy and there is a buzzing noise inside it. \nYou must have been injected with some kind of drug. \nIt might be an illusion, or not..."; 
	}	
	
	public:
		EnemyA(NPC* npc) : Decorator(npc)
		{}
		
		string getDesc()
		{
			return Decorator::getDesc().append(Desc());
		}
		
		void setHealth()
		{
			health = 50;
		}
		
		void setDamagePoint()
		{
			damagePoint = 20;
		}
};

class HarmfulNPC : public Decorator
{
	private:
		string Desc()
		{
			return "   The flesh is still rotting and smelt like an awful rotten egg. \n   It makes you feel dizzy.";
		}
	public:
		HarmfulNPC(NPC* npc) : Decorator(npc)
		{}
		
		string getDesc()
		{
			return Decorator::getDesc().append(Desc());
		}
			
		void effect()
		{
			hpCount -= 5;
		} 
};

class HelpfulNPC : public Decorator
{
	private:
		string Desc()
		{
			return "There is something hidden under its dirty and blood-covered cloth. You found a family photograph.";
		}
	public:
		HelpfulNPC(NPC* npc) : Decorator(npc)
		{}
		
		string getDesc()
		{
			return Decorator::getDesc().append(Desc());
		}
			
		void effect()
		{
			hpCount += 5;
		} 	
};



#endif
