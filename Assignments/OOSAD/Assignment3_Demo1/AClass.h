#pragma once
#ifndef _ACLASS_H_
#define _ACLASS_H_

#include <vector>
#include <iostream>
#include "item.h"
#include "Behavior.h"

using namespace std;

class AClass
{
	protected:
		string name;
		int hp, strength, vitality, level, speed, mana;
		
	public:
		Behaviour* behaviour;
		vector<Item> equipment;
		enum HERO_TYPE
		{
			SPARTAN = 0,
			SOLDIER,
			NINJA,
			ARCHER,
			MAGE
		};
		
		void CreateEquipment(Item equipment);
		void PrintEquipment();
		void ChangeEquiment(int choice, string type);
		void LevelUp();
		string getName();
		int getHP();
		int getStr();
		int getVit();
		int getLvl();
		int getSpd();
		int getMP();
		void performBehaviour();
		void SetBehaviour(Behaviour* behave);
		static AClass* CreateClass(int choice);
};

#endif
