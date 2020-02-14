#include "HeroFactory.h"
#include "Weapon.h"
#include "Armor.h"
#include "Job.h"

void HeroFactory::WeaponList(Weapon weapon)
{
	this->weapon.push_back(weapon);
}

void HeroFactory::ArmorList(Armor armor)
{
	this->armor.push_back(armor);
}

void HeroFactory::PrintStatus()
{
	for(int i=0; i<weapon.size();i++)
	{
		cout<<"Weapon: ";
		cout<<weapon[i].getName()<<endl;
	}
	
	for(int i=0; i<armor.size();i++)
	{
		cout<<"Armor: ";
		cout<<armor[i].getName()<<endl;
	}
}

HeroFactory* HeroFactory::CreateHero(int choice)
{
	if(choice == 1)
	{
		return new Warrior();
	}
	else if(choice == 2)
	{
		return new Archer();
	}
	else if(choice == 3)
	{
		return new Mage();
	}
}

