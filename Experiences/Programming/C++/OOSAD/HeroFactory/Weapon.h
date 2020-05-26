#pragma once
#include <string>

using namespace std;

class Weapon
{
	string name;
	public:
		Weapon(string n) : name(n)
		{}
		string getName()
		{
			return name;
		} 
};

class Sword : public Weapon
{
	public:
		Sword() : Weapon("Sword")
		{}
};

class Wand : public Weapon
{
	public:
		Wand() : Weapon("Wand")
		{}
};

class Bow : public Weapon
{
	public:
		Bow() : Weapon("Bow")
		{}
};

class Dagger : public Weapon
{
	public:
		Dagger() : Weapon("Dagger")
		{}
};
