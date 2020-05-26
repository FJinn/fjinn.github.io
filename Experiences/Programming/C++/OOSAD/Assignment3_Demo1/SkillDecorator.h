#ifndef SKILLDECORATOR_H
#define SKILLDECORATOR_H

#include "windows.h"
#include <iostream>
#include <string>
#include "AClass.h"

using namespace std;

class Skill : public AClass
{
	public:
		virtual double getCost()=0;
		virtual string getDesc()=0;
};

class Fire : public Skill
{
	public:
		double getCost()
		{
			return 10;
		}
		
		string getDesc()
		{
			return "Fire";
		}
};

class Lightning : public Skill
{
	public:
		double getCost()
		{
			return 30;
		}
		
		string getDesc()
		{
			return "Lightning";
		}
};


class Earth : public Skill
{
	public:
		double getCost()
		{
			return 20;
		}
		
		string getDesc()
		{
			return "Fire";
		}
};

class SubDecorator : public Skill
{
	protected:
		Skill* skill;
	public:
		SubDecorator(Skill* skillRef)
		{
			skill = skillRef;
		}
		
		double getCost()
		{
			return skill->getCost();
		}
		
		string getDesc()
		{
			return skill->getDesc();
		}
};

class FireDecorator  : public SubDecorator
{
	private:
		int fireCost;
		int fireDmg = getStr();
		string fire_Desc()
		{
			return " + Fire";
		}
	public:
		FireDecorator(Skill* skillRef) : SubDecorator(skillRef)
		{
			fireCost = 10;
		}
		double getCost()
		{
			return SubDecorator::getCost() + fireCost;
		}
		
		string getDesc()
		{
			return SubDecorator::getDesc().append(fire_Desc());
		}
};

class LightningDecorator  : public SubDecorator
{
	private:
		int lightningCost;
		int lightningDmg = getStr() + getVit();
		string lightning_Desc()
		{
			return " + Lightning";
		}
	public:
		LightningDecorator(Skill* skillRef) : SubDecorator(skillRef)
		{
			lightningCost = 30;
		}
		double getCost()
		{
			return SubDecorator::getCost() + lightningCost;
		}
		
		string getDesc()
		{
			return SubDecorator::getDesc().append(lightning_Desc());
		}
};

class EarthDecorator  : public SubDecorator
{
	private:
		int earthCost;
		int earthDmg = getVit();
		string earth_Desc()
		{
			return " + Earth";
		}
	public:
		EarthDecorator(Skill* skillRef) : SubDecorator(skillRef)
		{
			earthCost = 20;
		}
		double getCost()
		{
			return SubDecorator::getCost() + earthCost;
		}
		
		string getDesc()
		{
			return SubDecorator::getDesc().append(earth_Desc());
		}
};

#endif
