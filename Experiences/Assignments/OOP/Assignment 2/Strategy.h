#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>
#include <string>

using namespace std;

class AttackBehaviour
{
	public:
		virtual int getAttackNumber() = 0;
		virtual string getName() = 0;
		
};

class TechnicalAttack : public AttackBehaviour
{
	private:
		int attackNum = 4;
		string name = "attacking technically.";
	public:
		int getAttackNumber()
		{
			return attackNum;
		}
		
		string getName()
		{
			return name;
		}
		
};

class AllOutAttack : public AttackBehaviour
{
	private:
		int attackNum = 2;
		string name = "kill or be killed.";
	public:
		int getAttackNumber()
		{
			return attackNum;
		}
		
		string getName()
		{
			return name;
		}
		
};

class CriticalAttack : public AttackBehaviour
{
	private:
		int attackNum = 3;
		string name = "hitting weak spot.";
	public:
		int getAttackNumber()
		{
			return attackNum;
		}
		
		string getName()
		{
			return name;
		}
		
};

class DefendBehaviour
{
	public:
		virtual int getDefendNumber() = 0;
		virtual string getName() = 0;
	
};

class Block : public DefendBehaviour
{
	private:
		int defendNum = 2;
		string name = "Block";
	public:
		int getDefendNumber()
		{
			return defendNum;
		}
		
		string getName()
		{
			return name;
		}
		
};

class Dodge : public DefendBehaviour
{
	private:
		int defendNum = 0;
		string name = "Dodge";
	public:
		int getDefendNumber()
		{
			return defendNum;
		}
		
		string getName()
		{
			return name;
		}
		
};

class Withstand : public DefendBehaviour
{
	private:
		int defendNum = 4;
		string name = "Withstand";
	public:
		int getDefendNumber()
		{
			return defendNum;
		}
		
		string getName()
		{
			return name;
		}
		
};

class RunBehaviour
{
	public:
		virtual string getName() = 0;
		virtual int getRunNumber() = 0;
		virtual bool getState() = 0;
};

class Run : public RunBehaviour
{
	private:
		int runNum = 1;
		string name = "Run";
		bool isRun = true;
	public:
		int getRunNumber()
		{
			return runNum;
		}
		
		string getName()
		{
			return name;
		}
		
		bool getState()
		{
			return isRun;
		}
		
};

class CombatStrategy
{
	public:
		AttackBehaviour* ab;
		DefendBehaviour* db;
		RunBehaviour* rb;
		int choice = 0;
		
		void setAttackBehaviour(int choice)
		{
			if(choice == 1)
			{
				ab = new TechnicalAttack();
			}
			else if(choice == 2)
			{
				ab = new AllOutAttack();
			}
			else if(choice == 3)
			{
				ab = new CriticalAttack();
			}
		}
		
		void setDefendBehaviour(int choice)
		{
			if(choice == 1)
			{
				db = new Block();
			}
			else if(choice == 2)
			{
				db = new Dodge();
			}
			else if(choice == 3)
			{
				db = new Withstand();
			}
		}
		
		void setRunBehaviour()
		{
			rb = new Run();
		}
/*		
		string getAttackName()
		{
			ab->getName();
		}
		
		string getDefendName()
		{
			db->getName();
		}
		
		string getRunName()
		{
			rb->getName();
		}
		
		int getAttackNum()
		{
			ab->getAttackNumber();
		}
		
		int getDefendNum()
		{
			db->getDefendNumber();
		}
		
		int getRunNum()
		{
			rb->getRunNumber();
		}
		
		bool getRunBool()
		{
			rb->getState();
		}
*/		
};

#endif
