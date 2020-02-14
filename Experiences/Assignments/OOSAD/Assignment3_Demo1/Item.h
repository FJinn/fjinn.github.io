#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>

using namespace std;

class Item
{
	sring name, type;
	int atk, def, spd;
	public:
		Item(string n, int attack, int defence, string t, int speed) : name(n), atk(attack), def(defence), type(t), spd(speed)
		{}
		
		string getName()
		{
			return name;
		}
		string getType()
		{
			return type;
		}
		int getAttack()
		{
			return atk;
		}
		int getDefence()
		{
			return def;
		}
		int getSpeed()
		{
			return spd;
		}
};

class EnergySword : pubilc Item
{
	public:
		EnergySword(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};

class NanoBlade : pubilc Item
{
	public:
		NanoBlade(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class OmniTool : pubilc Item
{
	public:
		OmniTool(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class LightSaber : pubilc Item
{
	public:
		LightSaber(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class DermalArmor : pubilc Item
{
	public:
		DermalArmor(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class SpartanArmor : pubilc Item
{
	public:
		SpartanArmor(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class N7 : pubilc Item
{
	public:
		N7(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class AthenaArmor : pubilc Item
{
	public:
		AthenaArmor(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class HermesBoots : pubilc Item
{
	public:
		HermesBoots(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class MagneticBoots : pubilc Item
{
	public:
		MagneticBoots(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class Greaves : pubilc Item
{
	public:
		Greaves(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class Lazada : pubilc Item
{
	public:
		Lazada(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class IronRing : pubilc Item
{
	public:
		IronRing(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class Gauntlet : pubilc Item
{
	public:
		Gauntlet(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class CurseGauntlet : pubilc Item
{
	public:
		CurseGauntlet(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class AttackGauntlet : pubilc Item
{
	public:
		AttackGauntlet(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class Helmet : pubilc Item
{
	public:
		Helmet(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class Specs : pubilc Item
{
	public:
		Specs(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class None : pubilc Item
{
	public:
		None(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};
class Madness : pubilc Item
{
	public:
		Madness(string n, int attack, int defence, string t, int speed) : Item(n, attack, defence, t , speed)
		{}
};

#endif
