#pragma once
#include <vector>
#include "Weapon.h"
#include "Armor.h"
#include <iostream>

using namespace std;

class HeroFactory
{
	public:
		enum JOB_TYPE
		{
			WARRIOR=0,
			ARCHER,
			MAGE
		};
		vector<Weapon> weapon;
		vector<Armor> armor;
		
		void WeaponList(Weapon weapon);
		void ArmorList(Armor armor);
		void PrintStatus();
		static HeroFactory* CreateHero(int choice); 

};
