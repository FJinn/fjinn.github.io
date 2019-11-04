#pragma once
#include <string>

using namespace std;

class Armor
{
	string name;
	public:
		Armor(string n) : name(n)
		{}
		string getName()
		{
			return name;
		}
		
};

class Glove : public Armor
{
	public:
		Glove() : Armor("Glove")
		{}	
};

class StainedShirt : public Armor
{
	public:
		StainedShirt() : Armor("StainedShirt")
		{}
};

class ShortPants : public Armor
{
	public:
		ShortPants() : Armor("ShortPants")
		{};
};

class ClownHat : public Armor
{
	public:
		ClownHat() : Armor("ClownHat")
		{}
};
