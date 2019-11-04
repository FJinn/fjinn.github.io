#ifndef CHARACTERSTATBUILDER_H
#define CHARACTERSTATBUILDER_H

using namespace std;

class Mana
{
	public:
		int manaInt;
};

class Weapon
{
	public:
		string weaponName;
};
class Body
{
	public:
		string bodyName;
};
class Health
{
	public:
		int healthInt;
};
class Strength
{
	public:
		int strengthInt;
};
class Vitality
{
	public:
		int vitalityInt;
};class Speed
{
	public:
		int speedInt;
};
class Boots
{
	public:
		string bootsName;
};
class Hands
{
	public:
		string handsName;
};
class Legs
{
	public:
		string legsName;
};
class Head
{
	public:
		string headName;
};

class Job
{
	public:
		Weapon* weapon;
		Body* body;
		Strength* strength;
		Vitality* vitality;
		Health* health;
		Speed* speed;
		Boots* boots;
		Hands* hands;
		Legs* legs;
		Head* head;
		Mana* mana;
		
		void specification()
		{
			cout<<"Health: "<<health->healthInt<<endl;
			cout<<"Mana: "<<mana->manaInt<<endl;
			cout<<"Strength: "<<strength->strengthInt<<endl;
			cout<<"Vitality: "<<vitality->vitalityInt<<endl;
			cout<<"Speed: "<speed->speedInt<<endl;
			cout<<"Head: "<<head->headName<<endl;
			cout<<"Hands: "<hands->handsName<<endl;
			cout<<"Legs: "<<legs->legsName<<endl;
			cout<<"Body: "<<health->healthInt<<endl;
			cout<<"Weapon: "<<weapon->weaponName<<endl;
		}
		
};

class Builder
{		
	virtual Weapon* getWeapon() = 0;
	virtual Body* getBody() = 0;
	virtual Boots* getBoots() = 0;
	virtual Hands* getHands() = 0 ;
	virtual Legs* getLegs() = 0;
	void printStats();
};
		
class SpartanHero: public Builder
{
	public:
		Weapon* getWeapon()
		{
			Weapon* weapon = new Weapon();
			weapon->weaponName = "Nano Blade";'
			return weapon;
		}
};
		
class SoldierHero: public Builder
{
			
};
		
class NinjaHero: public Builder
{
			
};
		
class ArcherHero: public Builder
{
			
};
		
class MageHero: public Builder
{
			
};

class Director
{
	public:
		Builder* builder;
		
		void setBuilder(Builder* newBuilder)
		{
			builder = newBuilder;
		}
		
		Job* getJob()
		{
			Job* job = new Job();
			job->weapon = builder->getWeapon();
		}
};
#endif
